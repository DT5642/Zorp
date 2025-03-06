#include "Powerup.h"
#include "GameDefines.h"
#include <string.h>
#include <iostream>

using std::cout;
using std::cin;

Powerup::Powerup() : m_healthMultiplier{ 1 }, m_attackMultiplier{ 1 }, m_defenceMultiplier{ 1 }
{
	m_priority = PRIORITY_POWERUP;
	m_name[0] = 0;
}

Powerup::Powerup(const char name[30], float health, float attack, float defence) : m_healthMultiplier{ health }, m_attackMultiplier{ attack }, m_defenceMultiplier{ defence }
{
	m_priority = PRIORITY_POWERUP;
	strcpy_s(m_name, name);
}

Powerup::~Powerup()
{
}

char* Powerup::GetName()
{
	return nullptr;
}

float Powerup::GetHealthMultiplier()
{
	return 0.0f;
}

float Powerup::GetAttackMultiplier()
{
	return 0.0f;
}

float Powerup::GetDefenceMultiplier()
{
	return 0.0f;
}

void Powerup::SetName(const char* pStr)
{
	strncpy_s(m_name, pStr, 30);
}

void Powerup::SetHealthMultiplier(float health)
{

}

void Powerup::SetAttackMultiplier(float attack)
{

}

void Powerup::SetDefenceMultiplier(float defence)
{

}

bool Powerup::Compare(const Powerup* p1, const Powerup* p2)
{
	return (strcmp(p1->m_name, p2->m_name) < 0) ? true : false;
}

void Powerup::Draw()
{
	cout << "[ " << YELLOW << "$" << RESET_COLOR << " ] ";
}

void Powerup::DrawDescription()
{
	cout << INDENT << "There appears to be some treasure here. Perhaps you should investigate further.\n";
}

void Powerup::LookAt()
{
	cout << EXTRA_OUTPUT_POS << RESET_COLOR << "There is some treasure here. It looks small enough to pick up.\n";
}