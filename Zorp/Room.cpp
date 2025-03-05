#include "Room.h"
#include "Food.h"
#include "Player.h"
#include "Powerup.h"
#include "GameDefines.h"
#include <iostream>

using std::cout;
using std::cin;

Room::Room() : m_type{ EMPTY }, m_mapPosition{ 0, 0 }, m_powerup{ nullptr }, m_enemy{ nullptr }, m_food{ nullptr }
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

void Room::SetEnemy(Enemy* pEnemy)
{
	m_enemy = pEnemy;
}

void Room::SetPowerup(Powerup* pPowerup)
{
	m_powerup = pPowerup;
}

void Room::SetFood(Food* pFood)
{
	m_food = pFood;
}

int Room::GetType()
{
	return m_type;
}

Enemy* Room::GetEnemy()
{
	return m_enemy;
}

Powerup* Room::GetPowerup()
{
	return m_powerup;
}

Food* Room::GetFood()
{
	return m_food;
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
			if (m_enemy != nullptr)
			{
				cout << "[ " << RED << "\x94" << RESET_COLOR << " ] ";
				break;
			}
			if (m_powerup != nullptr)
			{
				cout << "[ " << YELLOW << "$" << RESET_COLOR << " ] ";
				break;
			}
			if (m_food != nullptr)
			{
				cout << "[ " << WHITE << "\xcf" << RESET_COLOR << " ] ";
				break;
			}

			cout << "[ " << GREEN << "\xb0" << RESET_COLOR << " ] ";
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
			if (m_enemy != nullptr)
			{
				cout << INDENT << RED << "BEWARE." << RESET_COLOR << "An enemy is approaching.\n";
				break;
			}
			if (m_powerup != nullptr)
			{
				cout << INDENT << "There appears to be some treasure here. Perhaps you should investigate futher.\n";
				break;
			}
			if (m_food != nullptr)
			{
				cout << INDENT << "At last! You collect some food to sustain you on your journey.\n";
				break;
			}

			cout << INDENT << "You are in an empty meadow. There is nothing of note here.\n";
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