#pragma once
#ifndef __FLEE_ACTION__
#define __FLEE_ACTION__

#include "ActionNode.h"

class FleeAction : public ActionNode
{
public:
	FleeAction(Agent* agent = nullptr);
	virtual ~FleeAction();

	virtual void Action() override; // Define here
};

#endif /* defined  (__FLEE_ACTION__) */