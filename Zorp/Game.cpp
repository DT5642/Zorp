#include "Game.h"
#include <iostream>
#include <random>
#include <Windows.h>
#include <time.h>

using std::cout;
using std::cin;

Game::Game() : m_gameOver{ false }
{
}

Game::~Game()
{
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

	InitializeMap();
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

	if (m_player.ExecuteCommand(command));
	{
		return;
	}

	m_map[playerPos.y][playerPos.x].ExecuteCommand(command, &m_player);
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

void Game::InitializeMap()
{
	srand(time(nullptr));

	//Fill the arrays with random room types
	for (int y = 0; y < MAZE_HEIGHT; y++)
	{
		for (int x = 0; x < MAZE_WIDTH; x++)
		{
			int type = rand() % (MAX_RANDOM_TYPE * 2);

			if (type < MAX_RANDOM_TYPE)
			{
				if (type == TREASURE)
				{
					type = rand() % 3 + TREASURE_HP;
				}

				m_map[y][x].SetType(type);
			}
			else
			{
				m_map[y][x].SetType(EMPTY);
			}
			m_map[y][x].SetPosition(Point2D{ x, y });
		}
	}
	//Set the rntrance and exit of the maze
	m_map[0][0].SetType(ENTRANCE);
	m_map[MAZE_HEIGHT - 1][MAZE_WIDTH - 1].SetType(EXIT);
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
	cout << CSI << "4M";

	//Insert 4 blank lines to ensure the inventory output remains correct
	cout << CSI << "4L";

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