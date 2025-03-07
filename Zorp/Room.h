#pragma once
#include "Point2D.h"
#include <vector>

class Food;
class Enemy;
class Powerup;
class GameObject;

class Room
{
public:
	Room();
	~Room();

	void SetPosition(Point2D position);
	void SetType(int type);

	void AddGameObject(GameObject* object);
	void RemoveGameObject(GameObject* object);
	void ClearGameObjects();

	int GetType();

	void Draw();
	void DrawDescription();
	void LookAt();

	Enemy* GetEnemy();
	Powerup* GetPowerup();
	Food* GetFood();

private:
	Point2D m_mapPosition;
	int m_type;

	std::vector<GameObject*>m_objects;
};