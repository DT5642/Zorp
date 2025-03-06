#include "Powerup.h"
#include "Character.h"
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

int Character::GetHP()
{
	return m_healthPoints;;
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