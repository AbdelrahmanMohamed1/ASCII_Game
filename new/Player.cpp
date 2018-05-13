#include "Player.h"
#include<random>
using namespace std;
#include<ctime>
#include<iostream>

//construct,just initializes position to 0
Player::Player()
{
	_x = 0;
	_y = 0;
}
// initializes the player with properities  
void Player::init(int level, int health, int attack, int defense, int experience)
{
	_level = level;
	_health = health;
	_attack = attack;
	_defence = defense;
	_experience = experience;
}
// set the position of the player
void Player::setposition(int x, int y)
{
	_x = x;
	_y = y;
}
// gets the position of the player using reference variable
void Player::getposition(int &x, int &y)
{
	x = _x;
	y = _y;
}
int Player::attack()
{
	static default_random_engine randomEngine(time(NULL));
	uniform_int_distribution<int> attackroll(0, _attack);

	return attackroll(randomEngine);
}

void Player::addExperience(int attackresult)
{
	_experience += attackresult;

	// level up
	while (_experience>0)
	{
		cout << "leveled Up!" << endl;
		_experience -= 50;
		_attack += 10;
		_defence += 5;
		_health += 10;
		_level++;
		system("PAUSE");
	}
}
int Player::tackDamage(int attack)
{
	attack -= _defence;
	// check if the attack does damage
	if (attack > 0) {
		_health -= attack;
		// check if he died
		if (_health <= 0)return 1;

	}
	return 0;
}