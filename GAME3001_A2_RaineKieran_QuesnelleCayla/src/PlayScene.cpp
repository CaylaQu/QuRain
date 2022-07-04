#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"
#include "InputType.h"
#include "PathManager.h"
#include "Renderer.h"
#include "Util.h"
#include "PathNode.h"


// required for IMGUI
#include "imgui.h"
#include "imgui_sdl.h"


PlayScene::PlayScene()
{
	PlayScene::Start();
}

PlayScene::~PlayScene()
= default;

void PlayScene::Draw()
{
	DrawDisplayList();
	SDL_SetRenderDrawColor(Renderer::Instance().GetRenderer(), 255, 255, 255, 255);
}

void PlayScene::Update()
{
	UpdateDisplayList();
}

void PlayScene::Clean()
{
	RemoveAllChildren();
}


void PlayScene::HandleEvents()
{
	EventManager::Instance().Update();

	GetPlayerInput();

	GetKeyboardInput();
}

void PlayScene::GetPlayerInput()
{
	switch (m_pCurrentInputType)
	{
	case static_cast<int>(InputType::GAME_CONTROLLER):
	{
		// handle player movement with GameController
		if (SDL_NumJoysticks() > 0)
		{
			if (EventManager::Instance().GetGameController(0) != nullptr)
			{
				constexpr auto dead_zone = 10000;
				if (EventManager::Instance().GetGameController(0)->STICK_LEFT_HORIZONTAL > dead_zone)
				{
					
				}
				else if (EventManager::Instance().GetGameController(0)->STICK_LEFT_HORIZONTAL < -dead_zone)
				{
					
				}
				else
				{
					
				}
			}
		}
	}
	break;
	case static_cast<int>(InputType::KEYBOARD_MOUSE):
	{
		static bool toggleGrid = false;
		// handle player movement with mouse and keyboard
		if (EventManager::Instance().IsKeyDown(SDL_SCANCODE_H))
		{
			m_pLevel->SetLabelsEnabled(toggleGrid);
		}
		else if (EventManager::Instance().IsKeyDown(SDL_SCANCODE_D))
		{
			
		}
		else
		{
			
		}
	}
	break;
	case static_cast<int>(InputType::ALL):
	{
		if (SDL_NumJoysticks() > 0)
		{
			if (EventManager::Instance().GetGameController(0) != nullptr)
			{
				constexpr auto dead_zone = 10000;
				if (EventManager::Instance().GetGameController(0)->STICK_LEFT_HORIZONTAL > dead_zone
					|| EventManager::Instance().IsKeyDown(SDL_SCANCODE_D))
				{
					
				}
				else if (EventManager::Instance().GetGameController(0)->STICK_LEFT_HORIZONTAL < -dead_zone
					|| EventManager::Instance().IsKeyDown(SDL_SCANCODE_A))
				{
					
				}
				else
				{
					
				}
			}
		}
		else if (EventManager::Instance().IsKeyDown(SDL_SCANCODE_A))
		{
			
		}
		else if (EventManager::Instance().IsKeyDown(SDL_SCANCODE_D))
		{
			
		}
		else
		{
			
		}
	}
	break;
	}
}

void PlayScene::GetKeyboardInput()
{
	if (EventManager::Instance().IsKeyDown(SDL_SCANCODE_ESCAPE))
	{
		Game::Instance().Quit();
	}

	if (EventManager::Instance().IsKeyDown(SDL_SCANCODE_1))
	{
		Game::Instance().ChangeSceneState(SceneState::START);
	}

	if (EventManager::Instance().IsKeyDown(SDL_SCANCODE_2))
	{
		Game::Instance().ChangeSceneState(SceneState::END);
	}
}

void PlayScene::ComputeTileCosts()
{
	float distance = 0.0f;
	float dx = 0.0f;
	float dy = 0.0f;

	for(auto tile : m_pLevel->GetLevel()) // get vector of all tiles to enter it through
	{
		if (tile->GetTileType() == TileType::IMPASSABLE) continue;
		switch(m_currentHeuristic)
		{
		case Heuristic::MANHATTAN:
			dx = abs(tile->GetGridPosition().x - m_pTarget->GetGridPosition().x);
			dy = abs(tile->GetGridPosition().y - m_pTarget->GetGridPosition().y);
			distance = dx + dy; 
			break;
		case Heuristic::EUCLIDEAN: // magnitude of dx and dy. c of pythagorian 
			distance = Util::Distance(tile->GetGridPosition(), m_pTarget->GetGridPosition());
			break;
		}
		tile->SetTileCost(distance);
	}
}

