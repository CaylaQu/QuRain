#include "Megaman.h"
#include "TextureManager.h"
#include "Util.h"
#include "Game.h"


Megaman::Megaman() : m_startPos( glm::vec2(300.0f, 500.0f) ),
	m_maxSpeed(20.0f), m_turnRate(5.0f), m_accelerationRate(2.0f)
{
	TextureManager::Instance().Load("../Assets/textures/megaman_small.png","mm");

	const auto size = TextureManager::Instance().GetTextureSize("mm");
	SetWidth(static_cast<int>(size.x));
	SetHeight(static_cast<int>(size.y));
	GetTransform()->position = m_startPos;
	GetRigidBody()->velocity = glm::vec2(0, 0);
	GetRigidBody()->acceleration = glm::vec2(0, 0);
	GetRigidBody()->isColliding = false;
	SetCurrentHeading(0.0f); // current facing angle
	// New for Lab 3
	SetLOSDistance(300.0f);
	SetWhiskerAngle(45.0f);

	SetType(GameObjectType::STAR_SHIP);
}

Megaman::~Megaman()
= default;

void Megaman::Draw()
{
	// draw the target
	TextureManager::Instance().Draw("mm", GetTransform()->position, GetCurrentHeading(), 255, true);
}

void Megaman::Update()
{
	/*Move();
	CheckBounds();*/
}

void Megaman::Clean()
{

}

float Megaman::GetMaxSpeed() const
{
	return m_maxSpeed;
}

float Megaman::GetTurnRate() const
{
	return m_turnRate;
}

glm::vec2 Megaman::GetDesiredVelocity() const
{
	return m_desiredVelocity;
}

float Megaman::GetAccelerationRate() const
{
	return m_accelerationRate;
}

void Megaman::SetMaxSpeed(float speed)
{
	m_maxSpeed = speed;
}

void Megaman::SetTurnRate(float angle)
{
	m_turnRate = angle;
}

void Megaman::SetDesiredVelocity(glm::vec2 target_position)
{
	m_desiredVelocity = Util::Normalize(target_position - GetTransform()->position) * m_maxSpeed;
}

void Megaman::SetAccelerationRate(float rate)
{
	m_accelerationRate = rate;
}

void Megaman::Seek()
{
	SetDesiredVelocity(GetTargetPosition());

	const glm::vec2 steering_direction = GetDesiredVelocity() - GetCurrentDirection();

	LookWhereIAmGoing(steering_direction);

	GetRigidBody()->acceleration = GetCurrentDirection() * GetAccelerationRate();
}

void Megaman::LookWhereIAmGoing(glm::vec2 target_direction)
{
	// Old version.
	//const auto target_rotation = Util::SignedAngle(GetCurrentDirection(), target_direction);
	//if (abs(target_rotation) > m_turnRate) // Do I still need to rotate?
	//{
	//	SetCurrentHeading(GetCurrentHeading() + GetTurnRate() * Util::Sign(target_rotation));
	//}

	// New for Lab 3 version 1. A bit jittery.
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

void Megaman::Move()
{
	Seek(); // Get our target for this frame.

	// Kinematic equation: final_position = position + velocity * time + 0.5*acceleration * time*time
	auto delta_time = Game::Instance().GetDeltaTime();

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

void Megaman::CheckBounds(){}

void Megaman::Reset()
{
	GetTransform()->position = m_startPos;
}
