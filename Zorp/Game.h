#pragma once
#include "Room.h"
#include "Player.h"
#include "GameDefines.h"

class Food;
class Enemy;
class Powerup;

class Game
{
public:
	Game();
	~Game();

public:
	bool Startup();
	void Update();
	void Draw();
	void Save();
	bool Load();

	bool IsGameOver();

private:
	bool EnableVirtualTerminal();
	void InitialiseMap();
	void InitialiseEnemies();
	void InitialisePowerups();
	void InitialiseFood();

	void DrawWelcomMessage();
	void DrawMap();
	void DrawValidDirections();

	int GetCommand();

private:
	bool m_gameOver;
	Room m_map[MAZE_HEIGHT][MAZE_WIDTH];

	int m_enemyCount;
	Enemy* m_enemies;

	int m_foodCount;
	Food* m_food;

	int m_powerupCount;
	Powerup* m_powerups;

	//A place to store temporary powerups during loading
	int m_tempPowerupCount;
	Powerup* m_tempPowerups;

	Player m_player;
};