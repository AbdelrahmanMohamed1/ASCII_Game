#pragma once
class Player
{
public:
	Player();
	void init(int level, int health, int attack, int defense, int experience);
	int attack();
	int tackDamage(int attack);

	// setter
	void setposition(int x, int y);
	void addExperience(int attackresult);

	// getter
	void getposition(int &x, int &y);

private:
	// properties
	int _level;
	int _health;
	int _attack;
	int _defence;
	int _experience;

	// position
	int _x;
	int _y;
	
};

