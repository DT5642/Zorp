#include "Game.h"
#include "Food.h"
#include "Enemy.h"
#include "Powerup.h"
#include <time.h>
#include <string>
#include <random>
#include <fstream>
#include <iostream>
#include <Windows.h>

using std::cout;
using std::cin;

Game::Game() : m_gameOver{ false }
{
}

Game::~Game()
{
	delete[] m_powerups;
	delete[] m_enemies;
	delete[] m_food;
}

bool Game::Startup()
{
	if (EnableVirtualTerminal() == false)
	{
		cout << "The virtual terminal processing mode could not be activated.\n";
		cout << "Press 'Enter' to exit.\n";
		cin.get();
		return false;
	}
	srand(time(nullptr));

	InitialiseMap();
	InitialiseEnemies();
	InitialisePowerups();
	InitialiseFood();

	m_player.SetPosition(Point2D{ 0, 0 });
	DrawWelcomMessage();
	return true;
}

void Game::Update()
{
	Point2D playerPos = m_player.GetPosition();

	if (m_map[playerPos.y][playerPos.x].GetType() == EXIT)
	{
		m_gameOver = true;
		return;
	}

	int command = GetCommand();

	if (command == QUIT)
	{
		m_gameOver = true;
		return;
	}

	m_player.ExecuteCommand(command, &m_map[playerPos.y][playerPos.x]);

	for (int i = 0; i < m_enemyCount; i++)
	{
		if (m_enemies[i].IsAlive() == false)
		{
			Point2D pos = m_enemies[i].GetPosition();
			m_map[pos.y][pos.x].RemoveGameObject(&m_enemies[i]);
		}
	}
}

void Game::Draw()
{
	Point2D playerPos = m_player.GetPosition();

	//List the directions the player can take
	DrawValidDirections();

	//Draw the description of the current room
	m_map[playerPos.y][playerPos.x].DrawDescription();

	//Redraw the map
	DrawMap();

	//Draw the player on the map
	m_player.Draw();
}

bool Game::IsGameOver()
{
	return m_gameOver;
}

Powerup* Game::FindPowerup(const char* name, bool isLoading) const
{
	return nullptr;
}

bool Game::EnableVirtualTerminal()
{
	//Set output mode to handle virtual terminal sequences
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	if (hOut == INVALID_HANDLE_VALUE)
	{
		return false;
	}

	DWORD dwMode = 0;
	if (!GetConsoleMode(hOut, &dwMode))
	{
		return false;
	}

	dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	if (!SetConsoleMode(hOut, dwMode))
	{
		return false;
	}

	return true;
}

void Game::InitialiseMap()
{
	//Set room positions
	for (int y = 0; y < MAZE_HEIGHT; y++)
	{
		for (int x = 0; x < MAZE_WIDTH; x++)
		{
			m_map[y][x].SetPosition(Point2D{ x, y });
		}
	}

	//Set the entrance and exit of the maze
	m_map[0][0].SetType(ENTRANCE);
	m_map[MAZE_HEIGHT - 1][MAZE_WIDTH - 1].SetType(EXIT);
}

void Game::InitialiseEnemies()
{
	//Create a dynamic array of enemies
	//(The number of enemies will change every game)
	m_enemyCount = 1 + rand() % 4;
	m_enemies = new Enemy[m_enemyCount];

	//Randomly place the enemies in the rooms on the map
	for (int i = 0; i < m_enemyCount; i++)
	{
		//A bit of math ensures the enemies wont spawn directly on or next to the entrance
		int x = 2 + (rand() % (MAZE_WIDTH - 3));
		int y = 2 + (rand() % (MAZE_HEIGHT - 3));

		m_enemies[i].SetPosition(Point2D{ x, y });
		m_map[y][x].AddGameObject(&m_enemies[i]);
	}
}

void Game::InitialisePowerups()
{
	//Create some powerups
	m_powerupCount = 3;
	m_powerups = new Powerup[m_powerupCount];

	//Randomly place the food in the map
	for (int i = 0; i < m_powerupCount; i++)
	{
		char name[30] = "";
		int x = rand() % (MAZE_WIDTH - 1);
		int y = rand() % (MAZE_HEIGHT - 1);

		float HP = 1;
		float AT = 1;
		float DF = 1;

		switch (i)
		{
		case 0:
		{
			strcpy_s(name, "potion of ");
			m_powerups[i].SetHealthMultiplier(1.1f);
			break;
		}
		case 1:
		{
			strcpy_s(name, "sword of ");
			m_powerups[i].SetAttackMultiplier(1.1f);
			break;
		}
		case 2:
		{
			strcpy_s(name, "shield of ");
			m_powerups[i].SetDefenceMultiplier(1.1f);
			break;
		}
		}

		strncat_s(name, itemNames[(rand() % 15)], 30);
		m_powerups[i].SetName(name);
		m_powerups[i].SetPosition(Point2D{ x, y });
		m_map[y][x].AddGameObject(&m_powerups[i]);
	}
}

