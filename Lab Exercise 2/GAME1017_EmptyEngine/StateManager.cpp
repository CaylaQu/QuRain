#include "StateManager.h"

void StateManager::Update()
{
	if (!s_states.empty())
		s_states.back()->Update(); // s_states.back() represents the current state running.
}

void StateManager::Render()
{
	if (!s_states.empty())
		s_states.back()->Render();
}

// Used when there are 2 states in vector, i.e. Game and Pause.
void StateManager::PushState(State* pState) // Going from Game to Pause.
{
	s_states.push_back(pState); // pState now becomes current state.
	s_states.back()->Enter();
}

// Used when there are 2 states in vector, i.e. Game and Pause.
void StateManager::PopState() // Going from Pause back to Game.
{
	if (s_states.size() <= 1) return;
	if (!s_states.empty())
	{
		s_states.back()->Exit(); // Cleans up current state.
		delete s_states.back(); // Deallocates current state.
		s_states.back() = nullptr; // Wrangle our dangle.
		s_states.pop_back(); // Removed nullptr to deallocated current state.
	}
	s_states.back()->Resume();
}

void StateManager::ChangeState(State* pState)
{
	if (!s_states.empty())
	{
		s_states.back()->Exit(); // Cleans up current state.
		delete s_states.back(); // Deallocates current state.
		s_states.back() = nullptr; // Wrangle our dangle.
		s_states.pop_back(); // Removed nullptr to deallocated current state.
	}
	s_states.push_back(pState);
	s_states.back()->Enter();
}

void StateManager::Quit()
{
	while (!s_states.empty())
	{
		s_states.back()->Exit(); // Cleans up current state.
		delete s_states.back(); // Deallocates current state.
		s_states.back() = nullptr; // Wrangle our dangle.
		s_states.pop_back(); // Removed nullptr to deallocated current state.
	}
}

std::vector<State*>& StateManager::GetStates() { return s_states; }

std::vector<State*> StateManager::s_states; // This now will be allocated memory. It now "exists".