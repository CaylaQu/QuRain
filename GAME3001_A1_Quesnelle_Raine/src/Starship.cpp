#include "Starship.h"
#include "TextureManager.h"
#include "Util.h"
#include "Game.h"

Starship::Starship(): m_startPos( glm::vec2(400.0f, 400.0f) ),
	m_maxSpeed(20.0f), m_turnRate(10.0f), m_accelerationRate(4.0f)
{
	TextureManager::Instance().Load("../Assets/textures/d7_small.png","Starship");

	const auto size = TextureManager::Instance().GetTextureSize("Starship");
	SetWidth(static_cast<int>(size.x));
	SetHeight(static_cast<int>(size.y));
	GetTransform()->position = m_startPos;
	GetRigidBody()->velocity = glm::vec2(0 , 0);
	GetRigidBody()->acceleration = glm::vec2(0, 0);
	GetRigidBody()->isColliding = false;
	SetCurrentHeading(0.0f);

	
	SetType(GameObjectType::SPACE_SHIP);
}

Starship::~Starship()
= default;

void Starship::Draw()
{
	// draw the target
	TextureManager::Instance().Draw("Starship", GetTransform()->position, GetCurrentHeading(), 255, true);
}

void Starship::Update()
{
	Move();
	CheckBounds();
}

void Starship::Clean()
{
}

float Starship::GetMaxSpeed() const
{
	return m_maxSpeed;
}

float Starship::GetDesiredVelocity() const
{
	return m_turnRate;
}

float Starship::GetAccelerationRate() const
{
	return m_accelerationRate;
}

float Starship::GetTurnRate() const
{
	return m_turnRate;
}

void Starship::SetMaxSpeed(float speed)
{
	m_maxSpeed = speed;
}

void Starship::SetTurnRate(float angle)
{
	m_turnRate = angle;
}

void Starship::SetDesiredVelocity(glm::vec2 target_position)
{
	m_desieredVelocity = Util::Normalize(target_position - GetTransform()->position) * m_maxSpeed;
}

void Starship::SetAccelerationRate(float rate)
{
	m_accelerationRate = rate;
}

void Starship::Move()
{
	Seek();

	auto delta_time = Game::Instance().GetDeltaTime();

	const glm::vec2 initial_poition = GetTransform()->position;

	const glm::vec2 velocity_term = GetRigidBody()->velocity * delta_time;

	const glm::vec2 acceleration_term = GetRigidBody()->acceleration * 0.5f;


	const glm::vec2 final_position = initial_poition + velocity_term + acceleration_term;

	GetTransform()->position = final_position;

	GetRigidBody()->velocity += GetRigidBody()->acceleration;

	GetRigidBody()->velocity = Util::Clamp(GetRigidBody()->velocity, GetMaxSpeed());
}

void Starship::CheckBounds(){}

void Starship::Seek()
{
	SetDesiredVelocity(GetTargetPosition());

	const glm::vec2 steering_direction = GetDesiredVelocity() - GetCurrentDirection();
	auto target_direction = GetTargetPosition() - GetTransform()->position;
	target_direction = Util::Normalize(target_direction);

	LookWhereIAmGoing(target_direction);

	GetRigidBody()->acceleration = GetCurrentDirection() * GetAccelerationRate();

}

void Starship::LookWhereIAmGoing(glm::vec2 target_direction)
{
	const auto target_rotation = Util::SignedAngle(GetCurrentDirection(), target_direction );

	if (abs(target_rotation) > m_turnRate)
	{
		SetCurrentHeading(GetCurrentHeading() + GetTurnRate() * Util::Sign(target_rotation));
	}

}

void Starship::Reset()
{
	GetTransform()->position = m_startPos;
}
