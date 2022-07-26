#pragma once
#ifndef __PATH_MANAGER__
#define __PATH_MANAGER__

#include <vector>
#include "NodeRecord.h"

class PathNode;

class PathManager
{
public:
	static void GetShortestPath(PathNode* start, PathNode* goal);
	static NodeRecord* GetSmallestNode();
	static std::vector<NodeRecord*>& GetOpenList();
	static std::vector<NodeRecord*>& GetClosedList();
	static bool ContainsNode(const std::vector<NodeRecord*>& list, const PathNode* n);
	static NodeRecord* GetNodeRecord(const std::vector<NodeRecord*>& list, const PathNode* n);
	// New for Lab 5.
	static void DrawPath();
	static void ClearPath();
	static void ClearLists();
private:
	PathManager() = default;
	~PathManager() = default;
private:
	static std::vector<NodeRecord*> s_open;
	static std::vector<NodeRecord*> s_closed;
	static std::vector<PathConnection*> s_path;
};

#endif /* defined (__PATH_MANAGER__) */