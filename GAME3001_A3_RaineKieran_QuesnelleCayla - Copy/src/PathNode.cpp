#include "PathNode.h"

PathNode::PathNode(Tile* tile): m_tile(tile)
{
	// Empty for now.
}

PathNode::~PathNode()
{
	for (auto& m_connection : m_connections)
	{
		delete m_connection;
		m_connection = nullptr;
	}
	m_connections.clear();
	m_connections.shrink_to_fit();
}

void PathNode::Update()
{
	// Empty for now.
}

Tile* PathNode::GetTile() const
{
	return m_tile;
}

void PathNode::AddConnection(PathConnection* c)
{
	m_connections.push_back(c);
}

std::vector<PathConnection*>& PathNode::GetConnections()
{
	return m_connections;
}
