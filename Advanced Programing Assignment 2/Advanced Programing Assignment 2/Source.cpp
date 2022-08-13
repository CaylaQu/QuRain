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
//{
//public:
//	char symbol;
//	int row, col;
//	Player(int row, int col, char symbol)
//	{
//		this->symbol = symbol;
//		this->row = row;
//		this->col = col;
//
//
//	}
//};





class Maplevel
{
	
public:
	int** mapData;
	int maxRows, maxColumns;
	Player* pl1;
	Player* pl2;


	Maplevel(string filename)
	{
		ifstream in;
		in.open(filename.c_str());
		if (in.is_open())
		{
			string line;
			getline(in, line);
			stringstream ss(line);
			in >> maxRows;
			in >> maxColumns;
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
	
	/*void MapData(string filename)
	{
		ifstream in;
		in.open(filename.c_str());
		if (in.is_open()) 
		{
			string line;
			getline(in, line);
			stringstream ss(line);
			in >> maxRows;
			in >> maxColumns;
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



	 }*/
	void addPlayer1(Player* p1)
	{
		pl1 = p1;

	}
	void addPlayer2(Player* p2)
	{
		pl2 = p2;
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
				 }
				 else 
					 if (pl2->row == r && pl2->col == c)
					 {
						 ss << pl2->symbol << " ";
					 }

				 if (mapData[r][c] == 0)
				 {
					 ss << "  ";
				 }
				 else
					 ss << wallSymbol << wallSymbol;


			}
			 ss << "\n";





		 }

		 return ss.str(); 
	}





};






int main()
{
	Player* p1l = new Player("Hero", 18, 20);
	Kobalt* k1l = new Kobalt("Monster", 10, 20);
	/*simulateCombat(p1l, k1l);*/
	string mapLocation = "C:\\Users\\kiera\\Desktop\\QuRain\\Advanced Programing Assignment 2\\Advanced Programing Assignment 2\\map1.txt";
	Maplevel level(mapLocation);
	level.addPlayer1(p1l);
	/*level.addPlayer2(k1l);*/

	
	

	 cout << level.printMap();
	//Maplevel level;
	


	return 0;
}