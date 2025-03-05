#pragma once
#include "Point2D.h"
#include <vector>

class Room;
class Enemy;
class Powerup;

class Player
{
public:
	Player();
	Player(int x, int y);
	~Player();

	void AddPowerup(Powerup* pPowerup);
	void SetPosition(const Point2D& position);

	Point2D GetPosition();

	void ExecuteCommand(int command, Room* pRoom);
	void Draw();

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