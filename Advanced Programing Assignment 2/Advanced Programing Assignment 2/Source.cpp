#include <iostream>
#include <ctime>
#include <fstream>
#include "Agent.h"
#include<conio.h>
#include<stdlib.h>
#include  <sstream>

using namespace std;


void simulateCombat(Agent* agent1, Agent* agent2)
{

	srand(time(0));

	int first;
	first = rand() % 100 + 1;

	if (first >= 0 && first <= 50)
	{
		cout << "You Have Made An Encounter!" << endl;
		cout << "Player Goes First!" << endl;
		while(true)
		{
			agent1->fight(agent2);
			cout << "---------------------" << endl;
			cout << agent1->getName() << " Attacks " << agent2->getName() << endl;
			cout << "---------------------" << endl;
			agent1->displayStats();
			agent2->displayStats();

			if(agent2->isDead())
			{
				agent2->deadMessage();

				break;
			}
			

			agent2->fight(agent1);
			cout << "---------------------" << endl;
			cout << agent2->getName() << " Attacks " << agent1->getName() << endl;
			cout << "---------------------" << endl;
			agent1->displayStats();
			agent2->displayStats();

			if (agent1->isDead())
			{
				agent1->deadMessage();

				break;
			}
			
		}

		
	}
	else if (first > 50 && first <= 100)
	{
		cout << "You Have Made An Encounter!" << endl;
		cout << "Enemy Goes First!" << endl;
		while (true)
		{
			agent2->fight(agent1);
			cout << "---------------------" << endl;
			cout << agent2->getName() << " attacks " << agent1->getName() << endl;
			cout << "---------------------" << endl;
			agent2->displayStats();
			agent1->displayStats();

			if (agent1->isDead())
			{
				agent1->deadMessage();

				break;
			}

			agent1->fight(agent2);
			cout << "---------------------" << endl;
			cout << agent1->getName() << " attacks " << agent2->getName() << endl;
			cout << "---------------------" << endl;
			agent2->displayStats();
			agent1->displayStats();

			if (agent2->isDead())
			{
				agent2->deadMessage();

				break;
			}

		}


	}



}
//class Player






class Maplevel
{
private: 
	int** mapData;
	int maxRows, maxColumns;

public:
	Maplevel();
	void MapData(string filename)
	{
		ifstream in;
		in.open(filename.c_str());
		if (in.is_open())
		{
			in >> maxRows;
			in >> maxColumns;
			mapData = new int* [maxRows];
			for (int x = 0; x < maxRows; x++)
			{
				mapData[x] = new int[maxColumns];
			}

			for (int r = 0; r < maxRows; r++)
			{
				for (int c = 0; c < maxColumns; c++)
				{
					in >> mapData[r][c];
				}
			}







		}
		in.close();



	 }
	
	string getMap()
	{
		stringstream ss;
		 char wallSymbol = (char)176;
		 for (int r = 0; r < maxRows; r++)
		 {
			 for (int c = 0; c < maxColumns; c++)
			 {
				 if (mapData[r][c] == 0)
				 {
					 ss << " ";
				 }
				 else
					 ss << wallSymbol << wallSymbol;


			}
			 ss << "\n";





		 }

		 return ss.str;
	}





};






int main()
{
	Player* p1l = new Player("Player", 10, 20);
	Kobalt* k1l = new Kobalt("Player", 10, 20);
	simulateCombat(p1l, k1l);

	Player* p1l = new Player(0, 0, 'P');
	Player* p12 = new Player(18, 0, 'P');
	
	Maplevel level;
	level.MapData("c:\\map1.txt");
	cout << level.getMap();

	return 0;
}