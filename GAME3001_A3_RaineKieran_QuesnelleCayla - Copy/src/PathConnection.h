#pragma once
#ifndef __PATH_CONNECTION__
#define __PATH_CONNECTION__

class PathNode; // Example of forward declaration instead of an #include.

class PathConnection
{
public:
	PathConnection(PathNode* from, PathNode* to, int cost = 1);
	~PathConnection();
	[[nodiscard]] int GetCost() const;
	void SetCost(int cost);
	[[nodiscard]] PathNode* GetFromNode() const;
	[[nodiscard]] PathNode* GetToNode() const;
private:
	int m_cost;
	PathNode* m_pFromNode, * m_pToNode;
};

#endif /* defined (__PATH_CONNECTION__) */