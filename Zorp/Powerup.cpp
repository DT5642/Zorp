#include "Powerup.h"
#include "GameDefines.h"
#include <fstream>
#include <string>
#include <cstring>
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
	return m_name;
}

float Powerup::GetHealthMultiplier()
{
	return m_healthMultiplier;
}

float Powerup::GetAttackMultiplier()
{
	return m_attackMultiplier;
}

float Powerup::GetDefenceMultiplier()
{
	return m_defenceMultiplier;
}

void Powerup::Save(std::ofstream& out)
{
	if (!out.is_open())
	{
		return;
	}

	out << m_priority << ",";
	out << m_mapPosition.x << ",";
	out << m_mapPosition.y << ",";
	out << m_name << ",";
	out << m_healthMultiplier << ",";
	out << m_attackMultiplier << ",";
	out << m_defenceMultiplier << "\n";
}

bool Powerup::Load(std::ifstream& in, const Game* game)
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
	strcpy_s(m_name, buffer);

	in.ignore(1);
	in.get(buffer, 50, ',');
	if (in.rdstate() || buffer[0] == 0)
	{
		return false;
	}
	m_healthMultiplier = std::stof(buffer);	//These values are floats, so use stof()

	in.ignore(1);
	in.get(buffer, 50, ',');
	if (in.rdstate() || buffer[0] == 0)
	{
		return false;
	}
	m_attackMultiplier = std::stof(buffer);

	in.ignore(1);
	in.getline(buffer, 50);
	if (in.rdstate() || buffer[0] == 0)
	{
		return false;
	}
	m_defenceMultiplier = std::stof(buffer);

	return true;
}

void Powerup::SetName(const char* pStr)
{
	strncpy_s(m_name, pStr, 30);
}

void Powerup::SetHealthMultiplier(float health)
{
	m_healthMultiplier = health;
}

void Powerup::SetAttackMultiplier(float attack)
{
	m_healthMultiplier = attack;
}

void Powerup::SetDefenceMultiplier(float defence)
{
	m_defenceMultiplier = defence;
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