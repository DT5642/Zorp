#pragma once
#include "GameDefines.h"
#include "Room.h"
#include "Player.h"

class GameDefines;

class Game
{
public:
	Game();
	~Game();

public:
	bool Startup();
	void Update();
	void Draw();

	bool IsGameOver();

private:
	bool EnableVirtualTerminal();
	void InitializeMap();

	void DrawWelcomMessage();
	void DrawMap();
	void DrawValidDirections();

	int GetCommand();

private:
	bool m_gameOver;
	Room m_map[MAZE_HEIGHT][MAZE_WIDTH];
	Player m_player;
};