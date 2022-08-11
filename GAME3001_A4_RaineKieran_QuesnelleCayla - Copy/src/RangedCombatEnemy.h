#pragma once
#ifndef __RANGED_COMBAT_ENEMY__
#define __RANGED_COMBAT_ENEMY__

#include "Agent.h"
#include "DecisionTree.h"

class RangedCombatEnemy final : public Agent
{
public:
	RangedCombatEnemy(Scene* scene);
	~RangedCombatEnemy() override;

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
	// New for Lab 7 part 3
	void Flee() override;
	void MoveToLOS() override;
	void MoveToRange() override;
	void MoveToCover() override;
	void WaitBehindCover() override;
	void Attack() override;


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

	int m_fireCounter;
	int m_fireCounterMax;
	Scene* m_pScene;
};


#endif /* defined (__RANGED_COMBAT_ENEMY__) */