#include "MoveToRangeAction.h"

#include <iostream>

MoveToRangeAction::MoveToRangeAction(Agent* agent)
	:ActionNode(agent)
{
	m_name = "Move To Range Action";
}

MoveToRangeAction::~MoveToRangeAction()
= default;

void MoveToRangeAction::Action()
{
	if(GetAgent()->GetActionState() != ActionState::MOVE_TO_RANGE)
	{
		std::cout << "Performing " << m_name << std::endl;
		GetAgent()->SetActionState(ActionState::MOVE_TO_RANGE);
	}
	GetAgent()->MoveToRange();
}
