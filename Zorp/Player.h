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
	void Draw();
	void DrawDescription();
	void LookAt();

private:
	void Pickup(Room* pRoom);
	void Attack(Enemy* pEnemy);
};