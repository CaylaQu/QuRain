#include "PathManager.h"
#include "Util.h"

void PathManager::GetShortestPath(PathNode* start, PathNode* goal) // Updated for Lab 5.
{
	// Clear the path.
	ClearPath();
	// Initialize the current node record used in the algorithm.
	NodeRecord* currentRecord = nullptr;
	// Initialize the record for the start node.
	s_open.push_back(new NodeRecord(start));
	start->GetTile()->SetTileStatus(TileStatus::OPEN);
	// Iterate through processing each node.
	while (!s_open.empty())
	{
		// Find the smallest element in the open list.
		currentRecord = GetSmallestNode();
		// If it is the goal node, then terminate.
		if (currentRecord->m_node == goal) // We found the goal!
		{
			s_open.erase(std::remove(s_open.begin(), s_open.end(), currentRecord), s_open.end());
			s_closed.push_back(currentRecord);
			currentRecord->m_node->GetTile()->SetTileStatus(TileStatus::CLOSED);
			break;
		}
		// Otherwise get its outgoing connections.
		std::vector<PathConnection*> connections = currentRecord->m_node->GetConnections();
		// Loop through each connection in turn.
		for (const auto& connection : connections)
		{
			// Get the cost estimate for the end node.
			PathNode* endNode = connection->GetToNode();
			NodeRecord* endNodeRecord;
			const int endNodeCost = currentRecord->m_costSoFar + connection->GetCost();
			// Skip if the node is closed.
			if (ContainsNode(s_closed, endNode)) continue;
			// Or if it is open and we’ve found a worse route.
			else if (ContainsNode(s_open, endNode))
			{
				endNodeRecord = GetNodeRecord(s_open, endNode);
				if (endNodeRecord->m_costSoFar <= endNodeCost)
					continue;
			}
			//Otherwise we know we’ve got an unvisited node, so make a record for it.
			else
			{
				endNodeRecord = new NodeRecord();
				endNodeRecord->m_node = endNode;
			}
			// We need to update the node, so update the cost and connection.
			endNodeRecord->m_costSoFar = endNodeCost;
			endNodeRecord->m_connection = connection;
			endNodeRecord->m_fromRecord = currentRecord; // Our way back.
			// And node to the open list.
			if (!ContainsNode(s_open, endNode))
			{
				s_open.push_back(endNodeRecord);
				endNodeRecord->m_node->GetTile()->SetTileStatus(TileStatus::OPEN);
			}
		}
		// We’ve finished looking at the connections for the current node, so update the lists. 
		s_open.erase(std::remove(s_open.begin(), s_open.end(), currentRecord), s_open.end());
		s_closed.push_back(currentRecord);
		currentRecord->m_node->GetTile()->SetTileStatus(TileStatus::CLOSED);
	}
	// We’re here if we’ve either found the goal, or if we’ve no more nodes to search, then not.
	if (currentRecord->m_node != goal)
	{
		std::cout << "Could not find path!" << std::endl;
	}
	else
	{
		std::cout << "Found goal!" << std::endl;
		// Compile the list of connections for the path.
		while(currentRecord->m_node != start)
		{
			s_path.push_back(currentRecord->m_connection);
			currentRecord = currentRecord->m_fromRecord;
		}
		// Reverse the path.
		std::reverse(s_path.begin(), s_path.end());
	}
	// Clean up the NodeRecord lists.
	ClearLists();
}

NodeRecord* PathManager::GetSmallestNode()
{
	auto smallest = s_open.begin();
	auto current = s_open.begin();

	while (++current != s_open.end())
	{
		if ((*current)->m_costSoFar < (*smallest)->m_costSoFar)
			smallest = current;
		else if ((*current)->m_costSoFar == (*smallest)->m_costSoFar) // If equal, flip a coin!
			smallest = (rand() % 2 ? current : smallest);
	}
	return (*smallest);
}

std::vector<NodeRecord*>& PathManager::GetOpenList()
{
	return s_open;
}

std::vector<NodeRecord*>& PathManager::GetClosedList()
{
	return s_closed;
}

bool PathManager::ContainsNode(const std::vector<NodeRecord*>& list, const PathNode* n)
{
	for (auto i : list)
		if (i->m_node == n)
			return true;
	return false;
}

NodeRecord* PathManager::GetNodeRecord(const std::vector<NodeRecord*>& list, const PathNode* n)
{
	for (const auto i : list)
		if (i->m_node == n)
			return i;
	return nullptr;
}

void PathManager::DrawPath()
{
	if (s_path.empty()) return;
	// Draw path.
	const auto offset = glm::vec2(s_path[0]->GetFromNode()->GetTile()->GetWidth() /2,
	                              s_path[0]->GetFromNode()->GetTile()->GetHeight() / 2);
	for (const auto& connection : s_path)
	{
		Util::DrawLine(connection->GetFromNode()->GetTile()->GetTransform()->position + offset,
			connection->GetToNode()->GetTile()->GetTransform()->position + offset,
			glm::vec4(1,1,0,1));
	}
}

void PathManager::ClearPath()
{
	s_path.clear();
	s_path.shrink_to_fit();
	ClearLists();
}

void PathManager::ClearLists()
{
	// Clean up open list.
	for (auto nr : s_open)
	{
		delete nr;
		nr = nullptr;
	}
	s_open.clear();
	s_open.shrink_to_fit();
	// Clean up closed list.
	for (auto nr : s_closed)
	{
		delete nr;
		nr = nullptr;
	}
	s_closed.clear();
	s_closed.shrink_to_fit();
}

std::vector<NodeRecord*> PathManager::s_open;
std::vector<NodeRecord*> PathManager::s_closed;
std::vector<PathConnection*> PathManager::s_path;