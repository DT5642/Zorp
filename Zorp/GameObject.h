#pragma once
#include "Point2D.h"
#include <fstream>

class Game;

class GameObject
{
public:
	GameObject();
	GameObject(Point2D position);
	~GameObject();

	Point2D GetPosition();
	void SetPosition(const Point2D& position);

	virtual void Draw() = 0;
	virtual void DrawDescription() = 0;
	virtual void LookAt() = 0;

	static bool Compare(const GameObject* p1, const GameObject* p2);

	virtual void Save(std::ofstream& out) = 0;
	virtual bool Load(std::ifstream& in, const Game* game) = 0;

protected:
	Point2D m_mapPosition;
	int m_priority;
};