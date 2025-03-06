#pragma once
#include "GameObject.h"
#include <fstream>

class Food : public GameObject
{
public:
	Food();
	Food(Point2D position);
	~Food();

	int GetHP();

	void Save(std::ofstream& out);
	void Draw();
	void DrawDescription();
	void LookAt();

private:
	int m_healthPoints;
};