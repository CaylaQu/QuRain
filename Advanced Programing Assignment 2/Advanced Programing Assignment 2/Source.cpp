#include <iostream>
#include <ctime>
#include <fstream>
#include "Agent.h"
#include<conio.h>
#include<stdlib.h>
#include  <sstream>
#include <string>

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


class Maplevel
{
	
public:
	int** mapData;
	int maxRows, maxColumns;
	Agent* pl1;
	Agent* pl2;


	Maplevel(string filename)
	{
		ifstream in;
		in.open(filename.c_str());
		if (in.is_open())
		{
			string line;
			getline(in, line);
			stringstream ss(line);
			ss >> maxRows;
			ss >> maxColumns;
			mapData = new int* [maxRows];
			for (int x = 0; x < maxRows; x++)
			{
				mapData[x] = new int[maxColumns];
			}

			for (int r = 0; r < maxRows; r++)
			{
				getline(in, line);
				stringstream ss(line);
				for (int c = 0; c < maxColumns; c++)
				{
					ss >> mapData[r][c];
				}
			}







		}
		in.close();
	}

	void addPlayer1(Agent* p1)
	{
		pl1 = p1;

	}
	void addPlayer2(Agent* p2)
	{
		pl2 = p2;
	}
	bool isValid(int r, int c) {
		if (r < 0 || c < 0 || r >= maxRows || c >= maxColumns || mapData[r][c] == 1) {
			return false;
		}
		return true;
	}



	string printMap()
	{

		stringstream ss;
		 char wallSymbol = (char)176;
		 for (int r = 0; r < maxRows; r++)
		 {
			 for (int c = 0; c < maxColumns; c++)
			 {
				 if (pl1->row == r && pl1->col == c)
				 {
					 ss << pl1->symbol << " ";
				 } else 
					 if (pl2->row == r && pl2->col == c)
					 {
						 ss << pl2->symbol << " ";
					 }
					 else {
						 if (mapData[r][c] == 0)
						 {
							 ss << "  ";
						 }
						 else
							 ss << wallSymbol << wallSymbol;

					 }
			}

			 ss << "\n";





		 }

		 return ss.str(); 
	}





};






int main()
{
	Player* p1l = new Player("Hero", 18, 20, 10, 10, 'p');
	Player* p2l = new Player("Hero", 18, 9, 14, 15, 'b');
	Kobalt* k1l = new Kobalt("Monster", 10, 20);
	simulateCombat(p1l, k1l);
	string mapLocation = "C:\\map1.txt";
	Maplevel level(mapLocation);
	level.addPlayer1(p1l);
	level.addPlayer2(p2l);
	 cout << level.printMap();
	

		 char dir = _getch();
		 while (dir != 'E') {
			 if (dir == 'w' || dir == 'W') {
				 if (level.isValid(p1l->row - 1, p1l->col)) {
					 p1l->row = p1l->row - 1;
				 }
			 }
			 if (dir == 'a' || dir == 'A') {
				 if (level.isValid(p1l->row, p1l->col - 1)) {
					 p1l->col = p1l->col - 1;
				 }
			 }
			 if (dir == 's' || dir == 'S') {
				 if (level.isValid(p1l->row + 1, p1l->col)) {
					 p1l->row = p1l->row + 1;
				 }
			 }
			 if (dir == 'd' || dir == 'D') {
				 if (level.isValid(p1l->row, p1l->col + 1)) {
					 p1l->col = p1l->col + 1;
				 }
			 }
			 //p2l
			 if (dir == 'i' || dir == 'I') {
				 if (level.isValid(p2l->row - 1, p2l->col)) {
					 p2l->row = p2l->row - 1;
				 }
			 }
			 if (dir == 'j' || dir == 'J') {
				 if (level.isValid(p2l->row, p2l->col - 1)) {
					 p2l->col = p2l->col - 1;
				 }
			 }
			 if (dir == 'k' || dir == 'K') {
				 if (level.isValid(p2l->row + 1, p2l->col)) {
					 p2l->row = p2l->row + 1;
				 }
			 }
			 if (dir == 'l' || dir == 'L') {
				 if (level.isValid(p2l->row, p2l->col + 1)) {
					 p2l->col = p2l->col + 1;
				 }
			 }
			 system("CLS");
			 cout << level.printMap();
			 dir = _getch();
		 }

		 
	 
	

	return 0;
}