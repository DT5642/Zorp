#include "Room.h"
#include "Food.h"
#include "Enemy.h"
#include "Player.h"
#include "Powerup.h"
#include "GameObject.h"
#include "GameDefines.h"
#include <iostream>
#include <algorithm>

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

void Room::AddGameObject(GameObject* object)
{
	m_objects.push_back(object);
	std::sort(m_objects.begin(), m_objects.end(), GameObject::Compare);
}

void Room::RemoveGameObject(GameObject* object)
{
	for (auto it = m_objects.begin(); it != m_objects.end(); it++)
	{
		if (*it == object)
		{
			//Reset the object's room number
			(*it)->SetPosition(Point2D{ -1, -1 });
			m_objects.erase(it);
			return;
		}
	}
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
			if (m_objects.size() > 0)
			{
				m_objects[0]->Draw();
			}
			else
			{
				cout << "[ " << GREEN << "\xb0" << RESET_COLOR << " ] ";
			}
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
			if (m_objects.size() > 0)
			{
				m_objects[0]->DrawDescription();
			}
			else
			{
				cout << INDENT << "You are in an empty meadow. There is nothing of note here.\n";
			}

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

void Room::LookAt()
{
	if (m_objects.size() > 0)
	{
		m_objects[0]->LookAt();
	}
	else
	{
		cout << EXTRA_OUTPUT_POS << RESET_COLOR << "You look around, but see nothing worth mentioning\n";
	}
}

Enemy* Room::GetEnemy()
{
	for (GameObject* pObj : m_objects)
	{
		Enemy* enemy = dynamic_cast<Enemy*>(pObj);

		if (enemy != nullptr)
		{
			return enemy;
		}
	}

	return nullptr;
}

Powerup* Room::GetPowerup()
{
	for (GameObject* pObj : m_objects)
	{
		Powerup* powerup = dynamic_cast<Powerup*>(pObj);

		if (powerup != nullptr)
		{
			return powerup;
		}
	}

	return nullptr;
}

Food* Room::GetFood()
{
	for (GameObject* pObj : m_objects)
	{
		Food* food = dynamic_cast<Food*>(pObj);

		if (food != nullptr)
		{
			return food;
		}
	}

	return nullptr;
}