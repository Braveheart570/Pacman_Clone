#include "PathNode.h"


PathNode::PathNode(Vector2 pos) : Texture("CircleCollider.png") {

	Position(pos);
	mConnections[0] = nullptr;
	mConnections[1] = nullptr;
	mConnections[2] = nullptr;
	mConnections[3] = nullptr;

}

PathNode::~PathNode() {

	mConnections[0] = nullptr;
	mConnections[1] = nullptr;
	mConnections[2] = nullptr;
	mConnections[3] = nullptr;

}