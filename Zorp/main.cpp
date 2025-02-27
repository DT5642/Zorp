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
const int MOVEMENT_DESC_Y = 9;
const int MAP_Y = 13;
const int PLAYER_INPUT_X = 30;
const int PLAYER_INPUT_Y = 11;

const int WEST = 4;
const int EAST = 6;
const int NORTH = 8;
const int SOUTH = 2;

bool EnableVirtualTerminal();
void Initialize(int map[MAZE_HEIGHT][MAZE_WIDTH]);
void DrawWelcomeMessage();
void DrawRoom(int map[MAZE_HEIGHT][MAZE_WIDTH], int x, int y);
void DrawMap(int map[MAZE_HEIGHT][MAZE_WIDTH]);
void DrawRoomDescription(int roomType);
void DrawPlayer(int x, int y);
void DrawValidDirections(int x, int y);

void main()
{
	//Create 2D array
	int rooms[MAZE_HEIGHT][MAZE_WIDTH];

	bool gameOver = false;
	int playerX = 0;
	int playerY = 0;

	if (EnableVirtualTerminal() == false)
	{
		cout << "The virtual terminal processing mode could not be activated.\n";
		cout << "Press 'Enter' to exit.\n";
		cin.get();
		return;
	}

	Initialize(rooms);

	DrawWelcomeMessage();
	cin.get();

	//Output map
	DrawMap(rooms);

	//Game loop
	while (!gameOver)
	{
		DrawRoomDescription(rooms[playerY][playerX]);

		DrawPlayer(playerX, playerY);

		if (rooms[playerY][playerX] == EXIT)
		{
			gameOver = true;
			continue;
		}

		//List the directions the player can take
		DrawValidDirections(playerX, playerY);
		int direction = GetMovementDirection();

		//Before updating the player position, redraw the old room
		//Character over the old position

		DrawRoom(rooms, playerX, playerY);

		//Update the player's position using the input movement data
		switch (direction)
		{
		case EAST:
			{
				if (playerX < MAZE_WIDTH - 1)
				{
					playerX++;
					break;
				}
			}
		case WEST:
			{
				if (playerX > 0)
				{
					playerX--;
					break;
				}
			}
		case NORTH:
			{
				if (playerY > 0)
				{
					playerY--;
					break;
				}
			}
		case SOUTH:
			{
				if (playerY < MAZE_HEIGHT - 1)
				{
					playerY++;
					break;
				}
			}
		default:
			{
				//The direction was not valid,
				//Do nothing, go back to the top of the loop and ask again
				break;
			}
		}
	}
	//End of game loop

	cout << CSI << PLAYER_INPUT_Y << ";" << 0 << "H";
	cout << "\n" << INDENT << "Press 'Enter' to exit the program.\n";
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());
	cin.get();

	return;
}

bool EnableVirtualTerminal()
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

void Initialize(int map[MAZE_HEIGHT][MAZE_WIDTH])
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
				map[y][x] = type;
			}
			else
			{
				map[y][x] = EMPTY;
			}
		}
	}

	//Set the entrance and exit of the maze
	map[0][0] = ENTRANCE;
	map[MAZE_HEIGHT - 1][MAZE_WIDTH - 1] = EXIT;
}

void DrawWelcomeMessage()
{
	cout << TITLE << MAGENTA << "Welcome to Zorp!\n" << RESET_COLOR;
	cout << INDENT << "Zorp is a game of adventure, danger, and low cunning.\n";
	cout << INDENT << "It is definitely not related to any other text-based adventure game...\n\n";
}

void DrawRoom(int map[MAZE_HEIGHT][MAZE_WIDTH], int x, int y)
{
	//Find the console output position
	int outX = INDENT_X + (6 * x) + 1;
	int outY = MAP_Y + y;

	//Jump to the correct loction
	cout << CSI << outY << ";" << outX << "H";

	//Draw the room
	switch (map[y][x])
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

void DrawMap(int map[MAZE_HEIGHT][MAZE_WIDTH])
{
	//Reset draw colours
	cout << RESET_COLOR;

	for (int y = 0; y < MAZE_HEIGHT; y++)
	{
		cout << INDENT;
		for (int x = 0; x < MAZE_WIDTH; x++)
		{
			DrawRoom(map, x, y);
		}
		cout << "\n";
	}
}

void DrawRoomDescription(int roomType)
{
	//Reset draw colours
	cout << RESET_COLOR;

	//Jump to the correct location
	cout << CSI << ROOM_DESC_Y << ";" << 0 << "H";

	//Delete 4 lines and insert 4 empty lines
	cout << CSI << "4M" << CSI << "4L\n";

	//Write description of current room
	switch (roomType)
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
			break;
		}
	}
}

void DrawPlayer(int x, int y)
{
	x = INDENT_X + (6 * x) + 3;
	y = MAP_Y + y;

	//Draw the player's position on the map
	//Move cursor to map pos and delete character at current position
	cout << CSI << y << ";" << x << "H";
	cout << MAGENTA << "\x81" << RESET_COLOR;
}

void DrawValidDirections(int x, int y)
{
	//Reset draw colours
	cout << RESET_COLOR;

	//Jump to the correct location
	cout << CSI << MOVEMENT_DESC_Y + 1 << ";" << 0 << "H";
	cout << INDENT << "You can see paths leading to the " <<
		((x > 0) ? "west, " : "") <<
		((x < MAZE_WIDTH - 1) ? "east, " : "") <<
		((y > 0) ? "north, " : "") <<
		((y < MAZE_HEIGHT - 1) ? "south, " : "") << "\n";
}

int GetMovementDirection()
{
	//Jump to the correct location
	cout << CSI << PLAYER_INPUT_Y << ";" << 0 << "H";
	cout << INDENT << "Where to now?";

	int direction;

	//Move cursor to position for player to enter input
	cout << CSI << PLAYER_INPUT_Y << ";" << PLAYER_INPUT_X << "H" << YELLOW;

	//Clear the input buffer, ready for player input
	cin.get();
	cin.ignore(cin.rdbuf()->in_avail());

	cin >> direction;
	cout << RESET_COLOR;

	if (cin.fail())
	{
		return 0;
	}

	return direction;
}