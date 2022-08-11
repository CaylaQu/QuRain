#include "WaitBehindCoverAction.h"

#include <iostream>

WaitBehindCoverAction::WaitBehindCoverAction(Agent* agent)
	:ActionNode(agent)
{
	m_name = "Wait Behind Cover Action";
}

WaitBehindCoverAction::~WaitBehindCoverAction()
= default;

void WaitBehindCoverAction::Action()
{
	if(GetAgent()->GetActionState() != ActionState::WAIT_BEHIND_COVER)
	{
		std::cout << "Performing " << m_name << std::endl;
		GetAgent()->SetActionState(ActionState::WAIT_BEHIND_COVER);
	}
	GetAgent()->WaitBehindCover();
}
