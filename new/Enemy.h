#pragma once
#include<string>
using namespace std;
class Enemy
{
public:
	Enemy(string name,char tile,int level,int attack,int defense,int health,int xp);
	int attack();
	int tackDamage(int attack);


	// setter
	void setposition(int x, int y);

	// getter
	void getposition(int &x, int &y);
	string Get_name() { return _name; };
	char gettile() { return _tile; }

	// gets AI move command
	char getMove(int playerx,int playery);

private:
	string _name;
	char _tile;


	int _level;
	int _attack;
	int _defence;
	int _health;
	int _experiencevalue;

	//position
	int _x;
	int _y;
};

