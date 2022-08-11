#pragma once
#ifndef __CLOSE_COMBAT_ENEMY__
#define __CLOSE_COMBAT_ENEMY__

#include "Agent.h"
#include "DecisionTree.h"

class CloseCombatEnemy final : public Agent
{
public:
	CloseCombatEnemy();
	~CloseCombatEnemy() override;

	// Inherited via GameObject
	virtual void Draw() override;
	virtual void Update() override;
	virtual void Clean() override;

	// Getters and Setters
	float GetMaxSpeed() const;
	float GetTurnRate() const;
	glm::vec2 GetDesiredVelocity() const;
	float GetAccelerationRate() const;

	void SetMaxSpeed(float speed);
	void SetTurnRate(float angle);
	void SetDesiredVelocity(glm::vec2 target_position);
	void SetAccelerationRate(float rate);

	// Others
	void Seek();
	void LookWhereIAmGoing(glm::vec2 target_direction);
	void Reset();

	// New for Lab 7 part 2
	void Patrol() override;
	void MoveToPlayer() override;
	DecisionTree* GetTree() const;

private:
	float m_maxSpeed;
	float m_turnRate;
	glm::vec2 m_desiredVelocity;
	float m_accelerationRate;
	glm::vec2 m_startPos;

	// New for Lab 7
	std::vector<glm::vec2> m_patrolPath;
	int m_wayPoint;

	void BuildPatrolPath();

	void Move();
	void CheckBounds();

	// New For Lab 7 part 2
	DecisionTree* m_tree;
	void m_buildTree();
};


#endif /* defined (__CLOSE_COMBAT_ENEMY__) */