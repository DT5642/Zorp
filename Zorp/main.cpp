#include <iostream>
#include <Windows.h>
#include <random>
#include <time.h>
#include "Point2D.h"
#include "GameDefines.h"

using std::cout;
using std::cin;

//Functions
void Initialize(int map[MAZE_HEIGHT][MAZE_WIDTH]);
void DrawWelcomeMessage();
void DrawRoom(int map[MAZE_HEIGHT][MAZE_WIDTH], Point2D position);
void DrawMap(int map[MAZE_HEIGHT][MAZE_WIDTH]);
void DrawRoomDescription(int roomType);
void DrawPlayer( Point2D position);
void DrawValidDirections(Point2D position);
bool EnableVirtualTerminal();
int GetCommand();

void main()
{
	//Create 2D array
	int rooms[MAZE_HEIGHT][MAZE_WIDTH];

	bool gameOver = false;

	Point2D player = { 0, 0 };

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
		DrawRoomDescription(rooms[player.y][player.x]);

		DrawPlayer(player);

		if (rooms[player.y][player.x] == EXIT)
		{
			gameOver = true;
			continue;
		}

		//List the directions the player can take
		DrawValidDirections(player);
		int command = GetCommand();

		//Before updating the player position, redraw the old room
		//Character over the old position

		DrawRoom(rooms, player);

		//Update the player's position using the input movement data
		switch (command)
		{
		case EAST:
		{
		if (player.x < MAZE_WIDTH - 1)
		{
			player.x++;
			break;
		}
		}
		case WEST:
		{
		if (player.x > 0)
		{
			player.x--;
			break;
		}
		}
		case NORTH:
		{
		if (player.y > 0)
		{
			player.y--;
			break;
		}
		}
		case SOUTH:
		{
		if (player.y < MAZE_HEIGHT - 1)
		{
			player.y++;
			break;
		}
		}
		case LOOK:
		{
			DrawPlayer(player);
			cout << EXTRA_OUTPUT_POS << RESET_COLOR << "You look around, but see nothing worth mentioning\n";
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			cin.get();
			break;
		}
		case FIGHT:
		{
			DrawPlayer(player);
			cout << EXTRA_OUTPUT_POS << RESET_COLOR << "You could try to fight, but you don't have a weapon\n";
			cout << INDENT << "Press 'Enter' to continue.";
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			cin.get();
			break;
		}
		default:
		{
			//The direction was not valid,
			//Do nothing, go back to the top of the loop and ask again
			DrawPlayer(player);
			cout << EXTRA_OUTPUT_POS << RESET_COLOR << "You try, but you just can't do it.\n";
			cout << INDENT << "Press 'Enter' to continue.";
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail());
			cin.get();
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

void DrawRoom(int map[MAZE_HEIGHT][MAZE_WIDTH], Point2D position)
{
	//Find the console output position
	int outX = INDENT_X + (6 * position.x) + 1;
	int outY = MAP_Y + position.y;

	//Jump to the correct loction
	cout << CSI << outY << ";" << outX << "H";

	//Draw the room
	switch (map[position.y][position.x])
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
	Point2D position = { 0, 0 };

	//Reset draw colours
	cout << RESET_COLOR;

	for (position.y = 0; position.y < MAZE_HEIGHT; position.y++)
	{
		cout << INDENT;
		for (position.x = 0; position.x < MAZE_WIDTH; position.x++)
		{
			DrawRoom(map, position);
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

void DrawPlayer( Point2D position)
{
	Point2D outPos =
	{
		INDENT_X + (6 * position.x) + 3,
		MAP_Y + position.y
	};

	//Draw the player's position on the map
	//Move cursor to map pos and delete character at current position
	cout << CSI << outPos.y << ";" << outPos.x << "H";
	cout << MAGENTA << "\x81" << RESET_COLOR;
}

void DrawValidDirections(Point2D position)
{
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

int GetCommand()
{
	//For now, we can't read commands longer than 50 characters
	char input[50] = "\0";

	//Jump to the correct location
	cout << CSI << PLAYER_INPUT_Y << ";" << 0 << "H";
	//Clear any existing text
	cout << CSI << "4M";

	cout << INDENT << "Enter a command.";
	//Move cursor to position for player to enter input
	cout << CSI << PLAYER_INPUT_Y << ";" << PLAYER_INPUT_X << "H" << YELLOW;

	//Clear the input buffer, ready for player input
	cin.get();
	cin.ignore(cin.rdbuf()->in_avail());

	cin >> input;
	cout << RESET_COLOR;

	bool bMove = false;

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

		char next = cin.peek();

		if (next == '\n' || next == EOF)
		{
			break;
		}
		cin >> input;
	}
	return 0;
}