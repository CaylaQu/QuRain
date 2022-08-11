// cayla quesnelle kieran raine
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <time.h>

using namespace std;

class Attackinfo
{

public:
	int damage;
	string description;

	Attackinfo(int damage, string description)
	{
		this->damage = damage;
		this->description = description;
	}
};

class BaseCharacter 
{
protected:
	string name;
	int strength;
	int agility;
	int intelligence;
	int maxHP;
	int presentHP;
	int dodgeChance;
	int baseDamage;

public:
	BaseCharacter(string name, int strength, int agility, int intelligence, int maxHP, int dodgeChance, int baseDamage) 
	{
		this->name = name;
		this->strength = strength;
		this->agility = agility;
		this->intelligence = intelligence;
		this->maxHP = maxHP;
		this->dodgeChance = dodgeChance;
		this->baseDamage = baseDamage;
	}
	virtual Attackinfo getAttack()
	{
		return primaryAttack();
	}
	virtual Attackinfo primaryAttack()
	{
		Attackinfo p_attack(baseDamage, " Strikes at");
		return p_attack;
		 
	}
	virtual Attackinfo secondaryAttack()
	{
		Attackinfo p_attack(baseDamage, " Strikes at");
		return p_attack;
	}
	virtual void takeDamage(int amt)
	{
		presentHP = presentHP - amt;
	}
	virtual string toString()
	{
		stringstream ss;
		ss << "Character stats \n";
		ss << "Name -> " << name << endl;
		ss << "Strength -> " << strength << endl;
		ss << "Agility -> " << agility << endl;
		ss << "Intelligence -> " << intelligence << endl;
		ss << "Max HP -> " << maxHP << endl;
		ss << "Attack damage -> " << baseDamage << endl;

		return ss.str();
	}
	string getName()
	{
		return name;
	}
	int getMaxHP()
	{
		return maxHP;
	}
	int getPresentHP()
	{
		return presentHP;
	}
	int getDodgeChance()
	{
		return dodgeChance;
	}

};

class Warrior : public ::BaseCharacter
{
public:
	int resistance;

	Warrior(string name, int strength, int agility, int intelligence, int maxHP, int dodgeChance, int baseDamage, int resistance) : BaseCharacter (name, strength, agility, intelligence, maxHP, dodgeChance, baseDamage)
	{
		this->resistance = resistance;
	}
	Attackinfo getAttack()
	{
		int roll = rand() % 100 + 1;
		if (roll <= 10) return secondaryAttack();
		return primaryAttack();
	}
	Attackinfo primaryAttack() 
	{
		
		Attackinfo p_attack( baseDamage + baseDamage * (strength / 20),
			"strikes at");
		return p_attack;
	}
	Attackinfo secondaryAttack()
	{
		dodgeChance += agility / 2;
		if (dodgeChance > 50)
		{
			dodgeChance = 50; 
		}
		Attackinfo s_attack(2, "gets more agile and leaps at");
		return s_attack;
	}
	void takeDamage(int amt)
	{
		 int dReduct = (amt * 0.01) * resistance;
			presentHP = presentHP - (amt - dReduct);
	}
	string toString()
	{
		stringstream ss;
		ss << "Warrior stats \n";
		ss << "Name -> " << name << endl;
		ss << "Strength -> " << strength << endl;
		ss << "Agility -> " << agility << endl;
		ss << "Intelligence -> " << intelligence << endl;
		ss << "Max HP -> " << maxHP << endl;
		ss << "Attack damage -> " << baseDamage << endl;
		ss << "Resistance -> " << resistance << endl;

		return ss.str();
	}
};

class Mage : public ::BaseCharacter
{
public:
	Mage(string name, int strength, int agility, int intelligence, int maxHP, int dodgeChance, int baseDamage) : BaseCharacter (name, strength, agility, intelligence, maxHP, dodgeChance, baseDamage)
	{
		
	}
	Attackinfo getAttack()
	{
		int roll = rand() % 100 + 1;
		if (roll <= 30) return secondaryAttack();
		return primaryAttack();
	}
	Attackinfo secondaryAttack()
	{
		Attackinfo s_attack(baseDamage + baseDamage * (intelligence / 20),
			"throws a fireball");
		return s_attack;
	}
	string toString()
	{
		stringstream ss;
		ss << "Mage stats \n";
		ss << "Name -> " << name << endl;
		ss << "Strength -> " << strength << endl;
		ss << "Agility -> " << agility << endl;
		ss << "Intelligence -> " << intelligence << endl;
		ss << "Max HP -> " << maxHP << endl;
		ss << "Attack damage -> " << baseDamage << endl;

		return ss.str();

	}
};

