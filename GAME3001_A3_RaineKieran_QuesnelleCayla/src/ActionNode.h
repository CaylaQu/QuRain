#pragma once
#ifndef __ACTION_NODE__
#define __ACTION_NODE__
#include "TreeNode.h"
#include "Agent.h"

// Abstract Class
class ActionNode : public TreeNode
{
public:
	ActionNode(Agent* agent = nullptr): TreeNode(agent) { m_isLeaf = true; }
	virtual ~ActionNode() = default;
	virtual void Action() = 0; // abstract method (function) -> Specialization
};

#endif /* defined (__ACTION_NODE__) */