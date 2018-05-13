#pragma once
#include"Player.h"
#include"Level.h"
#include"Enemy.h"
#include<string>

using namespace std;
class GameSystem
{
public:
	GameSystem(string levelfilename);

	void PlayGame();
	void playermove();
private:
	Player _player;
	Level _lvl;
	
};

