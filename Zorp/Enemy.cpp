#include "Enemy.h"

Enemy::Enemy() 
	: m_healthPoints{ 20 }, m_attackPoints{ 10 }, m_defendPoints{ 5 }
{
}

Enemy::~Enemy()
{
}

void Enemy::SetPosition(const Point2D& position)
{
	m_mapPosition = position;
}

void Enemy::OnAttacked(int attackPoints)
{
	m_healthPoints -= attackPoints - m_defendPoints;

	if (m_healthPoints < 0)
	{
		m_healthPoints = 0;
	}
}

Point2D Enemy::GetPosition()
{
	return m_mapPosition;
};

int Enemy::GetHP()
{
	return m_healthPoints;
}

int Enemy::GetAT()
{
	return m_attackPoints;
}

int Enemy::GetDF()
{
	return m_defendPoints;
}

bool Enemy::IsAlive()
{
	return (m_healthPoints > 0);
}