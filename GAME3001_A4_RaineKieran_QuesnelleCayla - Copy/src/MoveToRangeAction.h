#pragma once
#ifndef __MOVE_TO_RANGE_ACTION__
#define __MOVE_TO_RANGE_ACTION__

#include "ActionNode.h"

class MoveToRangeAction : public ActionNode
{
public:
	MoveToRangeAction(Agent* agent = nullptr);
	virtual ~MoveToRangeAction();

	virtual void Action() override; // Define here
};

#endif /* defined  (__MOVE_TO_RANGE_ACTION__) */