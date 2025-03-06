#include "Room.h"
#include "Food.h"
#include "Enemy.h"
#include "Player.h"
#include "Powerup.h"
#include "GameDefines.h"
#include <iostream>
#include <algorithm>

using std::cout;
using std::cin;

Player::Player() : Character({ 0, 0 }, 100, 20, 20)
{
	m_priority = PRIORITY_PLAYER;
}

Player::Player(int x, int y) : Character({ x, y }, 100, 20, 20)
{
}

Player::~Player()
{
}

void Player::ExecuteCommand(int command, Room* pRoom)
{
	switch (command)
	{
	case EAST:
	{
		if (m_mapPosition.x < MAZE_WIDTH - 1)
		{
			m_mapPosition.x++;
		}
		return;
	}
	case WEST:
	{
		if (m_mapPosition.x > 0)
		{
			m_mapPosition.x--;
		}
		return;
	}
	case NORTH:
	{
		if (m_mapPosition.y > 0)
		{
			m_mapPosition.y--;
		}
		return;
	}
	case SOUTH:
	{
		if (m_mapPosition.y < MAZE_HEIGHT - 1)
		{
			m_mapPosition.y++;
		}
		return;
	}
	case LOOK:
	{
		pRoom->LookAt();
		break;
	}
	case FIGHT:
	{
		Attack(pRoom->GetEnemy());
		break;
	}
	case PICKUP:
	{
		Pickup(pRoom);
		break;
	}
	case SAVE:
	{

	}
	case LOAD:
	{
		//Handle by the system before we get here.
		//No need to process these commands
		break;
	}
	default:
	{
		//The direction was not valid, do nothing, go back to the top of the loop and ask again
		cout << EXTRA_OUTPUT_POS << RESET_COLOR << "You try, but you just can't do it.\n";
	}
	}

	cout << INDENT << "Press 'Enter' to continue.";
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());
	cin.get();
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
	for (auto it = m_powerups.begin(); it < m_powerups.end(); it++) {
		cout << (*it)->GetName() << "\t";
	}
}

void Player::DrawDescription()
{

}

void Player::LookAt()
{
	cout << EXTRA_OUTPUT_POS << RESET_COLOR << "Hmm, I look good!\n";
}

void Player::Pickup(Room* pRoom)
{
	if (pRoom->GetPowerup() != nullptr)
	{
		Powerup* powerup = pRoom->GetPowerup();
		cout << EXTRA_OUTPUT_POS << RESET_COLOR << "You pick up the " << powerup->GetName() << "\n";
		//Add the powerup to the player's inventory
		AddPowerup(powerup);
		//Remove the powerup from the room (but don't delete it, the player owns it now)
		pRoom->RemoveGameObject(powerup);
	}
	else if (pRoom->GetFood() != nullptr)
	{
		Food* food = pRoom->GetFood();
		//Eat the food
		m_healthPoints += food->GetHP();
		cout << EXTRA_OUTPUT_POS << RESET_COLOR << "You feel refreshed. Your health is now " << m_healthPoints << "\n";
		//Remove the food from the room
		pRoom->RemoveGameObject(food);
	}
	else
	{
		cout << EXTRA_OUTPUT_POS << RESET_COLOR << "There is no one here you can fight with.\n";
	}
}

void Player::Attack(Enemy* pEnemy)
{
	if (pEnemy == nullptr)
	{
		cout << EXTRA_OUTPUT_POS << RESET_COLOR << "There is no one here you can fight with.\n";
	}
	else
	{
		pEnemy->OnAttacked(m_attackPoints);

		if (pEnemy->IsAlive() == false)
		{
			cout << EXTRA_OUTPUT_POS << RESET_COLOR << "You fight a grue adn kill it.\n";
		}
		else
		{
			int damage = pEnemy->GetAT() - m_defendPoints;

			if (damage < 0)
			{
				damage = 1 + rand() % 10;
			}

			m_healthPoints -= damage;

			cout << EXTRA_OUTPUT_POS << RESET_COLOR << "You fight a grue and take " << damage << " points damage. Your health is now at " << m_healthPoints << "\n";
			cout << INDENT << "The grue has " << pEnemy->GetHP() << " health remainging.\n";
		}
	}
}