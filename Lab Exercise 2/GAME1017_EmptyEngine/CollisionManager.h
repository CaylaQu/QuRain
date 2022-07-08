#pragma once
#ifndef _COLLISIONMANAGER_H_
#define _COLLISIONMANAGER_H_

#include <iostream>
#include <SDL.h>
#include "MathManager.h"

class CollisionManager
{
public:
	// AABB-AABB overloads.
	static bool AABBCheck(const SDL_Rect& object1, const SDL_Rect& object2); // Two int-based Rects.
	static bool AABBCheck(const SDL_Rect& object1, const SDL_FRect& object2); // Int-based Rect, Float-based Rect.
	static bool AABBCheck(const SDL_FRect& object1, const SDL_FRect& object2); // Two float-based Rects.

	// AABB-Line overloads.
	static bool AABBLineCheck(const SDL_Rect& object1, SDL_Point object2_start, SDL_Point object2_end); // Int-based.
	static bool AABBLineCheck(const SDL_FRect& object1, SDL_Point object2_start, SDL_Point object2_end); // Int-based line, Float-based Rect.
	static bool AABBLineCheck(const SDL_FRect& object1, SDL_FPoint object2_start, SDL_FPoint object2_end); // Float-based.

	// Circle-AABB overloads.
	static bool CircleAABBCheck(const SDL_Point object1, const double r, const SDL_Rect& object2); // Int-based.
	static bool CircleAABBCheck(const SDL_FPoint object1, const double r, const SDL_FRect& object2); // Float-based.

	// Circle-Circle overloads.
	static bool CircleCircleCheck(const SDL_Point object1, const SDL_Point object2, const double r1, const double r2 = 0.0); // Int-based.
	static bool CircleCircleCheck(const SDL_FPoint object1, const SDL_FPoint object2, const double r1, const double r2 = 0.0); // Float-based.
	
	// Line-Point overloads.
	static bool LinePointCheck(const SDL_Point object1_start, const SDL_Point object1_end, const SDL_Point object2); // Int-based.
	static bool LinePointCheck(const SDL_FPoint object1_start, const SDL_FPoint object1_end, const SDL_FPoint object2); // Float-based.

	// Point-AABB overloads.
	static bool PointAABBCheck(const SDL_Point object1, const SDL_Rect& object2); // Int-based.
	static bool PointAABBCheck(const SDL_Point object1, const SDL_FRect& object2); // Int-based point, Float-based Rect.
	static bool PointAABBCheck(const SDL_FPoint object1, const SDL_FRect& object2); // Float-based.
private:
	CollisionManager() {}
};

typedef CollisionManager COMA;

#endif