void Game::InitialiseFood()
{
	//Create some food
	m_foodCount = 3;
	m_food = new Food[m_foodCount];
	
	//Randomly place the food in the map
	for (int i = 0; i < m_foodCount; i++)
	{
		int x = rand() % (MAZE_WIDTH - 1);
		int y = rand() % (MAZE_HEIGHT - 1);
		m_food[i].SetPosition(Point2D{ x, y });
		m_map[y][x].AddGameObject(&m_food[i]);
	}
}

void Game::DrawWelcomMessage()
{
	cout << TITLE << MAGENTA << "Welcome to Zorp!" << RESET_COLOR << "\n";
	cout << INDENT << "ZORP is a game of adventure, danger and low cunning.\n";
	cout << INDENT << "It is definitely not related to any other text-based adventure game.\n\n";
}

void Game::DrawMap()
{
	Point2D position = { 0, 0 };

	//Reset draw colours
	cout << RESET_COLOR;

	for (position.y = 0; position.y < MAZE_HEIGHT; position.y++)
	{
		for (position.x = 0; position.x < MAZE_WIDTH; position.x++)
		{
			m_map[position.y][position.x].Draw();
		}
		cout << "\n";
	}
}

void Game::DrawValidDirections()
{
	Point2D position = m_player.GetPosition();

	//Reset draw colours
	cout << RESET_COLOR;
	//Jump to the correct location
	cout << CSI << MOVEMENT_DESC_Y + 1 << ";" << 0 << "H";
	cout << INDENT << "You can see paths leading to the " <<
		((position.x > 0) ? "west, " : "") <<
		((position.x < MAZE_WIDTH - 1) ? "east, " : "") <<
		((position.y > 0) ? "north, " : "") <<
		((position.y < MAZE_HEIGHT - 1) ? "south, " : "") << "\n";
}

void Game::Save()
{
	std::ofstream out;

	//Open the file for ouput, and truncate (any contents that existed in the file before it is open are discarded)

	out.open("Zorp_Savegame.txt", std::ofstream::out | std::ofstream::trunc);

	if (out.is_open())
	{
		//Save the position of every gam object, and the player's stats
		if (m_gameOver == true)
		{
			cout << EXTRA_OUTPUT_POS << "You have perished. Saving will not save you\n";
			cout << INDENT << "Your progress has not been saved.\n" << RESET_COLOR;
		}
		else
		{
			//Output the powerups first, as these will need to be loaded before we load any characters 
			//(So we can correctly copy the powerup points to the characters' powerup list)
			out << m_powerupCount << "\n";

			for (int i = 0; i < m_powerupCount; i++)
			{
				m_powerups[i].Save(out);
			}

			out << m_enemyCount << "\n";
			for (int i = 0; i < m_enemyCount; i++)
			{
				m_enemies[i].Save(out);
			}

			out << m_foodCount << "\n";
			for (int i = 0; i < m_foodCount; i++)
			{
				m_food[i].Save(out);
			}

			m_player.Save(out);
		}
	}
	else
	{
		//Could not open the file, display an error message
		cout << EXTRA_OUTPUT_POS << RED << "A grue has corrupted the scroll of rememberance.\n";
		cout << INDENT << "You progess has not been saved.\n" << RESET_COLOR;
	}

	out.flush();
	out.close();
}