class Priest : public ::BaseCharacter
{
public:
	Priest(string name, int strength, int agility, int intelligence, int maxHP, int dodgeChance, int baseDamage) : BaseCharacter(name, strength, agility, intelligence, maxHP, dodgeChance, baseDamage)
	{
		
	}
	Attackinfo getAttck()
	{
		int roll = rand() % 100 + 1;
		if (roll <= 40) return secondaryAttack();
		return primaryAttack();
	}
	Attackinfo secondaryAttack()
	{
		 
		int healPercent = maxHP * 0.01;
		int addHeal = healPercent * (5 + intelligence / 20);
		maxHP += addHeal;

		Attackinfo heal(0, "heals themselves and smiles at");
		return heal;
	}
	string toString()
	{
		stringstream ss;
		ss << "Priest stats \n";
		ss << "Name -> " << name << endl;
		ss << "Strength -> " << strength << endl;
		ss << "Agility -> " << agility << endl;
		ss << "Intelligence -> " << intelligence << endl;
		ss << "Max HP -> " << maxHP << endl;
		ss << "Attack damage -> " << baseDamage << endl;

		return ss.str();
	}
};

class ArenaManager 
{
private:
	BaseCharacter** contestantList;
	int maxContestant;
	int numContestants;

public:
	ArenaManager(int maxCon)
	{
		maxContestant = maxCon;
		numContestants = 0;
		contestantList = new BaseCharacter * [maxCon];
	}

	bool addContesntant(const char type, string n, int str, int agi, int intel, int max, int dodge, int dam)
	{
		const char select = type;
			
			if(select == 'M' && numContestants < maxContestant)
			{
				Mage* newMage = new Mage(n, str, agi, intel, max, dodge, dam);
				contestantList[numContestants++] = newMage;
				cout << "thank you for making a new Mage" << endl;
				cout << "================================ \n";

				return true;
			}
			else if (select == 'P' && numContestants < maxContestant)
			{
				Priest* newPriest = new Priest(n, str, agi, intel, max, dodge, dam);
				contestantList[numContestants++] = newPriest;
				cout << "thank you for making a new Priest" << endl;
				cout << "================================ \n";


				return true;
			}

			cout << "sorry no more room :(" << endl; 
			return false;
		
	}
	bool addContestant(string name, int strength, int agility, int intelligence, int maxHP, int dodgeChance,int baseDamage, int resistance)
	{
		if(numContestants < maxContestant)
		{
			Warrior* newWarrior = new Warrior(name, strength, agility, intelligence, maxHP, dodgeChance, baseDamage, resistance);
			contestantList[numContestants++] = newWarrior;
			cout << "thank you for making a new Warrior" << endl;
			cout << "================================ \n";
			return true;
		}
		return false;
	}
	BaseCharacter viewContestant(int arrayindex) 
	{
		int arr = arrayindex;

		return *contestantList[arr];

		

	}
	void simulateChallenge(int cintest1index, int contestant2index)
	{
		
	}
	string viewAllContestant()
	{
		stringstream ss;
		for(int i = 0; i <= maxContestant; i++ )
		{
			ss << i << ". " << contestantList[i]->getName() << " " << contestantList[i]->getPresentHP() << endl;
		}
		return ss.str();
	} 
	int getsize()
	{
		return maxContestant;
	}
	BaseCharacter** getList()
	{
		return contestantList;
	}
};

void menu()
{
	cout << "================================ \n";
	cout << "1. Add Contestant \n";
	cout << "2. View Specific Contestant \n";
	cout << "3. View All Contestants \n";
	cout << "5. Quit \n";
	cout << "================================ \n";
}

