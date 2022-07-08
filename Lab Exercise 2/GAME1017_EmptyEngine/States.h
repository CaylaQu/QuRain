#pragma once
#ifndef _STATES_H_
#define _STATES_H_
#include "Turret.h"
#include "Enemy.h"
#include <vector>

// An abstract class is one that cannot be instantiated. 
// Why? Because they'd be a base class most likely.
class State // This is the abstract base class for all state subclasses.
{
protected: // Private but inherited.
	State() = default; // Or State() {};
public:
	virtual void Enter() = 0; // = 0 means pure virtual. Method MUST be defined in subclass.
	virtual void Update() = 0;
	virtual void Render();
	virtual void Exit() = 0;
	virtual void Resume() {};
};

class TitleState : public State
{
private: // Private properties.
public: // Public methods.
	TitleState();
	virtual void Enter();
	virtual void Update();
	virtual void Render();
	virtual void Exit();
};

class PauseState : public State
{
public: // Public methods.

	PauseState();
	virtual void Enter();
	virtual void Update();
	virtual void Render();
	virtual void Exit();

};

class GameState : public State
{
private:
	std::vector<Turret*> m_turrets; 
	static std::vector<Enemy*> s_enemies; // didnt need to be startic
	static std::vector<Bullet*> s_bullets; // static because turret class is spawning bullets 
	int m_spawnCtr; // enemy spawn counter
	void ClearTurrets();
public: // Public methods.
	GameState();
	virtual void Enter();
	virtual void Update();
	virtual void Render();
	virtual void Exit();
	virtual void Resume();
	static std::vector<Bullet*>& Bullets() { return s_bullets; }
	static std::vector<Enemy*>& Enemies() { return s_enemies; }


};
#endif