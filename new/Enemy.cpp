#include "Enemy.h"
#include<random>
using namespace std;
#include<ctime>


Enemy::Enemy(string name, char tile, int level, int attack, int defense, int health, int xp)
{
	_name = name;
	_tile = tile;
	_level = level;
	_attack = attack;
	_defence = defense;
	_health = health;
	_experiencevalue = xp;
}
// set the position of the enemy
void Enemy::setposition(int x, int y)
{
	_x = x;
	_y = y;
}
// gets the position of the enemy using reference variable
void Enemy::getposition(int &x, int &y)
{
	x = _x;
	y = _y;
}
int Enemy::attack()
{
	static default_random_engine randomEngine(time(NULL));
	uniform_int_distribution<int> attackroll(0, _attack);

	return attackroll(randomEngine);
}
int Enemy::tackDamage(int attack)
{
	attack -= _defence;
	// check if the attack does damage
	if (attack > 0) {
		_health -= attack;
		// check if he died
		if (_health <= 0)return _experiencevalue;

	}
	return 0;
}


char Enemy::getMove(int playerx, int playery)
{
	static default_random_engine randomEngine(time(NULL));
	uniform_int_distribution<int> moveroll(0, 6);

	int distance;
	int dx = _x - playerx;
	int dy = _y - playery;
	int adx = abs(dx);
	int ady = abs(dy);
	
	distance = adx + ady;

	if (distance <= 5) {
		// Moving along X axis
		if (adx > ady) {
			if (dx > 0) {
				return'a';
			}
			else {
				return 'd';
			}
		}
		else { // Move along Y axis
			if (dy > 0) {
				return'w';
			}
			else {
				return 's';
			}
		}
	}

	int randomMove = moveroll(randomEngine);
	switch (randomMove)
	{
	case 0:
		return 'a';
	case 1:
		return 'w';
	case 2:
		return 's';
	case 3:
		return 'd';
	default:
		return '.';
	}

}

