#include "Powerup.h"
#include <string.h>

Powerup::Powerup(const char name[30], float health, float attack, float defence)
	: m_healthMultiplier( health ), m_attackMultiplier ( attack ), m_defenceMultiplier (defence)
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

bool Powerup::Compare(const Powerup& p1, const Powerup& p2)
{
	return (strcmp(p1.m_name, p2.m_name) < 0) ? true : false;
}