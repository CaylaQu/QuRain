#include "RangedCombatEnemy.h"

#include "AttackAction.h"
#include "EventManager.h"
#include "FleeAction.h"
#include "TextureManager.h"
#include "Util.h"
#include "Game.h"
#include "MoveToCoverAction.h"
#include "MoveToLOSAction.h"
#include "MoveToRangeAction.h"
#include "PatrolAction.h"
#include "WaitBehindCoverAction.h"

RangedCombatEnemy::RangedCombatEnemy(Scene* scene) : m_maxSpeed(20.0f),
                                         m_turnRate(5.0f), m_accelerationRate(2.0f),
										 m_fireCounter(0), m_fireCounterMax(60), m_pScene(scene)
{
	TextureManager::Instance().Load("../Assets/textures/dino.png","ranged_enemy");

	const auto size = TextureManager::Instance().GetTextureSize("ranged_enemy");
	SetWidth(static_cast<int>(size.x));
	SetHeight(static_cast<int>(size.y));  

	GetRigidBody()->velocity = glm::vec2(0, 0);
	GetRigidBody()->acceleration = glm::vec2(0, 0);
	GetRigidBody()->isColliding = false;

	SetCurrentHeading(0.0f); // current facing angle
	SetCurrentDirection(glm::vec2(1.0f, 0.0f)); // facing right

	SetLOSDistance(400.0f);
	SetLOSColour(glm::vec4(1, 0, 0, 1)); // default LOS colour is Red
	
	SetType(GameObjectType::AGENT);

	// New for Lab 7
	SetActionState(ActionState::NO_ACTION);
	BuildPatrolPath();

	// New for Lab 7 part 2
	m_tree = new DecisionTree(this); // Create a new Tree
	m_buildTree();
	m_tree->Display(); // optional
}

RangedCombatEnemy::~RangedCombatEnemy()
= default;

void RangedCombatEnemy::Draw()
{
	// draw the target
	TextureManager::Instance().Draw("ranged_enemy", GetTransform()->position, GetCurrentHeading(), 255, true);

	// draw LOS

	if(EventManager::Instance().IsIMGUIActive())
	{
		Util::DrawLine(GetTransform()->position + GetCurrentDirection() * 0.5f * static_cast<float>(GetWidth()),
			GetMiddleLOSEndPoint(), GetLOSColour());
	}
	
}

void RangedCombatEnemy::Update()
{
	// Determine which action to perform
	m_tree->MakeDecision();
}

void RangedCombatEnemy::Clean()
{

}

float RangedCombatEnemy::GetMaxSpeed() const
{
	return m_maxSpeed;
}

float RangedCombatEnemy::GetTurnRate() const
{
	return m_turnRate;
}

glm::vec2 RangedCombatEnemy::GetDesiredVelocity() const
{
	return m_desiredVelocity;
}

float RangedCombatEnemy::GetAccelerationRate() const
{
	return m_accelerationRate;
}

void RangedCombatEnemy::SetMaxSpeed(const float speed)
{
	m_maxSpeed = speed;
}

void RangedCombatEnemy::SetTurnRate(const float angle)
{
	m_turnRate = angle;
}

void RangedCombatEnemy::SetDesiredVelocity(const glm::vec2 target_position)
{
	m_desiredVelocity = Util::Normalize(target_position - GetTransform()->position) * m_maxSpeed;
}

void RangedCombatEnemy::SetAccelerationRate(const float rate)
{
	m_accelerationRate = rate;
}

void RangedCombatEnemy::Seek()
{
	// Find Next Waypoint if within 10px of the current waypoint
	if(Util::Distance(m_patrolPath[m_wayPoint], GetTransform()->position) < 10)
	{
		// check to see if you are at the last point in the path
		if(++m_wayPoint == m_patrolPath.size())
		{
			// if so...reset
			m_wayPoint = 0;
		}
		SetTargetPosition(m_patrolPath[m_wayPoint]);
	}


	SetDesiredVelocity(GetTargetPosition());

	const glm::vec2 steering_direction = GetDesiredVelocity() - GetCurrentDirection();

	LookWhereIAmGoing(steering_direction);

	GetRigidBody()->acceleration = GetCurrentDirection() * GetAccelerationRate();
}

