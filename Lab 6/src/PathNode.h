#pragma once
#ifndef __PATH_NODE__
#define __PATH_NODE__

#include "Agent.h"
#include "Tile.h"

class PathNode : public Agent
{
public:
	PathNode();
	~PathNode();

	// Inherited via GameObject
	void Draw() override;
	void Update() override;
	void Clean() override;

private:

};

#endif /* defined (__PATH_NODE__) */