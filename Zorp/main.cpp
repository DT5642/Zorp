#include <iostream>
#include <Windows.h>
#include <random>
#include <time.h>

using std::cout;
using std::cin;

//Console commands for universal functionality (Windows + Linux)
const char* ESC = "\x1b";
const char* CSI = "\x1b[";
const char* RED = "\x1b[91m";
const char* BLUE = "\x1b[94m";
const char* WHITE = "\x1b[97m";
const char* GREEN = "\x1b[92m";
const char* TITLE = "\x1b[5;20H";
const char* INDENT = "\x1b[5C";
const char* YELLOW = "\x1b[93m";
const char* MAGENTA = "\x1b[95m";
const char* RESET_COLOR = "\x1b[0m";
const char* SAVE_CURSOR_POS = "\x1b[s";
const char* RESTORE_CURSOR_POS = "\x1b[u";

void main()
{
	const int EMPTY = 0;
	const int ENEMY = 1;
	const int TREASURE = 2;
	const int FOOD = 3;
	const int ENTRANCE = 4;
	const int EXIT = 5;

	const int MAX_RANDOM_TYPE = FOOD + 1;

	const int MAZE_WIDTH = 10;
	const int MAZE_HEIGHT = 6;

	const int INDENT_X = 5;
	const int ROOM_DESC_Y = 8;
	const int MAP_Y = 13;
	const int PLAYER_INPUT_X = 30;
	const int PLAYER_INPUT_Y = 11;

	const int WEST = 4;
	const int EAST = 6;
	const int NORTH = 8;
	const int SOUTH = 2;

	bool gameOver = false;
	int playerX = 0;
	int playerY = 0;

	int height = 0;
	int avatarHP = 0;
	char firstLetterOfName = 0;

	//Set output mode to handle virtual terminal sequences
	DWORD dwMode = 0;
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleMode(hOut, &dwMode);
	dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	SetConsoleMode(hOut, dwMode);

	//Create 2D array
	int rooms[MAZE_HEIGHT][MAZE_WIDTH];

	srand(time(nullptr));

	//Fill the awways with room types
	for (int y = 0; y < MAZE_HEIGHT; y++)
	{
		for (int x = 0; x < MAZE_WIDTH; x++)
		{
			int type = rand() % (MAX_RANDOM_TYPE * 2);

			if (type < MAX_RANDOM_TYPE)
			{
				rooms[y][x] = type;
			}
			else
			{
				rooms[y][x] = EMPTY;
			}
		}
	}

	//Set the entrance and exit of the maze
	rooms[0][0] = ENTRANCE;
	rooms[MAZE_HEIGHT - 1][MAZE_WIDTH - 1] = EXIT;

	cout << "Hello world!\n\n";

	cout << TITLE << MAGENTA << "Welcome to Zorp!\n" << RESET_COLOR;
	cout << INDENT << "Zorp is a game of adventure, danger, and low cunning.\n";
	cout << INDENT << "It is definitely not related to any other text-based adventure game...\n";
	cin.get();

	//Save cursor position
	cout << SAVE_CURSOR_POS;

	//Output map
	cout << CSI << MAP_Y << ";" << 0 << "H";
	for (int y = 0; y < MAZE_HEIGHT; y++)
	{
		cout << INDENT;
		for (int x = 0; x < MAZE_WIDTH; x++)
		{
			switch (rooms[y][x])
			{
			case EMPTY:
			{
				cout << "[ " << GREEN << "\xb0" << RESET_COLOR << " ] ";
				break;
			}
			case ENEMY:
			{
				cout << "[ " << RED << "\x94" << RESET_COLOR << " ] ";
				break;
			}
			case TREASURE:
			{
				cout << "[ " << YELLOW << "$" << RESET_COLOR << " ] ";
				break;
			}
			case FOOD:
			{
				cout << "[ " << WHITE << "\xcf" << RESET_COLOR << " ] ";
				break;
			}
			case ENTRANCE:
			{
				cout << "[ " << WHITE << "\x9d" << RESET_COLOR << " ] ";
				break;
			}
			case EXIT:
			{
				cout << "[ " << WHITE << "\xFE" << RESET_COLOR << " ] ";
				break;
			}
			}
		}
		cout << "\n";
	}

	//Game loop
	while (!gameOver)
	{
		//Prepare screen for output
		//Move cursor to start of the 1st Q, then up 1, delete and insert 4 lines
		cout << RESTORE_CURSOR_POS << CSI << "A" << CSI << "4M" << CSI << "4L" << "\n";

		//Write description of current room
		switch (rooms[playerY][playerX])
		{
		case EMPTY:
			{
				cout << INDENT << "You are in an empty meadow. There is nothing of note here.\n";
				break;
			}
		case ENEMY:
			{
				cout << INDENT << "BEWARE. An enemy is approaching.\n";
				break;
			}
		case TREASURE:
			{
				cout << INDENT << "Your journey has been rewarded. You have found some treasure.\n";
				break;
			}
		case FOOD:
			{
				cout << INDENT << "At last! You collect some food to sustain you on your journey.\n";
				break;
			}
		case ENTRANCE:
			{
				cout << INDENT << "The entrance you used to enter this maze is blocked. There is no going back.\n";
				break;
			}
		case EXIT:
			{
				cout << INDENT << "Despite all odds, you made it to the exit. Congratulations.\n";
				gameOver = true;
				continue;
			}
		}

		//List the directions the player can take
		cout << INDENT << "You can see paths leading to the " <<
			((playerX > 0) ? "west (4), " : "") <<
			((playerX < MAZE_WIDTH - 1) ? "east (6), " : "") <<
			((playerY > 0) ? "north (8), " : "") <<
			((playerY < MAZE_HEIGHT - 1) ? "south (2), " : "") << "\n";

		cout << INDENT << "Where to now?";

		int x = INDENT_X + (6 * playerX) + 3;
		int y = MAP_Y + playerY;

		// draw the player's position on the map
		// move cursor to map pos and delete character at current position
		cout << CSI << y << ";" << x << "H";
		cout << MAGENTA << "\x81";
		// move cursor to position for player to enter input

		cout << CSI << PLAYER_INPUT_Y << ";" << PLAYER_INPUT_X << "H" << YELLOW;

		// clear the input buffer, ready for player input
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());

		int direction = 0;
		cin >> direction;
		cout << RESET_COLOR;

		if (cin.fail())
		{
			continue; // go back to the top of the game loop and ask again
		}

		//Before updating the player position, redraw the old room character over the old position
		cout << CSI << y << ";" << x << "H";
		switch (rooms[playerY][playerX])
		{
		case EMPTY:
			{
				cout << GREEN << "\xb0" << RESET_COLOR;
				break;
			}
		case ENEMY:
			{
				cout << RED << "\x94" << RESET_COLOR;
				break;
			}
		case TREASURE:
			{
				cout << YELLOW << "$" << RESET_COLOR;
				break;
			}
		case FOOD:
			{
				cout << WHITE << "\xcf" << RESET_COLOR;
				break;
			}
		case ENTRANCE:
		{
				cout << WHITE << "\x9d" << RESET_COLOR;
				break;
			}
		case EXIT:
			{
				cout << WHITE << "\xFE" << RESET_COLOR;
			}
		}

		switch (direction)
		{
		case EAST:
			{
				if (playerX < MAZE_WIDTH - 1)
					{
						playerX++;
					}
				break;
		}
		case WEST:
			{
				if (playerX > 0)
					{
						playerX--;
					}
				break;
			}
		case NORTH:
			{
				if (playerY > 0)
					{
						playerY--;
					}
				break;
			}
		case SOUTH:
			{
				if (playerY < MAZE_HEIGHT - 1)
					{
						playerY++;
					}
				break;
			}
		default:
			{
				//Do nothing, go back to the top of the loop and ask again
				break;
			}	
		}
	}
	//End of game loop

	cout << "\n" << INDENT << "Press 'Enter' to exit the program.\n";
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());
	cin.get();

	return;
}