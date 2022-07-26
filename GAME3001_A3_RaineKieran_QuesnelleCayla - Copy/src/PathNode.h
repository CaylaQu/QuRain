#pragma once
#ifndef __PATH_NODE__
#define __PATH_NODE__

#include <vector>
#include "PathConnection.h"
#include "Tile.h"

class PathNode
{
public:
	PathNode(Tile* tile);
	~PathNode();
	void Update();
	[[nodiscard]] Tile* GetTile() const;
	void AddConnection(PathConnection* c);
	std::vector<PathConnection*>& GetConnections();

private:
	Tile* m_tile; // Tile that this node belongs to.
	std::vector<PathConnection*> m_connections;
};

#endif /* defined (__PATH_NODE__) */