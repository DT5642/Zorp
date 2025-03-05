#pragma once

class Powerup
{
public:
	Powerup(const char name[30], float health, float attack, float defence);
	~Powerup();

	char* GetName();
	float GetHealthMultiplier();
	float GetAttackMultiplier();
	float GetDefenceMultiplier();

	static bool Compare(const Powerup* p1, const Powerup* p2);

private:
	char m_name[30];

	float m_healthMultiplier;
	float m_attackMultiplier;
	float m_defenceMultiplier;
};