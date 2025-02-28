#include "Player.h"
#include "GameDefines.h"
#include <iostream>

using std::cout;
using std::cin;

Player::Player() : m_mapPosition{ 0, 0 }, m_healthPoints{ 100 }, m_attackPoints{ 20 }, m_defendPoints{ 20 }
{
}

Player::Player(int x, int y) : m_mapPosition{ x, y }, m_healthPoints{ 100 }, m_attackPoints{ 20 }, m_defendPoints{ 20 }
{
}

Player::~Player()
{
}

void Player::SetPosition(Point2D position)
{
	m_mapPosition = position;
}

Point2D Player::GetPosition()
{
	return m_mapPosition;
}

void Player::Draw()
{
	Point2D outPos =
	{
		INDENT_X + (6 * m_mapPosition.x) + 3,
		MAP_Y + m_mapPosition.y
	};

	//Draw the player's position on the map
	//Move the cursor to the map pos and delete character at current position
	cout << CSI << outPos.y << ";" << outPos.x << "H";
	cout << MAGENTA << "\x81" << RESET_COLOR;

	cout << INVENTORY_OUTPUT_POS;
	for (auto it = m_powerups.begin(); it < m_powerups.end(); it++)
	{
		cout << (*it).GetName() << "\t";
	}
}

bool Player::ExecuteCommand(int command, int roomType)
{
	switch (command)
	{
	case EAST:
	{
		if (m_mapPosition.x < MAZE_WIDTH - 1)
		{
			m_mapPosition.x++;
		}
		return true;
	}
	case WEST:
	{
		if (m_mapPosition.x > 0)
		{
			m_mapPosition.x--;
		}
		return true;
	}
	case NORTH:
	{
		if (m_mapPosition.y > 0)
		{
			m_mapPosition.y--;
		}
		return true;
	}
	case SOUTH:
	{
		if (m_mapPosition.y < MAZE_HEIGHT - 1)
		{
			m_mapPosition.y++;
		}
		return true;
	}
	case PICKUP:
	{
		return Pickup(roomType);
	}
	}
	return false;
}

bool Player::Pickup(int roomType)
{
	static const char itemNames[15][30] =
	{
		"indifference", "invisibility", "invulnerability", "incontinence", "improbability", "impatience", "indecision",
		"inspiration", "indepedence", "incurability", "integration", "invocation", "inferno", "indigestion", "inoculation"
	};

	int item = rand() % 15;
	char name[30] = "";

	switch (roomType)
	{
	case TREASURE_HP:
		strcpy_s(name, "potion of ");
		break;
	case TREASURE_AT:
		strcpy_s(name, "sword of ");
		break;
	case TREASURE_DF:
		strcpy_s(name, "shield of ");
		break;
	default:
		return false;
	}

	//Appaend the item name to the string
	strncat_s(name, itemNames[item], 30);
	cout << EXTRA_OUTPUT_POS << RESET_COLOR << "You pick up the " << name << "\n";
	m_powerups.push_back(Powerup(name, 1, 1, 1.1f));

	std::sort (m_powerups.begin(), m_powerups.end(), Powerup::compare);

	cout << INDENT << "Press 'Enter' to continue.";
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());
	cin.get();

	return true;
}