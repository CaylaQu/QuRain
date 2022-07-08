#pragma once
#ifndef _STATEMANAGER_H_
#define _STATEMANAGER_H_

#include "States.h"
#include <vector>

// We're going to make StateManager a "static class".
class StateManager // This is our finite state machine (FSM)
{
private:
	static std::vector<State*> s_states; // s_ is my convention for static properties.
private:
	StateManager() = default;
public:
	static void Update();
	static void Render();
	static void PushState(State* pState);
	static void PopState();
	static void ChangeState(State* pState);
	static void Quit();
	static std::vector<State*>& GetStates(); // Getter for the s_states.
};

typedef StateManager STMA;

#endif

