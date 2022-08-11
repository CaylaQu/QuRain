#include "CloseCombatCondition.h"

CloseCombatCondition::CloseCombatCondition(Agent* agent, const bool within_combat_range)
	:ConditionNode(agent)
{
	m_name = "Close Combat Condition";
	SetIsWithinCombatRange(within_combat_range);
}

CloseCombatCondition::~CloseCombatCondition()
= default;

void CloseCombatCondition::SetIsWithinCombatRange(const bool state)
{
	m_isWithinCombatRange = state;
}

bool CloseCombatCondition::Condition()
{
	return m_isWithinCombatRange;
}
