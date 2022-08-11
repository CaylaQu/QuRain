#pragma once
#ifndef __TORPEDO__
#define __TORPEDO__

#include "Sprite.h"
#include "TorpedoAnimationState.h"

class Torpedo final : public Sprite
{
public:
	Torpedo(float speed = 0.0f);
	~Torpedo();

	void Draw() override;
	void Update() override;
	void Clean() override;

	void SetAnimationState(TorpedoAnimationState new_state);

private:
	void BuildAnimations();

	TorpedoAnimationState m_currentAnimationState;

	float m_speed;
};

#endif
