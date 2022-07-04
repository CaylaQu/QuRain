#pragma once
#ifndef __PLAY_SCENE__
#define __PLAY_SCENE__

#include "Scene.h"
#include "TiledLevel.h"
#include "Starship.h"
#include "Target.h"
#include "Heuristic.h"
#include "Megaman.h"

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
private:
	// IMGUI Function
	void GUI_Function();
	std::string m_guiTitle;

	// Lab 4 GameObjects
	TiledLevel* m_pLevel;
	//Starship* m_pStarship;
	Megaman* m_pMegaman;
	Starship* m_pActor;
	Target* m_pTarget;
	Label* m_instructionLable{};


	// Input Control
	int m_pCurrentInputType{};
	void GetPlayerInput();
	void GetKeyboardInput();

	void ComputeTileCosts();
	Heuristic m_currentHeuristic; 
};

#endif /* defined (__PLAY_SCENE__) */