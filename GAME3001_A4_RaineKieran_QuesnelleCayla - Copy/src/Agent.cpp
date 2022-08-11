#include "Agent.h"

#include "CollisionManager.h"
#include "Util.h"

Agent::Agent(): m_currentHeading(0.0f), m_LOSDistance(0.0f),
                m_hasLOS(false), m_whiskerAngle(0.0f), m_state()
{
}

Agent::~Agent()
= default;

glm::vec2 Agent::GetTargetPosition() const
{
	return m_targetPosition;
}

glm::vec2 Agent::GetCurrentDirection() const
{
	return m_currentDirection;
}

float Agent::GetLOSDistance() const
{
	return m_LOSDistance;
}

bool Agent::HasLOS() const
{
	return m_hasLOS;
}

float Agent::GetCurrentHeading() const
{
	return m_currentHeading;
}

glm::vec4 Agent::GetLOSColour() const
{
	return m_LOSColour;
}

glm::vec2 Agent::GetLeftLOSEndPoint() const
{
	return m_leftLOSEndPoint;
}

glm::vec2 Agent::GetMiddleLOSEndPoint() const
{
	return m_middleLOSEndPoint;
}

glm::vec2 Agent::GetRightLOSEndPoint() const
{
	return m_rightLOSEndPoint;
}

bool* Agent::GetCollisionWhiskers()
{
	return m_collisionWhiskers; // Returns array by address.
}

glm::vec4 Agent::GetLineColor(const int index) const
{
	return m_lineColor[index];
}

float Agent::GetWhiskerAngle() const
{
	return m_whiskerAngle;
}

ActionState Agent::GetActionState() const
{
	return m_state;
}

int Agent::GetHealth() const
{
	return m_health;
}

void Agent::SetHealth(const int value)
{
	m_health = value;
}

void Agent::TakeDamage(const int value)
{
	m_health -= value;
}

void Agent::SetTargetPosition(const glm::vec2 new_position)
{
	m_targetPosition = new_position;
}

void Agent::SetCurrentDirection(const glm::vec2 new_direction)
{
	m_currentDirection = new_direction;
}

void Agent::SetLOSDistance(const float distance)
{
	m_LOSDistance = distance;
}

void Agent::SetHasLOS(const bool state)
{
	m_hasLOS = state;
	m_LOSColour = (m_hasLOS) ? glm::vec4(0, 1, 0, 1) : glm::vec4(1, 0, 0, 1);
}

void Agent::SetHasLOS(const bool state, glm::vec4 colour)
{
	m_hasLOS = state;
	m_LOSColour = (m_hasLOS) ? colour : glm::vec4(1, 0, 0, 1);
}

void Agent::SetCurrentHeading(const float heading)
{
	m_currentHeading = heading;
	ChangeDirection();
}

void Agent::SetLOSColour(const glm::vec4 colour)
{
	m_LOSColour = colour;
}

void Agent::SetLeftLOSEndPoint(const glm::vec2 point)
{
	m_leftLOSEndPoint = point;
}

void Agent::SetMiddleLOSEndPoint(const glm::vec2 point)
{
	m_middleLOSEndPoint = point;
}

void Agent::SetRightLOSEndPoint(const glm::vec2 point)
{
	m_rightLOSEndPoint = point;
}

void Agent::SetLineColor(const int index, const glm::vec4 color)
{
	m_lineColor[index] = color;
}

void Agent::SetWhiskerAngle(const float angle)
{
	m_whiskerAngle = angle;
}

void Agent::UpdateWhiskers(const float angle)
{
	SetWhiskerAngle(angle);
	SetMiddleLOSEndPoint(GetTransform()->position + GetCurrentDirection() * GetLOSDistance());

	double x = sin((GetCurrentHeading() - m_whiskerAngle + 90) * Util::Deg2Rad);
	double y = cos((GetCurrentHeading() - m_whiskerAngle + 90) * Util::Deg2Rad);
	SetLeftLOSEndPoint(GetTransform()->position + glm::vec2(x, -y) * (GetLOSDistance() * 0.75f));

	x = sin((GetCurrentHeading() + m_whiskerAngle + 90) * Util::Deg2Rad);
	y = cos((GetCurrentHeading() + m_whiskerAngle + 90) * Util::Deg2Rad);
	SetRightLOSEndPoint(GetTransform()->position + glm::vec2(static_cast<float>(x), static_cast<float>(-y)) * (GetLOSDistance() * 0.75f));
}

void Agent::SetActionState(const ActionState state)
{
	m_state = state;
}

bool Agent::CheckAgentLOSToTarget(Agent* agent, DisplayObject* target_object, const std::vector<Obstacle*>& obstacles)
{
	bool has_LOS = false; // default - no LOS
	SetHasLOS(has_LOS);

	const auto target_direction = target_object->GetTransform()->position - GetTransform()->position;
	const auto normalized_direction = Util::Normalize(target_direction); // points to the target - Vector of magnitude 1
	SetMiddleLOSEndPoint(GetTransform()->position + normalized_direction * GetLOSDistance());

	// if ship to target distance is less than or equal to the LOS Distance (Range)
	const auto agent_to_range = Util::GetClosestEdge(GetTransform()->position, target_object);
	if (agent_to_range <= GetLOSDistance())
	{
		// we are in range
		std::vector<DisplayObject*> contact_list;
		for (const auto obstacle : obstacles)
		{
			if (obstacle->GetType() == GameObjectType::NONE) { continue; }
			const auto agent_to_object_distance = Util::GetClosestEdge(GetTransform()->position, obstacle);
			if (agent_to_object_distance > agent_to_range) { continue; } // target is out of range

			contact_list.push_back(obstacle);
		}

		has_LOS = CollisionManager::LOSCheck(agent, GetMiddleLOSEndPoint(), contact_list, target_object);
	}
	agent->SetHasLOS(has_LOS);

	return has_LOS;
}

void Agent::ChangeDirection()
{
	const auto x = cos(m_currentHeading * Util::Deg2Rad);
	const auto y = sin(m_currentHeading * Util::Deg2Rad);
	m_currentDirection = glm::vec2(x, y);
}
