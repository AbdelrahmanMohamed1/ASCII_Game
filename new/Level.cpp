#include "Level.h"
#include<iostream>
#include<fstream>


Level::Level()
{

}

void Level::loadlevel(string filename,Player &player)
{
	// load the level

	ifstream file;
	file.open(filename);
	if (file.fail()) {
		perror(filename.c_str());
		system("PAUSE");
		exit(1);
	}
	string line;
	while (getline(file,line))
	{
		_leveldata.push_back(line);
	}

	file.close();

	// process the level
	char tile;
	for (int i = 0; i < _leveldata.size(); i++) {
		for (int j = 0; j < _leveldata[i].size(); j++) {
			tile = _leveldata[i][j];
			switch (tile)
			{
			case '@'://player
				player.setposition(j, i);
				break;
			case 'S'://snake
				_enemies.push_back(Enemy("Snake",tile,1,3,1,10,50));
				_enemies.back().setposition(j, i);
				break;
			case 'g':
				_enemies.push_back(Enemy("Goblin", tile, 2, 10, 5, 35, 150));
				_enemies.back().setposition(j, i);
				break;
			case 'O':
				_enemies.push_back(Enemy("Ogre", tile, 4, 40, 40, 200, 500));
				_enemies.back().setposition(j, i);
				break;
			case 'D':
				_enemies.push_back(Enemy("Dragon", tile, 100, 2000, 2000, 2000, 500000000));
				_enemies.back().setposition(j, i);
				break;
			case 'B':
				_enemies.push_back(Enemy("Bandit", tile, 3, 15, 10, 100, 250));
				_enemies.back().setposition(j, i);
				break;
			}
			
		}
	}
}

void Level::print()
{
	cout << string(25, '\n');
	for (int i = 0; i < _leveldata.size(); i++) {
		printf("%s\n", _leveldata[i].c_str());
	}
	cout << endl;
}

void Level::moveplayer(char input,Player &player)
{
	int playerx;
	int playery;
	player.getposition(playerx, playery);

	

	switch (input)
	{

	case 'w':// up
	case 'W':
		processplayermove(player, playerx, playery - 1);
		break;
	case 's'://down
	case 'S':
		processplayermove(player, playerx, playery + 1);
		break;
	case 'a':// left
	case 'A':
		processplayermove(player, playerx - 1, playery);
		break;
	case 'd':// right
	case 'D':
		processplayermove(player, playerx + 1, playery);
		break;
	default:
		cout << "invalid input" << endl;
		system("PAUSE");
		break;
	}
}

void Level::uppdateEnemies(Player &player)
{
	char aiMove;
	int playerx;
	int playery;
	int enemyX;
	int enemyY;


	player.getposition(playerx, playery);

	for (int i = 0; i < _enemies.size(); i++) {
		aiMove = _enemies[i].getMove(playerx,playery);
		_enemies[i].getposition(enemyX, enemyY);
		switch (aiMove)
		{

		case 'w':// up
			processEnemymove(player,i, enemyX, enemyY - 1);
			break;
		case 's'://down
			processEnemymove(player,i, enemyX, enemyY + 1);
			break;
		case 'a':// left
			processEnemymove(player,i, enemyX - 1, enemyY);
			break;
		case 'd':// right
			processEnemymove(player,i, enemyX + 1, enemyY);
			break;
		}
	}
}

char Level::get_tile(int x, int y)
{
	char tile = _leveldata[y][x];
	return tile;
}

void Level::set_tile(int x, int y, char tile)
{
	_leveldata[y][x] = tile;
}

void Level::processplayermove(Player &player, int targetx, int targety)
{
	int playerx;
	int playery;
	player.getposition(playerx, playery);
	char movetile = get_tile(targetx, targety);
	switch (movetile)
	{
	case '.':
		player.setposition(targetx, targety);
		set_tile(playerx, playery, '.');
		set_tile(targetx, targety, '@');
		break;
	case '#':
		break;
	default:
		battle_monster(player, targetx, targety);
		break;
	}
}

void Level::processEnemymove(Player &player, int enemyindex, int targetx, int targety)
{
	int playerx;
	int playery;
	int enemyX;
	int enemyY;

	_enemies[enemyindex].getposition(enemyX, enemyY);

	player.getposition(playerx, playery);
	char movetile = get_tile(targetx, targety);
	switch (movetile)
	{
	case '.':
		_enemies[enemyindex].setposition(targetx, targety);
		set_tile(enemyX, enemyY, '.');
		set_tile(targetx, targety, _enemies[enemyindex].gettile());
		break;
	case '@':
		battle_monster(player, enemyX, enemyY);
		break;
	default:
		//battle_monster(player, targetx, targety);
		break;
	}
}


void Level::battle_monster(Player &player, int targetx, int targety)
{
	int enemyX;
	int enemyY;
	int playerX;
	int playerY;
	int attackroll;
	int attackresult;
	string enemy_name;
	player.getposition(playerX, playerY);

	for (int i = 0; i < _enemies.size(); i++) {
		_enemies[i].getposition(enemyX, enemyY);
		enemy_name = _enemies[i].Get_name();

		if (targetx == enemyX && targety == enemyY) {

			//Battle!
			attackroll = player.attack();
			cout << "Player attacked " <<enemy_name<< " with a roll of" << " " << attackroll << endl;
			attackresult= _enemies[i].tackDamage(attackroll);
			if (attackresult != 0) {
				set_tile(targetx, targety, '.');
				print();
				cout << "Monster Died" << endl;

				// remove the enemies !
				_enemies[i] = _enemies.back();
				_enemies.pop_back();
				i--;

				system("PAUSE");
				player.addExperience(attackresult);
				return;
			}

			// Monster turn
			attackroll = _enemies[i].attack();
			attackresult = player.tackDamage(attackroll);
			if (attackresult != 0) {
				set_tile(playerX, playerY, '.');
				print();
				cout << "you Died" << endl;
				system("PAUSE");
				
				exit(0);
			}
			system("PAUSE");
			return;
		}
	}
}

