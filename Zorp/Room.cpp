#include "Room.h"
#include "GameDefines.h"
#include "Powerup.h"
#include "Player.h"
#include <iostream>

using std::cout;
using std::cin;

static const char itemNames[15][30] =
{
	"indifference", "invisibility", "invulnerability", "incontinence", "improbability", "impatience", "indecision",
	"inspiration", "indepedence", "incurability", "integration", "invocation", "inferno", "indigestion", "inoculation"
};

Room::Room() : m_type{ EMPTY }, m_mapPosition{ 0, 0 }, m_powerup{ nullptr}
{
}

Room::~Room()
{
	if (m_powerup != nullptr)
	{
		delete m_powerup;
	}
}

void Room::SetPosition(Point2D position)
{
	m_mapPosition = position;
}

void Room::SetType(int type)
{
	m_type = type;

	if (!(m_type == TREASURE_HP || m_type == TREASURE_AT || m_type == TREASURE_DF))
	{
		return;
	}
	if (m_powerup != nullptr)
	{
		return;
	}

	int item = rand() % 15;
	char name[30] = "";

	float HP = 1;
	float AT = 1;
	float DF = 1;

	switch (type)
	{
	case TREASURE_HP:
		strcpy_s(name, "potion of ");
		HP = 1.1f;
		break;
	case TREASURE_AT:
		strcpy_s(name, "sword of ");
		AT = 1.1f;
		break;
	case TREASURE_DF:
		strcpy_s(name, "shield of ");
		DF = 1.1f;
		break;
	}

	strncat(name, itemNames[item], 30);
	m_powerup = new Powerup(name, HP, AT, DF);
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

bool Room::ExecuteCommand(int command, Player* pPlayer)
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
	case PICKUP:
	{
		return Pickup(pPlayer);
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

bool Room::Pickup(Player* pPlayer)
{
	if (m_powerup == nullptr)
	{
		cout << EXTRA_OUTPUT_POS << RESET_COLOR << "There is nothing here to pick up.\n";

		return true;
	}

	cout << EXTRA_OUTPUT_POS << RESET_COLOR << "You pick up the " << m_powerup->GetName() << "\n";

	//Add the powerup to the player's inventory 
	pPlayer->AddPowerup(m_powerup);

	//Remove the powerup from the room
	//(But don't delete it, the player owns it now)
	m_powerup = nullptr;

	//Change this room type to empty
	m_type = EMPTY;

	cout << INDENT << "Press 'Enter' to continue.";
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());
	cin.get();

	return true;
}