#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"
#include "InputType.h"
#include "PathManager.h"

// required for IMGUI
#include "imgui.h"
#include "imgui_sdl.h"

//required for the scene to run
#include "Renderer.h"
#include "Util.h"
#include "PathNode.h"
#include "Config.h"
#include <fstream>


PlayScene::PlayScene()
{
	PlayScene::Start();
}

PlayScene::~PlayScene()
= default;

void PlayScene::Draw()
{

	DrawDisplayList();
	if (m_isGridEnabled)
	{
		for (auto element : m_pObstacles)
		{
			auto offset = glm::vec2(element->GetWidth() * 0.5, element->GetHeight() * 0.5);
			Util::DrawRect(element->GetTransform()->position - offset, element->GetWidth(), element->GetHeight());
		}
		auto detected = m_pRangedEnemy->GetTree()->GetPlayerDetectedNode()->GetDetected();
		Util::DrawCircle(m_pRangedEnemy->GetTransform()->position, 120.0f, detected ? glm::vec4(0, 1, 0, 1) : glm::vec4(1, 0, 0, 1));
	}

	SDL_SetRenderDrawColor(Renderer::Instance().GetRenderer(), 255, 255, 255, 255);
}

void PlayScene::Update()
{
	UpdateDisplayList();

	m_pRangedEnemy->GetTree()->GetEnemyHealthNode()->SetHealth(m_pRangedEnemy->GetHealth() > 25);
	m_pRangedEnemy->GetTree()->GetEnemyHitNode()->SetIsHit(false);
	m_pRangedEnemy->CheckAgentLOSToTarget(m_pRangedEnemy, m_pStarship, m_pObstacles);

	// Distance Check between Starship and Target for Detection Radius
	float distance = Util::Distance(m_pRangedEnemy->GetTransform()->position, m_pStarship->GetTransform()->position);

	// Radius detection...just outside of LOS range (around 300 px)
	m_pRangedEnemy->GetTree()->GetPlayerDetectedNode()->SetDetected(distance < 400);

	// Within LOS distance...but not too close (optimum firing range)
	m_pRangedEnemy->GetTree()->GetRangedCombatNode()->SetIsWithinCombatRange(distance >= 120 && distance <= 180);


	m_checkAgentLOS(m_pRangedEnemy, m_pRangedEnemy);
	switch (m_LOSMode)
	{
	case LOSMode::SHIP:
		m_checkaAllNOdesWithTarget(m_pRangedEnemy);
		break;
	case LOSMode::BASEENEMY:
		m_checkaAllNOdesWithTarget(m_pRangedEnemy);
		break;
	case LOSMode::BOTH:
		m_checkAllNNodesWithBoth();
		break;
	}
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
		// handle player movement with mouse and keyboard
		if (EventManager::Instance().IsKeyDown(SDL_SCANCODE_A))
		{
			m_pStarship->GetTransform()->position.x -= 9.0f;
		}
		else if (EventManager::Instance().IsKeyDown(SDL_SCANCODE_D))
		{
			m_pStarship->GetTransform()->position.x += 9.0f;
		}
		if (EventManager::Instance().IsKeyDown(SDL_SCANCODE_W))
		{
			m_pStarship->GetTransform()->position.y -= 9.0f;
		}
		if (EventManager::Instance().IsKeyDown(SDL_SCANCODE_S))
		{
			m_pStarship->GetTransform()->position.y += 9.0f;
		}
		if (EventManager::Instance().IsKeyDown(SDL_SCANCODE_H))
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
		else if (EventManager::Instance().IsKeyDown(SDL_SCANCODE_W))
		{

		}
		else if (EventManager::Instance().IsKeyDown(SDL_SCANCODE_S))
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

void PlayScene::BuildObstaclePool()
{
	std::ifstream inFile("../Assets/data/obstacles.txt");
	while (!inFile.eof())
	{
		std::cout << "Obstacle" << std::endl;
		auto obstacle = new Obstacle();
		float x, y, w, h;
		inFile >> x >> y >> w >> h;
		obstacle->GetTransform()->position = glm::vec2(x, y);
		obstacle->SetWidth(w);
		obstacle->SetHeight(h);
		AddChild(obstacle, 0);
		m_pObstacles.push_back(obstacle);
	}
	inFile.close();
}

void PlayScene::m_buildGrid()
{
	const auto tile_size = Config::TILE_SIZE;
	auto offset = glm::vec2(Config::TILE_SIZE * 0.5f, Config::TILE_SIZE * 0.5f);

	//m_ClearNodes(); // we will need to clear nodes every time we move an obstacle

	// lay out a grid of path_nodes
	for (int row = 0; row < Config::ROW_NUM; ++row)
	{
		for (int col = 0; col < Config::COL_NUM; ++col)
		{
			PathNode* path_node = new PathNode();
			path_node->GetTransform()->position = glm::vec2(static_cast<float>(col) * tile_size + offset.x, static_cast<float>(row) * tile_size + offset.y);

			bool keep_node = true;
			for (auto obstacle : m_pObstacles)
			{
				if (CollisionManager::AABBCheck(path_node, obstacle))
				{
					keep_node = false;
				}

			}

			if (keep_node)
			{
				AddChild(path_node);
				m_pGrid.push_back(path_node);
			}
			else
			{
				delete path_node;
			}
		}

	}


	m_toggleGrid(m_isGridEnabled);
}

void PlayScene::m_toggleGrid(bool state)
{
	for (auto path_node : m_pGrid)
	{
		path_node->SetVisible(state);
	}
}


bool PlayScene::m_checkAgentLOS(Agent* agent, DisplayObject* target_objects)
{
	bool has_LOS = false; // default - no LOS
	agent->SetHasLOS(has_LOS);

	// if ship to target distance is less than or equal to the LOS Distance (Range)
	const auto agent_to_range = Util::GetClosestEdge(agent->GetTransform()->position, target_objects);
	if (agent_to_range <= agent->GetLOSDistance())
	{
		// we are in range
		std::vector<DisplayObject*> contact_list;
		for (auto display_object : GetDisplayList())
		{
			if (display_object->GetType() == GameObjectType::NONE) { continue; }

			const auto agent_to_object_distance = Util::GetClosestEdge(agent->GetTransform()->position, display_object);
			if (agent_to_object_distance > agent_to_range) { continue; } // target is out of range
			if ((display_object->GetType() != GameObjectType::AGENT) && (display_object->GetType() != GameObjectType::PATH_NODE) && (display_object->GetType() != GameObjectType::TARGET))
			{
				contact_list.push_back(display_object);
			}
		}

		const glm::vec2 agent_LOS_end_point = agent->GetTransform()->position + agent->GetCurrentDirection() * agent->GetLOSDistance();
		has_LOS = CollisionManager::LOSCheck(agent, agent_LOS_end_point, contact_list, target_objects);

	}
	agent->SetHasLOS(has_LOS);

	return has_LOS;
}

bool PlayScene::m_checkPathNodesLOS(PathNode* path_node, DisplayObject* target_object)
{
	// check angle to the target so we can ise LOS distance for path_nodes
	const auto target_direction = target_object->GetTransform()->position - path_node->GetTransform()->position;
	const auto normalized_direction = Util::Normalize(target_direction); // changes
	path_node->SetCurrentDirection(normalized_direction);
	return m_checkAgentLOS(path_node, target_object);
}

void PlayScene::m_checkaAllNOdesWithTarget(DisplayObject* target_object)
{
	for (const auto path_node : m_pGrid)
	{
		m_checkPathNodesLOS(path_node, target_object);
	}
}

void PlayScene::m_checkAllNNodesWithBoth()
{
	for (auto path_node : m_pGrid)
	{
		bool LOSWidthBaseEnemy = m_checkPathNodesLOS(path_node, m_pRangedEnemy);
		bool LOSWidthTarget = m_checkPathNodesLOS(path_node, m_pStarship);
		path_node->SetHasLOS(LOSWidthBaseEnemy && LOSWidthTarget, glm::vec4(0, 1, 1, 1));
	}
}

void PlayScene::m_setPathNodeLOSDistance(const int dist)
{
	for (const auto path_node : m_pGrid)
	{
		path_node->SetLOSDistance(static_cast<float>(dist));
	}
}


void PlayScene::m_clearNodes()
{
	m_pGrid.clear();
	for (auto display_object : GetDisplayList())
	{
		if (display_object->GetType() == GameObjectType::PATH_NODE)
		{
			RemoveChild(display_object);
		}
	}
}



void PlayScene::Start()
{
	// Set GUI Title
	m_guiTitle = "Assignment 4";

	// setup a few more fields
	m_LOSMode = LOSMode::SHIP; // future emu
	m_pathNodeLOSDistance = 1000; // 1000x distance
	m_setPathNodeLOSDistance(m_pathNodeLOSDistance);

	m_pLevel = new TiledLevel("../Assets/data/level.txt", "../Assets/data/leveldata.txt",
		"../Assets/textures/tilefloor.png", "tiles", { 32,32 }, { 40.0f,40.0f },
		15, 20, true, true);
	AddChild(m_pLevel);

	// Set Input Type
	m_pCurrentInputType = static_cast<int>(InputType::KEYBOARD_MOUSE);

	// Add Game Objects
	m_pTarget = new Target();
	m_pTarget->GetTransform()->position = glm::vec2(550.0f, 300.0f);
	AddChild(m_pTarget, 2);

	m_pStarship = new Starship();
	m_pStarship->GetTransform()->position = glm::vec2(150.0f, 300.0f);
	AddChild(m_pStarship, 2);

	//Add Obstacles
	BuildObstaclePool();

	m_pRangedEnemy = new RangedCombatEnemy(this);
	m_pRangedEnemy->GetTransform()->position = glm::vec2(400.0f, 40.0f);
	AddChild(m_pRangedEnemy, 2);




	// setup the grid
	m_isGridEnabled = false;
	m_buildGrid();
	m_toggleGrid(m_isGridEnabled);

	// preload sounds
	SoundManager::Instance().Load("../Assets/audio/yay.ogg", "yay", SoundType::SOUND_SFX);
	SoundManager::Instance().Load("../Assets/audio/thunder.ogg", "thunder", SoundType::SOUND_SFX);
	SoundManager::Instance().Load("../Assets/audio/Pixelland.mp3", "BackgroundMusic", SoundType::SOUND_MUSIC);
	/* DO NOT REMOVE */
	ImGuiWindowFrame::Instance().SetGuiFunction([this] { GUI_Function(); });
	SoundManager::Instance().PlayMusic("BackgroundMusic", -1, 0);
	SoundManager::Instance().SetMusicVolume(3);


}

Target* PlayScene::GetTarget() const
{
	return m_pTarget;
}

RangedCombatEnemy* PlayScene::GetRangedEnemy() const
{
	return m_pRangedEnemy;
}

void PlayScene::SpawnEnemyBullet()
{
	glm::vec2 Spawn_point = m_pRangedEnemy->GetTransform()->position + m_pRangedEnemy->GetCurrentDirection() * 30.0f;
	glm::vec2 enemy_bullet_direction = Util::Normalize(m_pStarship->GetTransform()->position - Spawn_point);

	m_pEnemyBullet.push_back(new EnemyBullet(5.0f, enemy_bullet_direction));
	m_pEnemyBullet.back()->GetTransform()->position = Spawn_point;
	AddChild(m_pEnemyBullet.back(), 2);
}

Starship* PlayScene::GetStarShip()
{
	return m_pStarship;
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


	if (ImGui::Checkbox("Toggle Grid", &m_isGridEnabled))
	{
		m_toggleGrid(m_isGridEnabled);
	}

	ImGui::Separator();

	//ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
	//ImGui::Begin(m_guiTitle.c_str(), nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoMove);

	static int LOS_mode = static_cast<int>(m_LOSMode);
	ImGui::Text("Path Node LOS");
	ImGui::RadioButton("Target", &LOS_mode, static_cast<int>(LOSMode::BASEENEMY)); ImGui::SameLine();
	ImGui::RadioButton("StarShip", &LOS_mode, static_cast<int>(LOSMode::SHIP)); ImGui::SameLine();
	ImGui::RadioButton("Both Target & StarShip", &LOS_mode, static_cast<int>(LOSMode::BOTH));

	m_LOSMode = static_cast<LOSMode>(LOS_mode);


	ImGui::Separator();

	// spaceship properties

	static int shipPosition[] = { static_cast<int>(m_pRangedEnemy->GetTransform()->position.x), static_cast<int>(m_pRangedEnemy->GetTransform()->position.y) };
	if (ImGui::SliderInt2("Enemy Position", shipPosition, 0, 800))
	{
		m_pRangedEnemy->GetTransform()->position.x = static_cast<float>(shipPosition[0]);
		m_pRangedEnemy->GetTransform()->position.y = static_cast<float>(shipPosition[1]);
	}

	// allow the ship to rotate
	static int angle;
	if (ImGui::SliderInt("Enemy Direction", &angle, -360, 360))
	{
		m_pRangedEnemy->SetCurrentHeading(static_cast<float>(angle));
	}

	// Target properties

	static int targetPosition[] = { static_cast<int>(m_pTarget->GetTransform()->position.x), static_cast<int>(m_pTarget->GetTransform()->position.y) };
	if (ImGui::SliderInt2("Target Position", targetPosition, 0, 800))
	{
		m_pTarget->GetTransform()->position.x = static_cast<float>(targetPosition[0]);
		m_pTarget->GetTransform()->position.y = static_cast<float>(targetPosition[1]);
	}

	ImGui::Separator();

	// Add Obstacle Position Control for all obstacles
	for (unsigned i = 0; i < m_pObstacles.size(); ++i)
	{
		int obstaclePosition[] = { static_cast<int>(m_pObstacles[i]->GetTransform()->position.x), static_cast<int>(m_pObstacles[i]->GetTransform()->position.y) };
		std::string label = "Obstacle" + std::to_string(i + 1) + " Position";
		if (ImGui::SliderInt2(label.c_str(), obstaclePosition, 0, 800))
		{
			m_pObstacles[i]->GetTransform()->position.x = static_cast<float>(obstaclePosition[0]);
			m_pObstacles[i]->GetTransform()->position.y = static_cast<float>(obstaclePosition[1]);
			m_buildGrid();
		}
	}

	ImGui::Separator();


	ImGui::End();
}