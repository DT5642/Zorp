#include "Game.h"
#include <time.h>
#include <random>
#include <iostream>
#include <Windows.h>
#include "Enemy.h"
#include "Food.h"
#include "Powerup.h"

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

	//Set the entrance and exit of the mase
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

		char next = cin.peek();
		
		if (next == '\n' || next == EOF)
		{
			break;
		}
		cin >> input;
	}

	return 0;
}