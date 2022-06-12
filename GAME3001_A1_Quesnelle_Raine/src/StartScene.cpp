#include "StartScene.h"
#include <algorithm>
#include "Game.h"
#include "glm/gtx/string_cast.hpp"
#include "EventManager.h"

StartScene::StartScene()
{
	StartScene::Start();
}

StartScene::~StartScene()
= default;

void StartScene::Draw()
{
	DrawDisplayList();
}

void StartScene::Update()
{
	UpdateDisplayList();
}

void StartScene::Clean()
{
	RemoveAllChildren();
}

void StartScene::HandleEvents()
{
	EventManager::Instance().Update();

	// Keyboard Events
	if(EventManager::Instance().IsKeyDown(SDL_SCANCODE_ESCAPE))
	{
		Game::Instance().Quit();
	}

	if(EventManager::Instance().IsKeyDown(SDL_SCANCODE_1))
	{
		Game::Instance().ChangeSceneState(SceneState::PLAY);
	}
}

void StartScene::Start()
{
	const SDL_Color black = { 0, 0, 0, 255 };
	m_pStartLabel = new Label("Game3001 Assignment 1", "Consolas", 35, black, glm::vec2(400.0f, 40.0f));
	m_pStartLabel->SetParent(this);
	AddChild(m_pStartLabel);

	m_pInstructionsLabel = new Label("By Kiean Raine: 101248364 and", "Consolas", 30, black, glm::vec2(400.0f, 120.0f));
	m_pInstructionsLabel->SetParent(this);
	AddChild(m_pInstructionsLabel);

	m_pInstructionsLabel = new Label(" Cayla Quesnelle: 101283672", "Consolas", 30, black, glm::vec2(400.0f, 160.0f));
	m_pInstructionsLabel->SetParent(this);
	AddChild(m_pInstructionsLabel);

	m_pShip = new Ship();
	m_pShip->GetTransform()->position = glm::vec2(400.0f, 300.0f); 
	AddChild(m_pShip); 

	// Start Button
	m_pStartButton = new Button();
	m_pStartButton->GetTransform()->position = glm::vec2(400.0f, 400.0f); 

	m_pStartButton->AddEventListener(Event::CLICK, [&]()-> void
	{
		m_pStartButton->SetActive(false);
		Game::Instance().ChangeSceneState(SceneState::PLAY);
	});
	
	m_pStartButton->AddEventListener(Event::MOUSE_OVER, [&]()->void
	{
		m_pStartButton->SetAlpha(128);
	});

	m_pStartButton->AddEventListener(Event::MOUSE_OUT, [&]()->void
	{
		m_pStartButton->SetAlpha(255);
	});
	AddChild(m_pStartButton);

	ImGuiWindowFrame::Instance().SetDefaultGuiFunction();
}

