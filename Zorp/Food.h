#pragma once
#include "GameObject.h"

class Food : public GameObject
{
public:
	Food();
	Food(Point2D position);
	~Food();

	int GetHP();

	void Draw();
	void DrawDescription();
	void LookAt();

private:
	int m_healthPoints;
};