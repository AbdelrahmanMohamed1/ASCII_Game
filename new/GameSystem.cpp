#include "GameSystem.h"
#include<fstream>
#include<iostream>
#include<conio.h>


// constructor sets up the game
GameSystem::GameSystem(string levelfilename)
{
	_player.init(1, 100, 10, 10, 0);

	_lvl.loadlevel(levelfilename,_player);

	system("PAUSE");
}

void GameSystem::PlayGame()
{
	bool done = 1;
	while (done)
	{
		_lvl.print();
		playermove();
		_lvl.uppdateEnemies(_player);
	}
}

void GameSystem::playermove()
{
	char input;
	cout << "Enter a move command: (w/s/a/d): ";
	input = _getch();
	
	_lvl.moveplayer(input,_player);
}

