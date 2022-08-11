#pragma once
#ifndef __WAIT_BEHIND_COVER_ACTION__
#define __WAIT_BEHIND_COVER_ACTION__

#include "ActionNode.h"

class WaitBehindCoverAction : public ActionNode
{
public:
	WaitBehindCoverAction(Agent* agent = nullptr);
	virtual ~WaitBehindCoverAction();

	virtual void Action() override; // Define here
};

#endif /* defined  (__WAIT_BEHIND_COVER_ACTION__) */