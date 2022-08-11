#pragma once
#ifndef __MOVE_TO_PLAYER_ACTION__
#define __MOVE_TO_PLAYER_ACTION__

#include "ActionNode.h"

class MoveToPlayerAction : public ActionNode
{
public:
	MoveToPlayerAction(Agent* agent = nullptr);
	virtual ~MoveToPlayerAction();

	virtual void Action() override; // Define here
};

#endif /* defined  (__MOVE_TO_PLAYER_ACTION__) */