#include <iostream>
#include <ctime>
#include <fstream>
#include "Agent.h"

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








int main()
{


	return 0;
}