int main()
{

	int roll = rand() % 100 + 1;

	cout << "Welcome to the arena! \n";
	cout << "what would you like to do first? \n";

	int choice;
	int AddCharChoice;
	ArenaManager arena1(20);

	menu();


	do
	{
		cout << "Enter your choice (1-5): ";
		cin >> choice;
		cout << "================================ \n";

		switch (choice)
		{
		case 1: //Add Contestant
			cout << "What type of contestant would you like to add? \n";
			cout << "1. Warrior \n";
			cout << "2. Mage \n";
			cout << "3. Priest \n";
			cin >> AddCharChoice;
			switch (AddCharChoice)
			{
			case 1: //warrior
			{
				string wName;
				int wStrength;
				int wIntelligence;
				int wAgility;
				int wmaxHP;
				int wDodgechance;
				int wBasedamage;
				int wResistance;
				

				cout << "Enter a name \n";
				cin >> wName;
				cout << "Enter warriors strength \n";
				cin >> wStrength;
				cout << "Enter warriors intelligence \n";
				cin >> wIntelligence;
				cout << "Enter warriors agility \n";
				cin >> wAgility;
				cout << "Enter warriors max health points \n";
				cin >> wmaxHP;
				cout << "Enter warriors dodge chances \n";
				cin >> wDodgechance;
				cout << "Enter warriors base damage \n";
				cin >> wBasedamage;
				cout << "Enter warriors resistance \n";
				cin >> wResistance;
				



				arena1.addContestant(wName, wStrength, wAgility, wIntelligence, wmaxHP, wDodgechance,
					wBasedamage, wResistance);
				break;
			}
			case 2: // mage
				{
					string mName;
					int mStrength;
					int mIntelligence;
					int mAgility;
					int mmaxHP;
					int mDodgechance;
					int mBasedamage;
					int mResistance;
					const char type = 'M';

					
					cout << "Enter a name \n";
					cin >> mName;
					cout << "Enter mages strength \n";
					cin >> mStrength;
					cout << "Enter mages intelligence \n";
					cin >> mIntelligence;
					cout << "Enter mages agility \n";
					cin >> mAgility;
					cout << "Enter mages max health points \n";
					cin >> mmaxHP;
					cout << "Enter mages dodge chances \n";
					cin >> mDodgechance;
					cout << "Enter mages base damage \n";
					cin >> mBasedamage;
			
					

					arena1.addContesntant(type, mName, mStrength,  mAgility, mIntelligence, mmaxHP, mDodgechance, mBasedamage);
					break; 
				}
			case 3:
			{
				string pName;
				int pStrength;
				int pIntelligence;
				int pAgility;
				int pmaxHP;
				int pDodgechance;
				int pBasedamage;
				int pResistance;
				char type = 'P';

				
				cout << "Enter a name \n";
				cin >> pName;
				cout << "Enter priests strength \n";
				cin >> pStrength;
				cout << "Enter priests intelligence \n";
				cin >> pIntelligence;
				cout << "Enter priests agility \n";
				cin >> pAgility;
				cout << "Enter priests max health points \n";
				cin >> pmaxHP;
				cout << "Enter priests dodge chances \n";
				cin >> pDodgechance;
				cout << "Enter priests base damage \n";
				cin >> pBasedamage;
				cout << "Enter priests resistance \n";
				cin >> pResistance;
				

				arena1.addContesntant(type, pName, pStrength, pAgility, pIntelligence, pmaxHP, pDodgechance, pBasedamage);
					
				break;
			}

			}
			break;
		case 2:
		{//View Specific Contestant
			int select;

			cout << "here is a list of all current fighters" << endl;
			for (int i = 0; i < arena1.getsize(); i++)
			{
				cout << i << ". " << arena1.getList()[i]->getName() << endl;
			}
			cout << "What contestant would you like to view? ";
			cin >> select;
			cout << endl;
			arena1.viewContestant(select).toString();
		}
			break;
		case 3: //View All Contestants
			cout << "List of all current contestants \n";
			arena1.viewAllContestant();

			break;
		case 4: //Run Combat Challenge


			break;
		}
	} while (choice != 5);


	return 0;
}