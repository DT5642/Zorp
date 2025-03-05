#include "Powerup.h"
#include <string.h>

Powerup::Powerup()
	: m_healthMultiplier{ 1 }, m_attackMultiplier{ 1 }, m_defenceMultiplier{ 1 }
{
	m_name[0] = 0;
}

Powerup::Powerup(const char name[30], float health, float attack, float defence)
{
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