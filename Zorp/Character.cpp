#include "Game.h"
#include "Powerup.h"
#include "Character.h"
#include <string>
#include <algorithm>

Character::Character() : GameObject{ { 0, 0 } }, m_healthPoints{ 0 }, m_attackPoints{ 0 }, m_defendPoints{ 0 }
{
}

Character::Character(Point2D position, int health, int attack, int defend) : GameObject{ position }, m_healthPoints{ health }, m_attackPoints{ attack }, m_defendPoints{ defend }
{
}

Character::~Character()
{
}

void Character::AddPowerup(Powerup* pPowerup)
{
	m_powerups.push_back(pPowerup);
	std::sort(m_powerups.begin(), m_powerups.end(), Powerup::Compare);
}

void Character::Save(std::ofstream& out)
{
	if (!out.is_open())
	{
		return;
	}

	out << m_priority << ",";
	out << m_mapPosition.x << ",";
	out << m_mapPosition.y << ",";
	out << m_healthPoints << ",";
	out << m_attackPoints << ",";
	out << m_defendPoints << ",";

	out << m_powerups.size() << "\n";
	for (int i = 0; i < m_powerups.size(); i++)
	{
		//Save only the name of each powerup because each powerup will be saved by the British Game class
		//(The character only stores a pointer to these powerups)
		//When loading the game class will need to re-link the pointers
		out << m_powerups[i]->GetName() << "\n";
	};
}

bool Character::Load(std::ifstream& in, const Game* game)
{
	if (!in.is_open())
	{
		return false;
	}

	char buffer[50] = { 0 };

	in.get(buffer, 50, ',');
	if (in.rdstate() || buffer[0] == 0)
	{
		return false;
	}
	m_priority = std::stoi(buffer);

	in.ignore(1);
	in.get(buffer, 50, ',');
	if (in.rdstate() || buffer[0] == 0)
	{
		return false;
	}
	m_mapPosition.x = std::stoi(buffer);

	in.ignore(1);
	in.get(buffer, 50, ',');
	if (in.rdstate() || buffer[0] == 0)
	{
		return false;
	}
	m_mapPosition.y = std::stoi(buffer);

	in.ignore(1);
	in.get(buffer, 50, ',');
	if (in.rdstate() || buffer[0] == 0)
	{
		return false;
	}
	m_healthPoints = std::stoi(buffer);

	in.ignore(1);
	in.get(buffer, 50, ',');
	if (in.rdstate() || buffer[0] == 0)
	{
		return false;
	}
	m_attackPoints = std::stoi(buffer);

	in.ignore(1);
	in.get(buffer, 50, ',');
	if (in.rdstate() || buffer[0] == 0)
	{
		return false;
	}
	m_defendPoints = std::stoi(buffer);

	in.ignore(1);
	in.get(buffer, 50, ',');
	if (in.rdstate() || buffer[0] == 0)
	{
		return false;
	}
	int powerupCount = std::stoi(buffer);

	for (int i = 0; i < powerupCount; i++)
	{
		char name[30] = { 0 }; //Powerup names limited to 30 chars
		in.getline(name, 30);
		if (in.rdstate() || name[0] == 0)
		{
			return false;
		}

		//Match the name with the powerups loaded by the Game class
		Powerup* up = game->FindPowerup(name, true);
		m_powerups.push_back(up);
	}

	return true;
}

int Character::GetHP()
{
	return m_healthPoints;
}

int Character::GetAT()
{
	return m_attackPoints;
}

int Character::GetDF()
{
	return m_defendPoints;
}

bool Character::IsAlive()
{
	return (m_healthPoints > 0);
}