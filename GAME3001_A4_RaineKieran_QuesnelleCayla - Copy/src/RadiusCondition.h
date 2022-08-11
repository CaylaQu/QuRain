#pragma once
#ifndef __RADIUS_CONDITION__
#define __RADIUS_CONDITION__

#include "ConditionNode.h"

class RadiusCondition : public ConditionNode
{
public:
	RadiusCondition(Agent* agent = nullptr, bool within_radius = false);
	virtual ~RadiusCondition();

	// Getters and Setters
	void SetIsWithinRadius(bool state);

	virtual bool Condition() override;
private:
	bool m_isWithinRadius{};
};

#endif /* defined (__RADIUS_CONDITION__) */