void RangedCombatEnemy::LookWhereIAmGoing(const glm::vec2 target_direction)
{
	const auto target_rotation = Util::SignedAngle(GetCurrentDirection(), target_direction);
	if (GetCollisionWhiskers()[0])
	{
		SetCurrentHeading(GetCurrentHeading() + GetTurnRate());
	}
	else if (GetCollisionWhiskers()[2])
	{
		SetCurrentHeading(GetCurrentHeading() - GetTurnRate());
	}
	else if (abs(target_rotation) > m_turnRate)
	{
		SetCurrentHeading(GetCurrentHeading() + GetTurnRate() * Util::Sign(target_rotation));
	}
	UpdateWhiskers(GetWhiskerAngle()); // New for Lab 3.
}

void RangedCombatEnemy::BuildPatrolPath()
{
	m_patrolPath.push_back(glm::vec2(760, 40)); // Top Right corner node
	m_patrolPath.push_back(glm::vec2(760, 560)); // Bottom Right corner node
	m_patrolPath.push_back(glm::vec2(40, 560)); // Bottom Left corner node
	m_patrolPath.push_back(glm::vec2(40, 40)); // Top Left corner node
	m_wayPoint = 0;

	SetTargetPosition(m_patrolPath[m_wayPoint]); // Top Right to Start
}

void RangedCombatEnemy::Move()
{
	Seek(); // Get our target for this frame.

	// Kinematic equation: final_position = position + velocity * time + 0.5*acceleration * time*time
	const auto delta_time = Game::Instance().GetDeltaTime();

	// compute the position term
	const glm::vec2 initial_position = GetTransform()->position;

	// compute the velocity term
	const glm::vec2 velocity_term = GetRigidBody()->velocity * delta_time;

	// compute the acceleration term
	const glm::vec2 acceleration_term = GetRigidBody()->acceleration * 0.5f;// *dt;


	// compute the new position
	glm::vec2 final_position = initial_position + velocity_term + acceleration_term;

	GetTransform()->position = final_position;

	// add our acceleration to velocity
	GetRigidBody()->velocity += GetRigidBody()->acceleration;

	// clamp our velocity at max speed
	GetRigidBody()->velocity = Util::Clamp(GetRigidBody()->velocity, GetMaxSpeed());
}

void RangedCombatEnemy::CheckBounds(){}

void RangedCombatEnemy::Reset()
{
	GetTransform()->position = m_startPos;
}

void RangedCombatEnemy::Patrol()
{
	if(GetActionState() != ActionState::PATROL)
	{
		// Initialize
		SetActionState(ActionState::PATROL);
	}
	Move();
}

void RangedCombatEnemy::MoveToPlayer()
{
	if(GetActionState() != ActionState::MOVE_TO_PLAYER)
	{
		SetActionState(ActionState::MOVE_TO_PLAYER);
	}

	// MoveToPlayer Algorithm
}

void RangedCombatEnemy::Flee()
{
	if (GetActionState() != ActionState::FLEE)
	{
		SetActionState(ActionState::FLEE);
	}
	//Flee();
}

void RangedCombatEnemy::MoveToLOS()
{
	if (GetActionState() != ActionState::MOVE_TO_LOS)
	{
		SetActionState(ActionState::MOVE_TO_LOS);
	}

	// MoveToLOS Algorithm
}

void RangedCombatEnemy::MoveToRange()
{
	if (GetActionState() != ActionState::MOVE_TO_RANGE)
	{
		SetActionState(ActionState::MOVE_TO_RANGE);
	}
	// MoveToRange Algorithm
}

void RangedCombatEnemy::MoveToCover()
{
	if (GetActionState() != ActionState::MOVE_TO_COVER)
	{
		SetActionState(ActionState::MOVE_TO_COVER);
	}
	// MoveToCover Algorithm
}

void RangedCombatEnemy::WaitBehindCover()
{
	if (GetActionState() != ActionState::WAIT_BEHIND_COVER)
	{
		SetActionState(ActionState::WAIT_BEHIND_COVER);
	}
	// WaitBehindCover Algorithm
}

void RangedCombatEnemy::Attack()
{
	auto scene = dynamic_cast<PlayScene*>(m_pScene);

	if (GetActionState() != ActionState::ATTACK)
	{
		SetActionState(ActionState::ATTACK);

		m_fireCounter = 0;
	}
	// Attack Action Algorithm


	/*glm::vec2 target_direction = Util::Normalize(scene->GetTarget()->GetTransform()->position - GetTransform()->position);
	LookWhereIAmGoing(target_direction);

	if(m_fireCounter++ % m_fireCounterMax == 0)
	{
		scene->SpawnEnemyTorpedo();
	}*/

}