bool Game::Load()
{
	std::ifstream in;
	in.open("Zorp_Savegame.txt", std::ofstream::in);

	if (!in.is_open())
	{
		return false;
	}

	char buffer[50] = { 0 };

	//Load all the powerups
	if (m_tempPowerups != nullptr)
	{
		delete[] m_tempPowerups;
	}

	in.getline(buffer, 50);
	m_tempPowerupCount = std::stoi(buffer);

	if (in.rdstate() || m_tempPowerupCount < 0)
	{
		return false;
	}

	m_tempPowerups = new Powerup[m_tempPowerupCount];

	for (int i = 0; i < m_tempPowerupCount; i++)
	{
		if (m_tempPowerups[i].Load(in, this) == false)
		{
			delete[] m_tempPowerups;
			m_tempPowerups = nullptr;
			return false;
		}
	}

	//Load all the enemies
	in.getline(buffer, 50);
	int enemyCount = std::stoi(buffer);
	if (in.rdstate() || enemyCount < 0);
	{
		return false;
	}
	Enemy* enemies = new Enemy[enemyCount];
	for (int i = 0; i < enemyCount; i++)
	{
		if (enemies[i].Load(in, this) == false)
		{
			delete[] enemies;
			delete[] m_tempPowerups;
			m_tempPowerups = nullptr;
			return false;
		}
	}

	//Load all the food
	in.getline(buffer, 50);
	int foodCount = std::stoi(buffer);
	if (in.rdstate() || foodCount < 0)
	{
		return false;
	}
	Food* foods = new Food[foodCount];
	for (int i = 0; i < foodCount; i++)
	{
		if (foods[i].Load(in, this) == false)
		{
			delete[] foods;
			delete[] enemies;
			delete[] m_tempPowerups;
			m_tempPowerups = nullptr;
			return false;
		}
	}

	//Load the player
	Player player;
	if (player.Load(in, this) == false)
	{
		delete[] foods;
		delete[] enemies;
		delete[] m_tempPowerups;
		m_tempPowerups = nullptr;
		return false;
	}

	//Everything succeeded up to here, so rebuild the level

	//Clean out the rooms
	for (int y = 0; y < MAZE_HEIGHT; y++)
	{
		for (int x = 0; x < MAZE_WIDTH; x++)
		{
			m_map[y][x].ClearGameObjects();
		}
	}

	//Add the powerups
	delete[] m_powerups;
	m_powerups = m_tempPowerups;
	m_powerupCount = m_tempPowerupCount;
	m_tempPowerups = nullptr;

	for (int i = 0; i < m_powerupCount; i++)
	{
		Point2D pos = m_powerups[i].GetPosition();
		if (pos.x >= 0 && pos.y >= 0)
		{
			m_map[pos.y][pos.x].AddGameObject(&m_powerups[i]);
		}
	}

	//Add the enemies
	delete[] m_enemies;
	m_enemies = enemies;
	m_enemyCount = enemyCount;
	for (int i = 0; i < m_enemyCount; i++)
	{
		Point2D pos = m_enemies[i].GetPosition();
		if (m_enemies->IsAlive())
		{
			m_map[pos.y][pos.x].AddGameObject(&m_enemies[i]);
		}
	}

	//Add the food
	delete[] m_food;
	m_food = foods;
	m_foodCount = foodCount;

	for (int i = 0; i < m_foodCount; i++)
	{
		Point2D pos = m_food[i].GetPosition();
		if (pos.x >= 0 && pos.y >= 0)
		{
			m_map[pos.y][pos.x].AddGameObject(&m_food[i]);
		}
	}

	m_player = player;

	return true;
}

int Game::GetCommand()
{
	//For nowm we can't read commands longer than 50 characters
	char input[50] = "\0";

	//Jump to the correct location
	cout << CSI << PLAYER_INPUT_Y << ";" << 0 << "H";

	//Clear any existing text
	cout << CSI << "5M";

	//Insert 5 blank lines to ensure the inventory output remains correct
	cout << CSI << "5L";

	cout << INDENT << "Enter a command.";
	
	//Move cursor to position for player to enter input
	cout << CSI << PLAYER_INPUT_Y << ";" << PLAYER_INPUT_X << "H" << YELLOW;

	//Clear the input buffer, ready for player input
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());

	cin >> input;
	cout << RESET_COLOR;

	bool bMove = false;
	bool bPickup = false;

	while (input)
	{
		if (strcmp(input, "move") == 0)
		{
			bMove = true;
		}
		else if (bMove == true)
		{
			if (strcmp(input, "north") == 0)
			{
				return NORTH;
			}
			if (strcmp(input, "south") == 0)
			{
				return SOUTH;
			}
			if (strcmp(input, "east") == 0)
			{
				return EAST;
			}
			if (strcmp(input, "west") == 0)
			{
				return WEST;
			}
		}
		if (strcmp(input, "look") == 0)
		{
			return LOOK;
		}
		if (strcmp(input, "fight") == 0)
		{
			return FIGHT;
		}
		if (strcmp(input, "exit") == 0)
		{
			return QUIT;
		}
		if (strcmp(input, "pick") == 0)
		{
			bPickup = true;
		}
		else if (bPickup == true)
		{
			if (strcmp(input, "up") == 0)
			{
				return PICKUP;
			}
		}
		if (strcmp(input, "save") == 0)
		{
			//Process the save command here, as the game class is the only class with direct access to the game objects
			Save();
			return SAVE;
		}
		if (strcmp(input, "load") == 0)
		{
			Load();
			return LOAD;
		}

		char next = cin.peek();
		
		if (next == '\n' || next == EOF)
		{
			break;
		}
		cin >> input;
	}

	return 0;
}