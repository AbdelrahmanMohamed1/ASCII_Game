#include<iostream>
#include<string>
#include<cstdlib>
#include<conio.h>
#include"GameSystem.h"
using namespace std;
int main()
{
	GameSystem gamesystem("lvl1.txt");

	gamesystem.PlayGame();



	cout << endl;
	system("PAUSE");
	return 0;
}
