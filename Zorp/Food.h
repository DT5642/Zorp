#pragma once
#include "GameObject.h"

class Food : public GameObject
{
public:
	Food();
	Food(Point2D position);
	~Food();

	int GetHP();

	virtual void Save(std::ofstream& out);
	virtual bool Load(std::ifstream& in, const Game* game);
	void Draw();
	void DrawDescription();
	void LookAt();

private:
	int m_healthPoints;
};