#include "Enemy.h"
#include "Engine.h"
#include "TextureManager.h"
#include "EventManager.h"

Enemy::Enemy(SDL_Rect dst) :m_dst(dst), m_src({ 80,0,40,57 }), m_speed(1) { }

void Enemy::Update()
{
	m_dst.y += m_speed;
}

void Enemy::Render()
{
	SDL_RenderCopyEx(Engine::Instance().GetRenderer(), TEMA::GetTexture("enemy"), &m_src, &m_dst, 180.0, NULL, SDL_FLIP_NONE);
}
