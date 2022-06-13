#include "Starship4.h"
#include "TextureManager.h"
#include "Util.h"
#include "Game.h"


Starship4::Starship4() : m_startPos(glm::vec2(300.0f, 500.0f)),
m_maxSpeed(20.0f), m_turnRate(5.0f), m_accelerationRate(2.0f)
{
	TextureManager::Instance().Load("../Assets/textures/d7_small.png", "d7");

	const auto size = TextureManager::Instance().GetTextureSize("d7");
	SetWidth(static_cast<int>(size.x));
	SetHeight(static_cast<int>(size.y));
	GetTransform()->position = m_startPos;
	GetRigidBody()->velocity = glm::vec2(0, 0);
	GetRigidBody()->acceleration = glm::vec2(0, 0);
	GetRigidBody()->isColliding = false;
	SetCurrentHeading(0.0f); // current facing angle

	SetLOSDistance(300.0f);
	SetWiskerAngle(45.0f);

	SetType(GameObjectType::SPACE_SHIP4);
}

Starship4::~Starship4()
= default;

void Starship4::Draw()
{
	// draw the target
	TextureManager::Instance().Draw("d7", GetTransform()->position, GetCurrentHeading(), 255, true);
}

void Starship4::Update()
{
	Move();
	CheckBounds();
}

void Starship4::Clean()
{

}

float Starship4::GetMaxSpeed() const
{
	return m_maxSpeed;
}

float Starship4::GetTurnRate() const
{
	return m_turnRate;
}

glm::vec2 Starship4::GetDesiredVelocity() const
{
	return m_desiredVelocity;
}

float Starship4::GetAccelerationRate() const
{
	return m_accelerationRate;
}

void Starship4::SetMaxSpeed(float speed)
{
	m_maxSpeed = speed;
}

void Starship4::SetTurnRate(float angle)
{
	m_turnRate = angle;
}

void Starship4::SetDesiredVelocity(glm::vec2 target_position)
{
	m_desiredVelocity = Util::Normalize(target_position - GetTransform()->position) * m_maxSpeed;
}

void Starship4::SetAccelerationRate(float rate)
{
	m_accelerationRate = rate;
}

void Starship4::Seek() //obstacle avoidance seek 
{
	SetDesiredVelocity(GetTargetPosition());

	const glm::vec2 steering_direction = GetDesiredVelocity() - GetCurrentDirection();

	LookWhereIAmGoing(steering_direction);

	GetRigidBody()->acceleration = GetCurrentDirection() * GetAccelerationRate();
}

void Starship4::LookWhereIAmGoing(glm::vec2 target_direction)
{

	const auto target_rotation = Util::SignedAngle(GetCurrentDirection(), target_direction);


	if (GetCollisionWiskers()[0])
	{
		SetCurrentHeading(GetCurrentHeading() + GetTurnRate());
	}
	else if (GetCollisionWiskers()[2])
	{
		SetCurrentHeading(GetCurrentHeading() - GetTurnRate());
	}
	else if (abs(target_rotation) > m_turnRate)
	{
		SetCurrentHeading(GetCurrentHeading() + GetTurnRate() * Util::Sign(target_rotation));
	}

	UpdateWiskers(GetWiskerAngle());


	//const auto target_rotation = Util::SignedAngle(GetCurrentDirection(), target_direction);

	//if (abs(target_rotation) > m_turnRate) // Do I still need to rotate?
	//{
	//	SetCurrentHeading(GetCurrentHeading() + GetTurnRate() * Util::Sign(target_rotation));
	//}

	//UpdateWiskers(GetWiskerAngle());
}

void Starship4::Move()
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

void Starship4::CheckBounds() {}

void Starship4::Reset()
{
	GetTransform()->position = m_startPos;
}