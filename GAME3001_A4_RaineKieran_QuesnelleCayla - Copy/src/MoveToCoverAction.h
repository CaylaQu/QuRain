#pragma once
#ifndef __MOVE_TO_COVER_ACTION__
#define __MOVE_TO_COVER_ACTION__

#include "ActionNode.h"

class MoveToCoverAction : public ActionNode
{
public:
	MoveToCoverAction(Agent* agent = nullptr);
	virtual ~MoveToCoverAction();

	virtual void Action() override; // Define here
};

#endif /* defined  (__MOVE_TO_COVER_ACTION__) */