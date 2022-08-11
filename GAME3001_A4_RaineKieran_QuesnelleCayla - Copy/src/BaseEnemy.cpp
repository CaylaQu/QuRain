#include "BaseEnemy.h"

#include "TextureManager.h"
#include "Util.h"

BaseEnemy::BaseEnemy()
{

	GetTransform()->position = m_startPos;
	GetRigidBody()->velocity = glm::vec2(0, 0);
	GetRigidBody()->acceleration = glm::vec2(0, 0);
	GetRigidBody()->isColliding = false;
	SetCurrentHeading(0.0f); // current facing angle
	// New for Lab 3
	SetLOSDistance(300.0f);
	SetWhiskerAngle(45.0f);

	SetLOSColour(glm::vec4(1, 0, 0, 1));

	SetType(GameObjectType::AGENT);
}

BaseEnemy::~BaseEnemy()
= default;

void BaseEnemy::Draw()
{
	TextureManager::Instance().Draw("mm", GetTransform()->position, GetCurrentHeading(), 255, true);

	// draw the line of sight
	Util::DrawLine(GetTransform()->position + GetCurrentDirection() * 0.5f * static_cast<float>(GetWidth()),
		GetTransform()->position + GetCurrentDirection() * GetLOSDistance(), GetLOSColour());

	Util::DrawCircle(GetTransform()->position, 100,GetLOSColour(),ShapeType::SYMMETRICAL,Renderer::Instance().GetRenderer());
}

void BaseEnemy::Update()
{
}

void BaseEnemy::Clean()
{
}

void BaseEnemy::EnemyPatrol()
{
}

void BaseEnemy::EnemyEngaged()
{
}

void BaseEnemy::EnemyIdle()
{
}

//bool BaseEnemy::LOSDetectPlayer()
//{
//}

void BaseEnemy::LookWhereIAmGoing(glm::vec2 target_direction)
{
}

void BaseEnemy::Reset()
{
}

void BaseEnemy::CheckBounds()
{
}
