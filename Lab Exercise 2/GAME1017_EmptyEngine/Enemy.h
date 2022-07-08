#pragma once
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include <SDL.h>

class Enemy
{
private:
	SDL_Rect m_src, m_dst;
	int m_speed;
	int m_hits; // Maybe after 4 hits, the enemy is destroyed.

public:
	Enemy(SDL_Rect dst);
	void Update();
	void Render();
	SDL_Point GetPos() const { return {m_dst.x + m_dst.w/2, m_dst.y + m_dst.h/2}; }
	int& Hits() { return m_hits; } // Getter and setter.
};

#endif