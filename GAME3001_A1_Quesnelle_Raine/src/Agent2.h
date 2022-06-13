#pragma once
#ifndef __AGENT2__
#define __AGENT2__

#include <glm/vec4.hpp>
#include "NavigationObject.h"

class Agent2 : public NavigationObject
{
public:
	Agent2();
	~Agent2();

	// Inherited via GameObject
	void Draw() override = 0;
	void Update() override = 0;
	void Clean() override = 0;

	// getters
	[[nodiscard]] glm::vec2 GetTargetPosition() const;
	[[nodiscard]] glm::vec2 GetCurrentDirection() const;
	[[nodiscard]] float GetLOSDistance() const;
	[[nodiscard]] bool HasLOS() const;
	[[nodiscard]] float GetCurrentHeading() const;
	[[nodiscard]] glm::vec4 GetLOSColour() const;

	glm::vec2 GetLeftLOSEndPoint() const;
	glm::vec2 GetMiddleLOSEndPoint() const;
	glm::vec2 GetRightLOSEndPoint() const;
	bool* GetCollisionWiskers();
	glm::vec4 GetLineColour(int index);
	float GetWiskerAngle() const;

	// setters
	void SetTargetPosition(glm::vec2 new_position);
	void SetCurrentDirection(glm::vec2 new_direction);
	void SetLOSDistance(float distance);
	void SetHasLOS(bool state);
	void SetCurrentHeading(float heading);
	void SetLOSColour(glm::vec4 colour);

	void SetLeftLOSEndPoint(glm::vec2 point);
	void SetMiddleLOSEndPoint(glm::vec2 point);
	void SetRightLOSEndPoint(glm::vec2 point);
	void SetLineColour(int index, glm::vec4 colour);
	void SetWiskerAngle(float angle);

	void UpdateWiskers(float angle);

private:
	void ChangeDirection(); // From scalar to vec2.

	float m_currentHeading; // Scalar angle in degrees.
	glm::vec2 m_currentDirection; // Vec2 direction/angle.
	glm::vec2 m_targetPosition; // Where the agent wants to be.

	// LOS (line of sight)
	float m_LOSDistance; // (Position + direction) * distance
	bool m_hasLOS; // Used for collision.
	glm::vec4 m_LOSColour;

	glm::vec2 m_leftLOSEndPoint;
	glm::vec2 m_middleLOSEndPoint;
	glm::vec2 m_rightLOSEndPoint;
	//glm::vec2 m_2rightLOSEndPoint;
	//glm::vec2 m_2leftLOSEndPoint;

	glm::vec4 m_lineColour[3]; //Left, Middle, Right. 2nd right, 2nd left.
	bool m_collisionWiskers[3];
	float m_wiskerAngle;
};



#endif /* defined ( __AGENT__) */
