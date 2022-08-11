#include "LOSCondition.h"

LOSCondition::LOSCondition(Agent* agent)
	:ConditionNode(agent)
{
	m_name = "LOS Condition";
}

LOSCondition::~LOSCondition()
= default;

bool LOSCondition::Condition()
{
	return GetAgent()->HasLOS();
}
