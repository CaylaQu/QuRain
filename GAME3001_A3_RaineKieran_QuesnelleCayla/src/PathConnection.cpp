#include "PathConnection.h"
#include "PathNode.h"

PathConnection::PathConnection(PathNode* from, PathNode* to, const int cost)
	:m_cost(cost), m_pFromNode(from), m_pToNode(to)
{
	// Empty for now.
}

PathConnection::~PathConnection() = default;

int PathConnection::GetCost() const
{
	return m_cost;
}

void PathConnection::SetCost(int cost)
{
	m_cost = cost;
}

PathNode* PathConnection::GetFromNode() const
{
	return m_pFromNode;
}

PathNode* PathConnection::GetToNode() const
{
	return m_pToNode;
}
