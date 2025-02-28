#include "Room.h"
#include "GameDefines.h"
#include <iostream>

using std::cout;
using std::cin;

Room::Room() : m_type{ EMPTY }, m_mapPosition{ 0, 0 }
{
}

Room::~Room()
{
}

void Room::SetPosition(Point2D position)
{
	m_mapPosition = position;
}

void Room::SetType(int type)
{
	m_type = type;
}

int Room::GetType()
{
	return m_type;
}

void Room::Draw()
{
	//Find the console output position
	int outX = INDENT_X + (6 * m_mapPosition.x) + 1;
	int outY = MAP_Y + m_mapPosition.y;

	//Jump to the correct loction
	cout << CSI << outY << ";" << outX << "H";

	//Draw the room
	switch (m_type)
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
		case TREASURE_HP:
		case TREASURE_AT:
		case TREASURE_DF:
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

void Room::DrawDescription()
{
	//Reset draw colours
	cout << RESET_COLOR;

	//Jump to the correct location
	cout << CSI << ROOM_DESC_Y << ";" << 0 << "H";

	//Delete 4 lines and insert 4 empty lines
	cout << CSI << "4M" << CSI << "4L\n";

	//Write description of current room
	switch (m_type)
	{
		case EMPTY:
		{
			cout << INDENT << "You are in an empty meadow. There is nothing of note here.\n";
			break;
		}
		case ENEMY:
		{
			cout << INDENT << RED << "BEWARE." << RESET_COLOR << "An enemy is approaching.\n";
			break;
		}
		case TREASURE_HP:
		case TREASURE_AT:
		case TREASURE_DF:
		{
			cout << INDENT << "There appears to be some treasure here. Perhaps you should investigate futher.\n";
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

bool Room::ExecuteCommand(int command)
{
	cout << EXTRA_OUTPUT_POS;
	switch (command)
	{
	case LOOK:
	{
		if (m_type == TREASURE_HP || m_type == TREASURE_AT || m_type == TREASURE_DF)
		{
			cout << EXTRA_OUTPUT_POS << RESET_COLOR << "There is some treasure here. It looks small enough to pick up.\n";
		}
		else
		{
			cout << EXTRA_OUTPUT_POS << RESET_COLOR << "You look around, but see nothing worth mentioning\n";
		}

		cout << INDENT << "Press 'Enter' to continue.";
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cin.get();
		return true;
	}
	case FIGHT:
	{
		cout << EXTRA_OUTPUT_POS << RESET_COLOR << "You look around, but see nothing worth mentioning\n";
		cout << INDENT << "Press 'Enter' to continue";
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cin.get();
		return true;
	}
	default:
	{
		cout << EXTRA_OUTPUT_POS << RESET_COLOR << "You try, but you just can't do it.\n";
		cout << INDENT << "Press 'Enter' to continue.";
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cin.get();
		break;
	}
	}
	return false;
}