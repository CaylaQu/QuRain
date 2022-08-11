#pragma once
#ifndef __TREE_NODE__
#define __TREE_NODE__
#include <string>

#include "Agent.h"

struct TreeNode
{
	TreeNode(Agent* agent = nullptr)
	{
		m_agent = agent;
	}

	virtual ~TreeNode() = default;

	std::string m_name;

	TreeNode* m_pLeft = nullptr;
	TreeNode* m_pRight = nullptr;
	TreeNode* m_pParent = nullptr;
	bool m_isLeaf = false;

	[[nodiscard]] Agent* GetAgent() const { return m_agent; }
	void SetAgent(Agent* agent) { m_agent = agent; }

protected:
	Agent* m_agent;
};

#endif /* defined (__TREE_NODE__) */
