#pragma once
#ifndef __NODE_RECORD__
#define __NODE_RECORD__

#include "PathNode.h"
#include "PathConnection.h"

struct NodeRecord // Everything public by default.
{ 
	NodeRecord(PathNode* n = nullptr) :m_node(n), m_connection(nullptr), m_fromRecord(nullptr), m_costSoFar(0) {}
	PathNode* m_node;
	PathConnection* m_connection;
	NodeRecord* m_fromRecord;
	int m_costSoFar;
};

#endif /* defined (__NODE_RECORD__) */