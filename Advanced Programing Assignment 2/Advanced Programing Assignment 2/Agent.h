#pragma once
#include <iostream>
using namespace std;


class AttackInfo
{
private:
	int damage;
	string description;


public:

	AttackInfo(int dam, string des)
	{
		this->damage = dam;
		this->description = des;

	}

};

class Agent
{

public:
	char symbol;
	int row, col;
	Agent();

	Agent(string name, int hp, int damage, int row, int col, char symbol)
	{
		this->Name = name;
		this->HP = hp;
		this->Damage = damage;
		this->row = row;
		this->col = col;
		this->symbol = symbol;

	}

	virtual ~Agent();


	virtual void takeDamage(int dam)
	{
		HP -= dam;
	}

	virtual void fight(Agent* otherA)
	{
		otherA->takeDamage(Damage);
	}

	virtual void displayStats()
	{
		cout << Name << ":" << endl;
		cout << "HP = " << HP << endl;
	}

	virtual string getName()
	{
		return Name;
	}

	virtual bool isDead()
	{
		if(HP <= 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	virtual void deadMessage()
	{
		cout << "---------------------" << endl;
		cout << getName() << " is Dead" << endl;
		cout << "---------------------" << endl;
	}

protected:
	string Name;
	int HP, Damage;
};

class Player : public Agent
{

	
public:


	//Player(string name, int hp, int damage) :Agent(name, hp, damage, row, col, symbol)
	//{
	//{
	//	Name = "Player";
	//	HP = 400;
	//	Damage = 35;
	//}
	Player(string name, int hp, int damage, int row, int col, char symbol) : Agent(name, hp, damage,  row,  col,  symbol)
	{
		this->symbol = symbol;
		this->row = row;
		this->col = col;

		Name = "Player";
		HP = 400;
		Damage = 35;
	}

};

class Kobalt : public  Agent
{
public:
	Kobalt(string name, int hp, int damage, int row, int col, char symbol) : Agent(name, hp, damage, row, col, symbol)
	{
		Name = "Kobalt";
		HP = 70;
		Damage = 20;
	}
	Kobalt(): Agent()
	{
		Name = "Kobalt";
		HP = 70;
		Damage = 20;
	}

	
};



class Boss : public  Agent
{

	Boss(string name, int hp, int damage, int row, int col, char symbol) : Agent(name, hp, damage, row, col, symbol)
	{
		Name = "Boss";
		HP = 600;
		Damage = 50;

	}

	


};

inline Agent::~Agent()
= default;


