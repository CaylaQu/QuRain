#pragma once
#ifndef __PATH_NODE__
#define __PATH_NODE__

#include "Agent.h"
#include "Tile.h"
#include "PathConnection.h"

class PathNode : public Agent
{
public:
	PathNode();
	explicit PathNode(Tile* tile);
	~PathNode();

	// Inherited via GameObject
	void Draw() override;
	void Update() override;
	void Clean() override;
	std::vector<PathConnection*>& PathNode::GetConnections();
	void AddConnection(PathConnection* c);
	[[nodiscard]] Tile* GetTile() const;


private:
	Tile* m_tile; // Tile that this node belongs to.
	std::vector<PathConnection*> m_connections;
};

#endif /* defined (__PATH_NODE__) */