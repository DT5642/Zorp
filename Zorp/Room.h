#pragma once
#include "Point2D.h"

class Powerup;
class Player;
class Enemy;
class Food;

class Room
{
public:
	Room();
	~Room();

	void SetPosition(Point2D position);
	void SetType(int type);
	void SetEnemy(Enemy* pEnemy);
	void SetPowerup(Powerup* pPowerup);
	void SetFood(Food* pFood);

	int GetType();
	Enemy* GetEnemy();
	Powerup* GetPowerup();
	Food* GetFood();

	void Draw();
	void DrawDescription();

private:
	Point2D m_mapPosition;
	int m_type;

	Powerup* m_powerup;
	Enemy* m_enemy;
	Food* m_food;
};