DecisionTree* RangedCombatEnemy::GetTree() const
{
	return m_tree;
}

void RangedCombatEnemy::m_buildTree()
{
	// Create and add the root node - Health Condition
	m_tree->SetEnemyHealthNode(new EnemyHealthCondition(this));
	m_tree->GetTree().push_back(m_tree->GetEnemyHealthNode());

	// Left SubTree Level 1 - Flee Action
	TreeNode* fleeNode = m_tree->AddNode(m_tree->GetEnemyHealthNode(), new FleeAction(this), TreeNodeType::LEFT_TREE_NODE);
	m_tree->GetTree().push_back(fleeNode);

	// Right SubTree Level 1 - Enemy Hit Condition
	m_tree->SetEnemyHitNode(new EnemyHitCondition(this));
	m_tree->AddNode(m_tree->GetEnemyHealthNode(), m_tree->GetEnemyHitNode(), TreeNodeType::RIGHT_TREE_NODE);
	m_tree->GetTree().push_back(m_tree->GetEnemyHitNode());

	// Left SubTree Level 2 - Player Detected Condition
	m_tree->SetPlayerDetectedNode(new PlayerDetectedCondition(this));
	m_tree->AddNode(m_tree->GetEnemyHitNode(), m_tree->GetPlayerDetectedNode(), TreeNodeType::LEFT_TREE_NODE);
	m_tree->GetTree().push_back(m_tree->GetPlayerDetectedNode());

	// Right SubTree Level 2 - Right LOS Condition
	LOSCondition* LOSNodeRight = new LOSCondition(this);
	m_tree->AddNode(m_tree->GetEnemyHitNode(), LOSNodeRight, TreeNodeType::RIGHT_TREE_NODE);
	m_tree->GetTree().push_back(LOSNodeRight);

	// Left Left Sub-Tree Level 3 - Patrol Action
	TreeNode* patrolNode = m_tree->AddNode(m_tree->GetPlayerDetectedNode(), new PatrolAction(this), TreeNodeType::LEFT_TREE_NODE);
	m_tree->GetTree().push_back(patrolNode);

	// Left Right Sub-Tree Level 3 - Left LOS Condition
	LOSCondition* LOSNodeLeft = new LOSCondition(this);
	m_tree->AddNode(m_tree->GetPlayerDetectedNode(), LOSNodeLeft, TreeNodeType::RIGHT_TREE_NODE);
	m_tree->GetTree().push_back(LOSNodeLeft);

	// Right Left Sub-Tree Level 3 - Wait Behind Cover Action
	TreeNode* waitBehindCoverNode = m_tree->AddNode(LOSNodeRight, new WaitBehindCoverAction(this), TreeNodeType::LEFT_TREE_NODE);
	m_tree->GetTree().push_back(waitBehindCoverNode);

	// Right Right Sub-Tree Level 3 - Move To Cover Action
	TreeNode* moveToCoverNode = m_tree->AddNode(LOSNodeRight, new MoveToCoverAction(this), TreeNodeType::RIGHT_TREE_NODE);
	m_tree->GetTree().push_back(moveToCoverNode);

	// Left Sub-Tree Level 4 - Move to LOS Action
	TreeNode* moveToLOSNode = m_tree->AddNode(LOSNodeLeft, new MoveToLOSAction(this), TreeNodeType::LEFT_TREE_NODE);
	m_tree->GetTree().push_back(moveToLOSNode);

	// Right Sub-Tree Level 4 - Ranged Combat Condition
	m_tree->SetRangedCombatNode(new RangedCombatCondition(this));
	m_tree->AddNode(LOSNodeLeft, m_tree->GetRangedCombatNode(), TreeNodeType::RIGHT_TREE_NODE);
	m_tree->GetTree().push_back(m_tree->GetRangedCombatNode());

	// Left Sub-Tree Level 5 - MoveToRange Action
	TreeNode* moveToRangeNode = m_tree->AddNode(m_tree->GetRangedCombatNode(), new MoveToRangeAction(this), TreeNodeType::LEFT_TREE_NODE);
	m_tree->GetTree().push_back(moveToRangeNode);

	// Right Sub-Tree Level 5 - Attack Action
	TreeNode* attackNode = m_tree->AddNode(m_tree->GetRangedCombatNode(), new AttackAction(this), TreeNodeType::RIGHT_TREE_NODE);
	m_tree->GetTree().push_back(attackNode);
}
