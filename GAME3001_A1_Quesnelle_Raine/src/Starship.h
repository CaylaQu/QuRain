#pragma once
#ifndef __STARSHIP__
#define __STARSHIP__

#include "Agent.h"

class Starship final : public Agent {
public:
	Starship();
	~Starship() override;

	// Inherited via GameObject
	virtual void Draw() override;
	virtual void Update() override;
	virtual void Clean() override;

	float GetMaxSpeed() const;
	float GetDesiredVelocity() const;
	float GetAccelerationRate() const;
	float GetTurnRate() const;


	void SetMaxSpeed(float speed);
	void SetTurnRate(float angle);
	void SetDesiredVelocity(glm::vec2 target_position);
	void SetAccelerationRate(float rate);

	//Others
	void Seek();
	void LookWhereIAmGoing(glm::vec2 target_direction);
	void Reset();

private:
	float m_maxSpeed;
	float m_turnRate;
	glm::vec2 m_desieredVelocity;
	float m_accelerationRate;
	glm::vec2 m_startPos;

	void Move();
	void CheckBounds();
	

};


#endif /* defined (__TARGET__) */