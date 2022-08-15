#include "EnemyBullet.h"
#include "TextureManager.h"

EnemyBullet::EnemyBullet(float speed, glm::vec2 direction) : m_currentAnimationState(EnemyBulletAnimationState::FIRED), m_speed(speed)
{
	TextureManager::Instance().LoadSpriteSheet(
		"../Assets/sprites/torpedo.txt",
		"../Assets/sprites/torpedo.png",
		"torpedosheet");

	SetSpriteSheet(TextureManager::Instance().GetSpriteSheet("torpedosheet"));

	SetWidth(64);
	SetWidth(64); 

	GetTransform()->position = glm::vec2(400.0f, 300.0f);
	GetRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	GetRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	GetRigidBody()->isColliding = false;
	SetType(GameObjectType::PROJECTILE);


	m_direction = { direction.x * speed, direction.y * speed }; 
	BuildAnimation();
}

EnemyBullet::~EnemyBullet()
= default;

void EnemyBullet::Draw()
{
	switch(m_currentAnimationState)
	{
	case EnemyBulletAnimationState::FIRED:
		TextureManager::Instance().PlayAnimation("torpedosheet", GetAnimation("fired"),
			GetTransform()->position, 5.0, 0, 255, true);
		break;
	default:
		break;
	}
}

void EnemyBullet::Update()
{
	GetTransform()->position += m_direction;

}

void EnemyBullet::Clean()
{
}

void EnemyBullet::SetAnimationState(const EnemyBulletAnimationState newstate)
{
	m_currentAnimationState = newstate;

}

void EnemyBullet::BuildAnimation()
{
	auto fired_animation = Animation();

	fired_animation.name = "fired";
	fired_animation.frames.push_back(GetSpriteSheet()->GetFrame("fired1"));
	fired_animation.frames.push_back(GetSpriteSheet()->GetFrame("fired2"));
	fired_animation.frames.push_back(GetSpriteSheet()->GetFrame("fired3"));
	fired_animation.frames.push_back(GetSpriteSheet()->GetFrame("fired4"));
	fired_animation.frames.push_back(GetSpriteSheet()->GetFrame("fired5"));
	fired_animation.frames.push_back(GetSpriteSheet()->GetFrame("fired6"));
	fired_animation.frames.push_back(GetSpriteSheet()->GetFrame("fired7"));
	fired_animation.frames.push_back(GetSpriteSheet()->GetFrame("fired8"));

	SetAnimation(fired_animation);
}
