#include "CollisionManager.h"
#define BUFFER 0.2

bool CollisionManager::AABBCheck(const SDL_Rect& object1, const SDL_Rect& object2)
{
	return SDL_HasIntersection(&object1, &object2);
}

bool CollisionManager::AABBCheck(const SDL_Rect& object1, const SDL_FRect& object2)
{
	SDL_Rect r = MAMA::ConvertFRect2Rect(object2);
	return SDL_HasIntersection(&object1, &r);
}

bool CollisionManager::AABBCheck(const SDL_FRect& object1, const SDL_FRect& object2)
{
	SDL_Rect r1 = MAMA::ConvertFRect2Rect(object1);
	SDL_Rect r2 = MAMA::ConvertFRect2Rect(object2);
	return SDL_HasIntersection(&r1, &r2);
}

bool CollisionManager::AABBLineCheck(const SDL_Rect& object1, SDL_Point object2_start, SDL_Point object2_end)
{
	return SDL_IntersectRectAndLine(&object1, &object2_start.x, &object2_start.y, &object2_end.x, &object2_end.y);
}

bool CollisionManager::AABBLineCheck(const SDL_FRect& object1, SDL_Point object2_start, SDL_Point object2_end)
{
	SDL_Rect r = MAMA::ConvertFRect2Rect(object1);
	return SDL_IntersectRectAndLine(&r, &object2_start.x, &object2_start.y, &object2_end.x, &object2_end.y);
}

bool CollisionManager::AABBLineCheck(const SDL_FRect& object1, SDL_FPoint object2_start, SDL_FPoint object2_end)
{
	SDL_Rect r1 = MAMA::ConvertFRect2Rect(object1);
	SDL_Point p1 = MAMA::ConvertFPoint2Point(object2_start);
	SDL_Point p2 = MAMA::ConvertFPoint2Point(object2_end);
	return SDL_IntersectRectAndLine(&r1, &p1.x, &p1.y, &p2.x, &p2.y);
}

bool CollisionManager::CircleAABBCheck(const SDL_Point object1, const double r, const SDL_Rect& object2)
{
	double x1 = (double)object1.x;
	double y1 = (double)object1.y;
	if (object1.x < object2.x) // Circle center, rect left edge.
		x1 = (double)object2.x;
	else if (object1.x > object2.x + object2.w)
		x1 = (double)object2.x + (double)object2.w;
	if (object1.y < object2.y)
		y1 = (double)object2.y;
	else if (object1.y > object2.y + object2.h)
		y1 = (double)object2.y + (double)object2.h;

	return CircleCircleCheck({ (int)x1, (int)y1 }, object1, r);
}

bool CollisionManager::CircleAABBCheck(const SDL_FPoint object1, const double r, const SDL_FRect& object2)
{
	double x1 = (double)object1.x;
	double y1 = (double)object1.y;
	if (object1.x < object2.x) // Circle center, rect left edge.
		x1 = (double)object2.x;
	else if (object1.x > object2.x + object2.w)
		x1 = (double)object2.x + (double)object2.w;
	if (object1.y < object2.y)
		y1 = (double)object2.y;
	else if (object1.y > object2.y + object2.h)
		y1 = (double)object2.y + (double)object2.h;

	return CircleCircleCheck({ (float)x1, (float)y1 }, object1, r);
}

bool CollisionManager::CircleCircleCheck(const SDL_Point object1, const SDL_Point object2, const double r1, const double r2)
{
	return (MAMA::Distance((double)object1.x, (double)object2.x, (double)object1.y, (double)object2.y) < (r1+r2));
}

bool CollisionManager::CircleCircleCheck(const SDL_FPoint object1, const SDL_FPoint object2, const double r1, const double r2)
{
	return (MAMA::Distance((double)object1.x, (double)object2.x, (double)object1.y, (double)object2.y) < (r1 + r2));
}

bool CollisionManager::LinePointCheck(const SDL_Point object1_start, const SDL_Point object1_end, const SDL_Point object2)
{
	double distToStart = MAMA::Distance((double)object1_start.x, (double)object2.x, (double)object1_start.y, (double)object2.y);
	double distToEnd = MAMA::Distance((double)object1_end.x, (double)object2.x, (double)object1_end.y, (double)object2.y);

	double lineLength = MAMA::Distance((double)object1_start.x, (double)object1_end.x, (double)object1_start.y, (double)object1_end.y);

	double buffer = BUFFER; // Extra distance since line thickness is one pixel.
	
	if (distToStart + distToEnd <= lineLength + buffer)
		return true;
	return false;
}

bool CollisionManager::LinePointCheck(const SDL_FPoint object1_start, const SDL_FPoint object1_end, const SDL_FPoint object2)
{
	double distToStart = MAMA::Distance((double)object1_start.x, (double)object2.x, (double)object1_start.y, (double)object2.y);
	double distToEnd = MAMA::Distance((double)object1_end.x, (double)object2.x, (double)object1_end.y, (double)object2.y);

	double lineLength = MAMA::Distance((double)object1_start.x, (double)object1_end.x, (double)object1_start.y, (double)object1_end.y);

	double buffer = BUFFER; // Extra distance since line thickness is one pixel.
	
	if (distToStart + distToEnd <= lineLength + buffer)
		return true;
	return false;
}

bool CollisionManager::PointAABBCheck(const SDL_Point object1, const SDL_Rect &object2)
{
	return SDL_PointInRect(&object1, &object2);
}

bool CollisionManager::PointAABBCheck(const SDL_Point object1, const SDL_FRect &object2)
{
	SDL_Rect r = MAMA::ConvertFRect2Rect(object2);
	return SDL_PointInRect(&object1, &r);
}

bool CollisionManager::PointAABBCheck(const SDL_FPoint object1, const SDL_FRect &object2)
{
	SDL_Point p = MAMA::ConvertFPoint2Point(object1);
	SDL_Rect r = MAMA::ConvertFRect2Rect(object2);
	return SDL_PointInRect(&p, &r);
}