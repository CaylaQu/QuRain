#include "MoveToPlayerAction.h"

#include <iostream>

MoveToPlayerAction::MoveToPlayerAction(Agent* agent)
	:ActionNode(agent)
{
	m_name = "Move To Player Action";
}

MoveToPlayerAction::~MoveToPlayerAction()
= default;

void MoveToPlayerAction::Action()
{
	if(GetAgent()->GetActionState() != ActionState::MOVE_TO_PLAYER)
	{
		std::cout << "Performing " << m_name << std::endl;
		GetAgent()->SetActionState(ActionState::MOVE_TO_PLAYER);
	}
	GetAgent()->MoveToPlayer();
}
