#pragma once
#include "Point2D.h"

class Enemy
{
public:
	Enemy();
	~Enemy();

	void SetPosition(const Point2D& position);
	void OnAttacked(int attackPoints);

	Point2D GetPosition();

	int GetHP();
	int GetAT();
	int GetDF();

	bool IsAlive();

private:
	Point2D m_mapPosition;

	int m_healthPoints;
	int m_attackPoints;
	int m_defendPoints;
};