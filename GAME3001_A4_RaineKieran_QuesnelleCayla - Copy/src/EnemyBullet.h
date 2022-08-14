#pragma once
#ifndef __ENEMY_BULLET__
#define __ENEMY_BULLET__
#include "Sprite.h"
#include "EnemyBulletAnimationState.h"
class EnemyBullet : public Sprite
{
public:

	EnemyBullet(float speed = 0.0f, glm::vec2 direction = { 0,0 });
	~EnemyBullet();

	void Draw() override;
	void Update() override;
	void Clean() override;

	void SetAnimationState(EnemyBulletAnimationState newstate);

private:
	void BuildAnimation(); 
	EnemyBulletAnimationState m_currentAnimationState; 
	float m_speed;
	glm::vec2 m_direction;

};




#endif