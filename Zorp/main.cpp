#include "Game.h"
#include <iostream>

using std::cout;
using std::cin;

void main()
{
	Game game;

	if (game.Startup() == false)
	{
		return;
	}

	//Game loop
	while (!game.IsGameOver())
	{
		game.Draw();

		game.Update();
	} //End game loop

	//Jump to the correct location
	cout << CSI << PLAYER_INPUT_Y << ";" << 0 << "H";
	cout << "\n" << INDENT << "Press 'Enter' to exit program.";
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());
	cin.get();
}