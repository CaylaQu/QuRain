#pragma once
#ifndef __ATTACK_ACTION__
#define __ATTACK_ACTION__

#include "ActionNode.h"

class AttackAction : public ActionNode
{
public:
	AttackAction(Agent* agent = nullptr);
	virtual ~AttackAction();

	virtual void Action() override; // Define here
};

#endif /* defined  (__ATTACK_ACTION__) */