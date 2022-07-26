#include "PathNode.h"
#include "Util.h"

PathNode::PathNode()
{
	SetWidth(10);
	SetHeight(10);
	GetTransform()->position = glm::vec2(0, 0);
	GetRigidBody()->isColliding = false;
	SetType(GameObjectType::PATH_NODE);
	SetCurrentHeading(0.0f);
	SetCurrentDirection(glm::vec2(1.0f, 0.0f));
	SetLOSDistance(1000.0f);
	SetLOSColour(glm::vec4(0, 0.5, 1, 1));
}

PathNode::~PathNode()
= default;

void PathNode::Draw()
{
	Util::DrawRect(GetTransform()->position - glm::vec2(5, 0), 10, 10, GetLOSColour());
}

void PathNode::Update()
{
}

void PathNode::Clean()
{
}
