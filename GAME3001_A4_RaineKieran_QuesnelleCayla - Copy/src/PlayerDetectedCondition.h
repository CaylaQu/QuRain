#pragma once
#ifndef __PLAYER_DETECTED_CONDITION__
#define __PLAYER_DETECTED_CONDITION__

#include "ConditionNode.h"

class PlayerDetectedCondition : public ConditionNode
{
public:
	PlayerDetectedCondition(Agent* agent = nullptr, bool detected = false);
	virtual ~PlayerDetectedCondition();

	// Getters and Setters
	[[nodiscard]] bool GetDetected() const;
	void SetDetected(bool detected);

	virtual bool Condition() override;
private:
	bool m_detected{};
};

#endif /* defined (__PLAYER_DETECTED_CONDITION__) */