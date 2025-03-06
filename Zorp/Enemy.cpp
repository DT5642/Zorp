#include "Enemy.h"
#include "GameDefines.h"
#include <iostream>

using std::cout;
using std::cin;

Enemy::Enemy() : Character({ 0,0 }, 20, 10, 5)
{
	m_priority = PRIORITY_ENEMY;
}

Enemy::~Enemy()
{
}

void Enemy::OnAttacked(int attackPoints)
{
	m_healthPoints -= attackPoints - m_defendPoints;

	if (m_healthPoints < 0)
	{
		m_healthPoints = 0;
	}
}

void Enemy::Draw()
{
	cout << "[ " << RED << "\x94" << RESET_COLOR << " ]";
}

void Enemy::DrawDescription()
{
	cout << INDENT << RED << "BEWARE." << RESET_COLOR << " An enemy is approaching.\n";
}

void Enemy::LookAt()
{
	cout << EXTRA_OUTPUT_POS << RESET_COLOR << "LOOK OUT! An enemy is approaching.\n";
}