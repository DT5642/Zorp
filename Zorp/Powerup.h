#pragma once
#include "GameObject.h"

class Powerup : public GameObject
{
public:
	Powerup();
	Powerup(const char name[30], float health, float attack, float defence);
	~Powerup();

	char* GetName();
	float GetHealthMultiplier();
	float GetAttackMultiplier();
	float GetDefenceMultiplier();

	void SetName(const char* pStr);
	void SetHealthMultiplier(float health);
	void SetAttackMultiplier(float attack);
	void SetDefenceMultiplier(float defence);

	static bool Compare(const Powerup* p1, const Powerup* p2);

	void Draw();
	void DrawDescription();
	void LookAt();

private:
	char m_name[30];

	float m_healthMultiplier;
	float m_attackMultiplier;
	float m_defenceMultiplier;
};