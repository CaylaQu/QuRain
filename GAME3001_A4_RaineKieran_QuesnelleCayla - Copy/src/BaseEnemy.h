#pragma once

#ifndef __BASE_ENEMY__
#define __BASE_ENEMY__

#include "Agent.h"

class BaseEnemy : public Agent
{
public:
	BaseEnemy();
	~BaseEnemy() override;

	// Inherited via GameObject
	virtual void Draw() override;
	virtual void Update() override;
	virtual void Clean() override;

	// Others
	void EnemyPatrol();
	void EnemyEngaged();
	void EnemyIdle();
	//bool LOSDetectPlayer();
	void LookWhereIAmGoing(glm::vec2 target_direction);
	void Reset();

private:
	float m_maxSpeed;
	float m_turnRate;
	glm::vec2 m_desiredVelocity;
	float m_accelerationRate;
	glm::vec2 m_startPos;

	void CheckBounds();
	
};

#endif