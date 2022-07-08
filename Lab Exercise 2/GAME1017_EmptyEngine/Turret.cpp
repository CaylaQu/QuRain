#include "Turret.h"
#include "States.h"
#include "Enemy.h"
#include "Engine.h"
#include "TextureManager.h"
#include "EventManager.h"
#include "MathManager.h"

int Turret::s_coolDown = 120;

Turret::Turret(SDL_Rect dst) :m_dst(dst), m_src({ 0,0,100,100 }), m_angle(0.0), m_hasTarget(false), m_fireCtr(0)
{
	m_startPos = { dst.x, dst.y };
}

void Turret::Update()
{
	if (m_fireCtr > 0) m_fireCtr--;
	// Click and drag functionality.
	if (EVMA::MouseHeld(1) && SDL_PointInRect(&EVMA::GetMousePos(), &m_dst))
	{
		m_dst.x = EVMA::GetMousePos().x - m_dst.w / 2;
		m_dst.y = EVMA::GetMousePos().y - m_dst.h / 2;
	}
	m_angle = 0;
	m_hasTarget = false;

	if (GameState::Enemies().size() == 0) return;

	// Store center points of closest enemy and turret. For distance check.
	SDL_Point cPos = GameState::Enemies()[0]->GetPos(); // Closest enemy position.
	SDL_Point tPos = { GetPos().x, GetPos().y };

	// THIS IS WHAT FINDS THE CLOSEST ENEMY.
	for (unsigned i = 1; i < GameState::Enemies().size(); i++)
	{
		SDL_Point ePos = GameState::Enemies()[i]->GetPos(); // Gets the next enemy.
		// If current enemy distance is less than stored closest enemy.
		if (MAMA::Distance(tPos.x, ePos.x, tPos.y, ePos.y) < // current enemy distance
			MAMA::Distance(tPos.x, cPos.x, tPos.y, cPos.y)) // // closest enemy distance

		{
			cPos = ePos; // Updates the closest enemy as current enemy.
		}
	}
	// Is the closest enemy <= 300
	if (MAMA::Distance(tPos.x, cPos.x, tPos.y, cPos.y) <= 300.0)
	{
		SDL_FPoint deltaVector = { cPos.x - tPos.x , cPos.y - tPos.y + 30 }; // Class, what is the +30 for?
		m_angle = MAMA::Rad2Deg(MAMA::AngleBetweenPoints(deltaVector.y, deltaVector.x)) + 90;
		m_hasTarget = true;
		if (m_fireCtr == 0)
		{
			m_fireCtr = s_coolDown;

			// Method 1. Normalize the deltaVector.
			SDL_FPoint normalVec = MAMA::Normalize(deltaVector);
			double dx = normalVec.x * 6.0; // 6 is a bullet speed.
			double dy = normalVec.y * 6.0;

			// Method 2. Use the angle we got and Sohcahtoa it.
			// double dx = MAMA::SetDeltaX(MAMA::Deg2Rad(m_angle-90), 6.0);
			// double dy = MAMA::SetDeltaY(MAMA::Deg2Rad(m_angle-90), 6.0);

			// Method 3. Just use SetDeltas.
			// double dx, dy;
			//MAMA::SetDeltas(m_angle - 90, dx, dy, 6.0, 6.0);

			GameState::Bullets().push_back(new Bullet({ (float)(tPos.x - 2), (float)(tPos.y + 2), (float)4, (float)4 }, dx, dy));
		}
	}
}

void Turret::Render()
{
	SDL_RenderCopyEx(Engine::Instance().GetRenderer(), TEMA::GetTexture("turret"), &m_src, &m_dst, m_angle, NULL, SDL_FLIP_NONE); // Change to Ex.
}