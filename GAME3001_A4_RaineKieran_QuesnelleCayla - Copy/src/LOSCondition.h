#pragma once
#ifndef __LOS_CONDITION__
#define __LOS_CONDITION__

#include "ConditionNode.h"

class LOSCondition : public ConditionNode
{
public:
	LOSCondition(Agent* agent = nullptr);
	virtual ~LOSCondition();

	virtual bool Condition() override;
};

#endif /* defined (__LOS_CONDITION__) */