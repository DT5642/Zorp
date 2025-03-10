#pragma once
#include "GameObject.h"
#include <vector>

class Powerup;

class Character : public GameObject
{
public:
	Character();
	Character(Point2D position, int health, int attack, int defend);
	~Character();

	void AddPowerup(Powerup* pPowerup);

	virtual void Draw() = 0;
	virtual void DrawDescription() = 0;
	virtual void LookAt() = 0;

	virtual void Save(std::ofstream& out);
	virtual bool Load(std::ifstream& in, const Game* game);

	int GetHP();
	int GetAT();
	int GetDF();

	bool IsAlive();

protected:
	std::vector<Powerup*> m_powerups;

	int m_healthPoints;
	int m_attackPoints;
	int m_defendPoints;
};