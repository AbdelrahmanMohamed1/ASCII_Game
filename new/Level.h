#pragma once
#include<string>
#include<vector>
#include"Player.h"
#include"Enemy.h"

using namespace std;
class Level
{
public:
	Level();
	void loadlevel(string filename,Player &player);
	void print();

	void moveplayer(char input, Player &player);
	void uppdateEnemies(Player &player);

	// getter
	char get_tile(int x, int y);
	// setter
	void set_tile(int x,int y,char tile);


private:
	vector<string> _leveldata;
	vector<Enemy> _enemies;

	void processplayermove(Player &player, int targetx, int targety);
	void processEnemymove(Player &player, int enemyindex, int targetx, int targety);

	void battle_monster(Player &player, int targetx, int targety);
};

