#pragma once
#ifndef __PLAY_SCENE__
#define __PLAY_SCENE__

#include "Obstacle.h"
#include "Scene.h"
#include "PathNode.h"
#include "Starship.h"
#include "Target.h"
#include "LOSMode.h" 
#include "TiledLevel.h"



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
	bool m_isGridEnabled;

	// Input Control
	int m_pCurrentInputType{};
	void GetPlayerInput();
	void GetKeyboardInput();

	// Game Objects
	Target* m_pTarget;
	Starship* m_pStarship;
	std::vector<Obstacle*> m_pObstacles;
	TiledLevel* m_pLevel;


	void BuildObstaclePool();

	// Create our Division Scheme (Grid of PathNodes)
	std::vector<PathNode*> m_pGrid;
	void m_buildGrid();
	void m_toggleGrid(bool state);

	bool m_checkAgentLOS(Agent* agnet, DisplayObject* target_objects);
	bool m_checkPathNodesLOS(PathNode* path_node, DisplayObject* target_object);
	void m_checkaAllNOdesWithTarget(DisplayObject* target_object);
	void m_checkAllNNodesWithBoth();
	void m_setPathNodeLOSDistance(int dist);
	LOSMode m_LOSMode; // 0 = nodes visible to the target, 1 = nodes visible to the player, 2 = nodes visible to both


	void m_clearNodes();
	int m_pathNodeLOSDistance;
};

#endif /* defined (__PLAY_SCENE__) */