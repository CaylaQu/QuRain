#include "Starship2.h"
#include "TextureManager.h"
#include "Util.h"
#include "Game.h"

Starship2::Starship2() : m_startPos(glm::vec2(200.0f, 200.0f)),
m_maxSpeed(20.0f), m_turnRate(10.0f), m_accelerationRate(4.0f)
{
	TextureManager::Instance().Load("../Assets/textures/d7_small.png", "Starship2");

	const auto size = TextureManager::Instance().GetTextureSize("Starship2");
	SetWidth(static_cast<int>(size.x));
	SetHeight(static_cast<int>(size.y));
	GetTransform()->position = m_startPos;
	GetRigidBody()->velocity = glm::vec2(0, 0);
	GetRigidBody()->acceleration = glm::vec2(0, 0);
	GetRigidBody()->isColliding = false;
	SetCurrentHeading(0.0f);


	SetType(GameObjectType::SPACE_SHIP1);
}



Starship2::~Starship2()
= default;

void Starship2::Draw()
{
	// draw the target
	TextureManager::Instance().Draw("Starship2", GetTransform()->position, GetCurrentHeading(), 255, true);
}

void Starship2::Update()
{
	Move();
	CheckBounds();
}

void Starship2::Clean()
{
}

float Starship2::GetMaxSpeed() const
{
	return m_maxSpeed;
}

float Starship2::GetDesiredVelocity() const
{
	return m_turnRate;
}

float Starship2::GetAccelerationRate() const
{
	return m_accelerationRate;
}

float Starship2::GetTurnRate() const
{
	return m_turnRate;
}

void Starship2::SetMaxSpeed(float speed)
{
	m_maxSpeed = speed;
}

void Starship2::SetTurnRate(float angle)
{
	m_turnRate = angle;
}

void Starship2::SetDesiredVelocity(glm::vec2 target_position)
{
	m_desieredVelocity = Util::Normalize(target_position - GetTransform()->position) * m_maxSpeed;
}

void Starship2::SetAccelerationRate(float rate)
{
	m_accelerationRate = rate;
}

void Starship2::Move()
{
	Flee();

	auto delta_time = Game::Instance().GetDeltaTime();

	const glm::vec2 initial_poition = GetTransform()->position;

	const glm::vec2 velocity_term = GetRigidBody()->velocity * delta_time;

	const glm::vec2 acceleration_term = GetRigidBody()->acceleration * 0.5f;


	const glm::vec2 final_position = initial_poition + velocity_term + acceleration_term;

	GetTransform()->position = final_position;

	GetRigidBody()->velocity += GetRigidBody()->acceleration;

	GetRigidBody()->velocity = Util::Clamp(GetRigidBody()->velocity, GetMaxSpeed());
}

void Starship2::CheckBounds() {}

void Starship2::Flee()
{
	SetDesiredVelocity(GetTargetPosition());

	const glm::vec2 steering_direction = GetDesiredVelocity() + GetCurrentDirection();
	auto target_direction = GetTargetPosition() + GetTransform()->position;
	target_direction = Util::Normalize(target_direction);

	LookWhereIAmGoing(target_direction);

	GetRigidBody()->acceleration = GetCurrentDirection() * GetAccelerationRate();

}

void Starship2::LookWhereIAmGoing(glm::vec2 target_direction)
{
	const auto target_rotation = Util::SignedAngle(GetCurrentDirection(), target_direction);

	if (abs(target_rotation) > m_turnRate)
	{
		SetCurrentHeading(GetCurrentHeading() + GetTurnRate() * Util::Sign(target_rotation));
	}

}

void Starship2::Reset()
{
	GetTransform()->position = m_startPos;
}
