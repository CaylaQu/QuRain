#include "Agent2.h"

#include "Util.h"

Agent2::Agent2()
{
}

Agent2::~Agent2()
= default;

glm::vec2 Agent2::GetTargetPosition() const
{
	return m_targetPosition;
}

glm::vec2 Agent2::GetCurrentDirection() const
{
	return m_currentDirection;
}

float Agent2::GetLOSDistance() const
{
	return m_LOSDistance;
}

bool Agent2::HasLOS() const
{
	return m_hasLOS;
}

float Agent2::GetCurrentHeading() const
{
	return m_currentHeading;
}

glm::vec4 Agent2::GetLOSColour() const
{
	return m_LOSColour;
}

glm::vec2 Agent2::GetLeftLOSEndPoint() const
{
	return m_leftLOSEndPoint;
}

glm::vec2 Agent2::GetMiddleLOSEndPoint() const
{
	return m_middleLOSEndPoint;
}

glm::vec2 Agent2::GetRightLOSEndPoint() const
{
	return m_rightLOSEndPoint;
}

glm::vec2 Agent2::Get2RightLOSEndPoint() const
{
	return m_2rightLOSEndPoint;
}

glm::vec2 Agent2::Get2LeftLOSEndPoint() const
{
	return m_2leftLOSEndPoint;
}

bool* Agent2::GetCollisionWiskers()
{
	return m_collisionWiskers;
}

glm::vec4 Agent2::GetLineColour(int index)
{
	return m_lineColour[index];
}

float Agent2::GetWiskerAngle() const
{
	return m_wiskerAngle;
}

void Agent2::SetTargetPosition(const glm::vec2 new_position)
{
	m_targetPosition = new_position;
}

void Agent2::SetCurrentDirection(const glm::vec2 new_direction)
{
	m_currentDirection = new_direction;
}

void Agent2::SetLOSDistance(const float distance)
{
	m_LOSDistance = distance;
}

void Agent2::SetHasLOS(const bool state)
{
	m_hasLOS = state;
	m_LOSColour = (m_hasLOS) ? glm::vec4(0, 1, 0, 1) : glm::vec4(1, 0, 0, 1);
}

void Agent2::SetCurrentHeading(const float heading)
{
	m_currentHeading = heading;
	ChangeDirection();
}

void Agent2::SetLOSColour(const glm::vec4 colour)
{
	m_LOSColour = colour;
}

void Agent2::SetLeftLOSEndPoint(glm::vec2 point)
{
	m_leftLOSEndPoint = point;
}

void Agent2::SetMiddleLOSEndPoint(glm::vec2 point)
{
	m_middleLOSEndPoint = point;
}

void Agent2::SetRightLOSEndPoint(glm::vec2 point)
{
	m_rightLOSEndPoint = point;
}

void Agent2::Set2LeftLOSEndPoint(glm::vec2 point)
{
	m_2leftLOSEndPoint = point;
}

void Agent2::Set2RightLOSEndPoint(glm::vec2 point)
{
	m_2rightLOSEndPoint = point;
}

void Agent2::SetLineColour(int index, glm::vec4 colour)
{
	m_lineColour[index] = colour;
}

void Agent2::SetWiskerAngle(float angle)
{
	m_wiskerAngle = angle;
}

void Agent2::UpdateWiskers(float angle)
{
	SetWiskerAngle(angle);


	float x = sin((GetCurrentHeading() - m_wiskerAngle + 90) * Util::Deg2Rad);
	float y = cos((GetCurrentHeading() - m_wiskerAngle + 90) * Util::Deg2Rad);
	SetLeftLOSEndPoint(GetTransform()->position + glm::vec2(x, -y) * (GetLOSDistance() * 0.75f));

	x = sin((GetCurrentHeading() + m_wiskerAngle + 90) * Util::Deg2Rad);
	y = cos((GetCurrentHeading() + m_wiskerAngle + 90) * Util::Deg2Rad);
	SetRightLOSEndPoint(GetTransform()->position + glm::vec2(x, -y) * (GetLOSDistance() * 0.75f));

	x = sin((GetCurrentHeading() + m_wiskerAngle + 135) * Util::Deg2Rad);
	y = cos((GetCurrentHeading() + m_wiskerAngle + 135) * Util::Deg2Rad);
	Set2RightLOSEndPoint(GetTransform()->position + glm::vec2(x, -y) * (GetLOSDistance() * 0.75f));

	x = sin((GetCurrentHeading() - m_wiskerAngle + 45) * Util::Deg2Rad);
	y = cos((GetCurrentHeading() - m_wiskerAngle + 45) * Util::Deg2Rad);
	Set2LeftLOSEndPoint(GetTransform()->position + glm::vec2(x, -y) * (GetLOSDistance() * 0.75f));

	x = sin((GetCurrentHeading() + m_wiskerAngle + 45) * Util::Deg2Rad);
	y = cos((GetCurrentHeading() + m_wiskerAngle + 45) * Util::Deg2Rad);
	SetMiddleLOSEndPoint(GetTransform()->position + glm::vec2(x, -y) * (GetLOSDistance() * 0.75f));
	//SetMiddleLOSEndPoint(GetTransform()->position + GetCurrentHeading() * GetLOSDistance());
}

void Agent2::ChangeDirection()
{
	const auto x = cos(m_currentHeading * Util::Deg2Rad);
	const auto y = sin(m_currentHeading * Util::Deg2Rad);
	m_currentDirection = glm::vec2(x, y);
}