void PlayScene::Start()
{
	//set background music 
	SoundManager::Instance().Load("../Assets/audio/Mutara.mp3", "bgsong", SoundType::SOUND_MUSIC);

	//play background music
	SoundManager::Instance().PlayMusic("bgsong", -1, 0);
	SoundManager::Instance().SetMusicVolume(60);
	// Set GUI Title
	m_guiTitle = "Play Scene";

	// Set Input Type
	m_pCurrentInputType = static_cast<int>(InputType::KEYBOARD_MOUSE);

	// Create GameObjects
	m_pLevel = new TiledLevel("../Assets/data/level.txt", "../Assets/data/leveldata.txt",
		"../Assets/textures/Tiles.png", "tiles", { 32,32 }, { 40.0f,40.0f },
		15, 20, true, true);
	AddChild(m_pLevel);

	auto offset = glm::vec2(20, 20);

	//make lables for instructions 
	const SDL_Color Black = { 0, 0, 0, 255 };
	m_instructionLable = new Label("Press H for debug view", "8bitOperatorPlus8-Bold", 18, Black, glm::vec2(132.0f, 20.0f));
	m_instructionLable->SetParent(this);
	AddChild(m_instructionLable);

	m_instructionLable = new Label("Press F to find shortest path", "8bitOperatorPlus8-Bold", 18, Black, glm::vec2(170.0f, 45.0f));
	m_instructionLable->SetParent(this);
	AddChild(m_instructionLable);

	m_instructionLable = new Label("Press M to make agent march", "8bitOperatorPlus8-Bold", 18, Black, glm::vec2(164.0f, 70.0f));
	m_instructionLable->SetParent(this);
	AddChild(m_instructionLable);

	m_instructionLable = new Label("Right Click to set Goal", "8bitOperatorPlus8-Bold", 18, Black, glm::vec2(132.0f, 95.0f));
	m_instructionLable->SetParent(this);
	AddChild(m_instructionLable);

	m_instructionLable = new Label("Left Click to set Start", "8bitOperatorPlus8-Bold", 18, Black, glm::vec2(132.0f, 120.0f));
	m_instructionLable->SetParent(this);
	AddChild(m_instructionLable);

	m_pTarget = new Target();
	m_pTarget->GetTransform()->position = m_pLevel->GetTile(15, 11)->GetTransform()->position + offset;
	m_pTarget->SetGridPosition(15.0f, 11.0f);
	// TODO: set targets tile to goal
	AddChild(m_pTarget);

	m_pActor = new Starship(); // todo: replace Megaman with megaman
	m_pActor->GetTransform()->position = m_pLevel->GetTile(0, 7)->GetTransform()->position + offset;
	m_pActor->SetGridPosition(0.0f, 7.0f);
	// TODO: set targets tile to goal
	AddChild(m_pActor);

	/* DO NOT REMOVE */
	ImGuiWindowFrame::Instance().SetGuiFunction([this] { GUI_Function(); });
}

void PlayScene::GUI_Function() 
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();

	ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
	ImGui::Begin(m_guiTitle.c_str(), nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoMove);

	ImGui::Text("Player Input");
	ImGui::RadioButton("Keyboard / Mouse", &m_pCurrentInputType, static_cast<int>(InputType::KEYBOARD_MOUSE)); ImGui::SameLine();
	ImGui::RadioButton("Game Controller", &m_pCurrentInputType, static_cast<int>(InputType::GAME_CONTROLLER)); ImGui::SameLine();
	ImGui::RadioButton("Both", &m_pCurrentInputType, static_cast<int>(InputType::ALL));

	ImGui::Separator();

	static bool toggleGrid = false;
	if (ImGui::Checkbox(" Toggle Grid", &toggleGrid))
	{
		m_pLevel->SetLabelsEnabled(toggleGrid);
	}

	ImGui::Separator();

	auto offset = glm::vec2(20, 20);

	static int start_position[2] = { (int)m_pActor->GetGridPosition().x, (int)m_pActor->GetGridPosition().y };
	if (ImGui::SliderInt2("Start Position", start_position, 0, 19))
	{
		if (start_position[1] > 14) start_position[1] = 14;
		{
			m_pActor->GetTransform()->position =
				m_pLevel->GetTile(start_position[0], start_position[1])->GetTransform()->position + offset;
			m_pActor->SetGridPosition(start_position[0], start_position[1]);
		}
	}
	
	static int goal_position[2] = { (int)m_pTarget->GetGridPosition().x, (int)m_pTarget->GetGridPosition().y };
	if (ImGui::SliderInt2("Goal Position", goal_position, 0, 19))
	{
		if (goal_position[1] > 14) goal_position[1] = 14;
		{
			m_pTarget->GetTransform()->position =
				m_pLevel->GetTile(goal_position[0], goal_position[1])->GetTransform()->position + offset;
			m_pTarget->SetGridPosition(goal_position[0], goal_position[1]);
		}
	}
	ImGui::Separator();

	static int radio = static_cast<int>(m_currentHeuristic);
	ImGui::Text("Heuristic Type");
	ImGui::RadioButton("manhattan", &radio, static_cast<int>(Heuristic::MANHATTAN));
	ImGui::SameLine();
	ImGui::RadioButton("euclidean", &radio, static_cast<int>(Heuristic::EUCLIDEAN));
	if (m_currentHeuristic != static_cast<Heuristic>(radio))
	{
		m_currentHeuristic = static_cast<Heuristic>(radio);
	}

	if(ImGui::Button("Compute tile cost", {208, 20}))
	{
		ComputeTileCosts();
	}

	ImGui::Separator();

	if (ImGui::Button("Get Shortest Path", { 208, 20 }) && m_pLevel->HasNavigation())
	{
		PathNode* startNode = m_pLevel->GetTile(m_pActor->GetGridPosition())->GetNode();
		PathNode* goalNode = m_pLevel->GetTile(m_pTarget->GetGridPosition())->GetNode();
		if(startNode != nullptr && goalNode != nullptr)
		{
			PathManager::GetShortestPath(startNode, goalNode);
		}
		else
		{
			std::cout << "Cannot get the shortest path. One or more nodes are null!" << std::endl;
		}
	}

	ImGui::SameLine();

	if (ImGui::Button("Clear Path", { 104, 20 }) && m_pLevel->HasNavigation())
	{
		PathManager::ClearPath();
		for(const auto tile : m_pLevel->GetLevel())
		{
			if (tile->GetTileType() == TileType::IMPASSABLE)continue;
			tile->SetTileStatus(TileStatus::UNVISITED);
		}
	}


	ImGui::End();
}