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