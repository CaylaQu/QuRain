#include <iostream>
#include <list>
#include <sstream>
#include <vector>
#include <time.h>
#include <stdlib.h>


using namespace std;

class soldier
{
private:
	int HP;
	int Dam;
public:

	soldier(int health, int damage)
	{
		HP = health;
		Dam = damage;
	}

	int getHP() { return HP; }
	int getDamage() { return Dam; }

	string toString()
	{
		stringstream ss;
		ss << "==============================" << endl;
		ss << "The Soldier's health stat is: " << HP << endl;
		ss << "The Soldier's Damage stat is : " << Dam << endl;
		ss << "==============================" << endl;
		return ss.str();
	}
};

void showlist(list<soldier*> l)
{
	list<soldier*>::iterator iter;
	for(iter = l.begin(); iter != l.end(); iter++)
	{
		cout <<  (*iter)->toString() << " " << endl;
	}
}


class WarData
{
private:
	list<soldier*> army1, army2;
public:
	WarData()
	{
		
	}

	int generateArmy1(int num, int maxSolHp, int maxSolDam)
	{
		srand(time(0));

		for (int x = 0; x < 100; x++)
		{
			int hp = rand() % maxSolHp + 1;
			int dama = rand() % maxSolDam + 1;
			army1.push_back(new soldier(hp, dama));

		}
		

	}

	int generateArmy2(int num, int maxSolHp, int maxSolDam)
	{
		srand(time(0));

		for (int x = 0; x < num; x++)
		{
			int hp = rand() % maxSolHp + 1;
			int dama = rand() % maxSolDam + 1;
			army2.push_back(new soldier(hp, dama));

		}
		
	}

	void simulateWar()
	{
		
	}

	void showArmy1()
	{
		showlist(army1);
	}
	void showArmy2()
	{
		showlist(army2);
	}



};




int main()
{
	/*srand(time(0));
	list<soldier*> army1, army2;

	for (int x = 0; x < 100; x ++)
	{
		int hp = rand() % 150 + 1;
		int dama = rand() % 60 + 1;
		army1.push_back(new soldier(hp, dama));

	}
	showlist(army1);*/
	
	WarData war;
	war.generateArmy1(100,500,250);
	war.showArmy1; 

	return 0;
}