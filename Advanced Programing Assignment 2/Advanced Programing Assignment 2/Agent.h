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
	Agent();

	Agent(string name, int hp, int damage)
	{
		this->Name = name;
		this->HP = hp;
		this->Damage = damage;

	}
	virtual ~Agent();

	virtual void takeDamage(int dam)
	{
		HP -= dam;
	}

	virtual void fight(Agent otherA)
	{
		otherA.takeDamage(Damage);
	}

	virtual void displayStats()
	{
		cout << Name << ":" << endl;
		cout << "HP = " << HP << ":" << endl;
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

protected:
	string Name;
	int HP, Damage;
};

class Player : public Agent
{
	Player(string name, int hp, int damage) : Agent(name, hp, damage)
	{
		Name = "Player";
		HP = 400;
		Damage = 35;
	}
	Player();
	virtual ~Player();

};

class Kobalt : public  Agent
{
	Kobalt(string name, int hp, int damage) : Agent( name,  hp,  damage)
	{
		Name = "Kobalt";
		HP = 70;
		Damage = 20;
	}
	Kobalt();
	virtual ~Kobalt();

};



class Boss : public  Agent
{

	Boss(string name, int hp, int damage) : Agent(name, hp, damage)
	{
		Name = "Boss";
		HP = 600;
		Damage = 50;

	}

	


};