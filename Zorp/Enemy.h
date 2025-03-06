#pragma once
#include "Character.h"

class Enemy : public Character
{
public:
	Enemy();
	~Enemy();

	void OnAttacked(int attackPoints);

	void Draw();
	void DrawDescription();
	void LookAt();
};