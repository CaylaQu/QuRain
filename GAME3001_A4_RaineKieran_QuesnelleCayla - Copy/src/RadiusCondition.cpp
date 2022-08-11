#include "RadiusCondition.h"

RadiusCondition::RadiusCondition(Agent* agent, const bool within_radius)
	:ConditionNode(agent)
{
	m_name = "Radius Condition";
	SetIsWithinRadius(within_radius);
}

RadiusCondition::~RadiusCondition()
= default;

void RadiusCondition::SetIsWithinRadius(const bool state)
{
	m_isWithinRadius = state;
}

bool RadiusCondition::Condition()
{
	return m_isWithinRadius;
}
