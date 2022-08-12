#include <iostream>
#include <ctime>
#include <fstream>
#include "Agent.h"
#include<conio.h>
#include<stdlib.h>

using namespace std;


void simulateCombat(Agent agent1, Agent agent2)
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
			agent1.fight(agent2);
			cout << agent1.getName() << " attacks " << agent2.getName() << endl;
			agent1.displayStats();
			agent2.displayStats();

			if(agent2.isDead())
			{
				cout << agent2.getName() << " is Dead." << endl;
				break;
			}

			agent2.fight(agent1);
			cout << agent2.getName() << " attacks " << agent1.getName() << endl;
			agent1.displayStats();
			agent2.displayStats();

			if (agent1.isDead())
			{
				cout << agent1.getName() << " is Dead." << endl;
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
			agent2.fight(agent1);
			cout << agent2.getName() << " attacks " << agent1.getName() << endl;
			agent2.displayStats();
			agent1.displayStats();

			if (agent1.isDead())
			{
				cout << agent1.getName() << " is Dead." << endl;
				break;
			}

			agent1.fight(agent2);
			cout << agent1.getName() << " attacks " << agent2.getName() << endl;
			agent2.displayStats();
			agent1.displayStats();

			if (agent2.isDead())
			{
				cout << agent1.getName() << " is Dead." << endl;
				break;
			}

		}


	}



}
class Player












class Maplevel
{
private: 
	int** mapData;
	int maxRows, maxColumns;

public:
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








		}
		in.close();



	 }
	
	string getMap() {
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

		 return ss.str
	}





};






int main()
{
	Player* p1l = new Player(0, 0, 'P');
	Player* p12 = new Player(18, 0, 'P');
 	Maplevel level ("c:\\map1.txt");
	cout << level.getMap();
	return 0;

}