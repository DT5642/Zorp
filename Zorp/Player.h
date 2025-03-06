#pragma once
#include "Character.h"
#include <vector>

class Room;
class Enemy;
class Powerup;

class Player : public Character
{
public:
	Player();
	Player(int x, int y);
	~Player();

	void ExecuteCommand(int command, Room* pRoom);
	void Draw() override;
	void DrawDescription() override;
	void LookAt() override;

private:
	void Pickup(Room* pRoom);
	void Attack(Enemy* pEnemy);

private:
	Point2D m_mapPosition;

	std::vector<Powerup*> m_powerups;

	int m_healthPoints;
	int m_attackPoints;
	int m_defendPoints;
};