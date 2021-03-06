#pragma once
#ifndef __PLAY_SCENE__
#define __PLAY_SCENE__

#include "Scene.h"
#include "Target.h"
#include "Starship.h"
#include "Label.h"
#include "Starship2.h"
#include "Starship3.h"
#include "Starship4.h"
#include "Obstacle.h"
#include "SoundManager.h"
 

class PlayScene : public Scene
{
public:
	PlayScene();
	~PlayScene() override;

	// Scene LifeCycle Functions
	virtual void Draw() override;
	virtual void Update() override;
	virtual void Clean() override;
	virtual void HandleEvents() override;
	virtual void Start() override;
	bool ClearScreen = false;
private:
	// IMGUI Function
	void GUI_Function();
	std::string m_guiTitle;
	
	//Game Objects Lab 2
	Target* m_pTarget;
	Starship* m_pStarship;
	Starship2* m_pStarship2;
	Starship3* m_pStarship3;
	Starship4* m_pStarship4;
	Label* play_Label;
	Obstacle* m_pObstacle; 

	// Input Control
	int m_pCurrentInputType{};
	void GetPlayerInput();
	void GetKeyboardInput();

	void DoWiskerCollision();
};

#endif /* defined (__PLAY_SCENE__) */