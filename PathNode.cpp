#include "PathNode.h"


PathNode::PathNode(Vector2 pos) : Texture("CircleCollider.png") {

	Position(pos);

}

PathNode::~PathNode() {

	for (auto conection : mConnections) {
		
		delete conection;
		conection = nullptr;
	}

}

void PathNode::AddConnection(PathNode* node) {

	mConnections.push_back( node);

}

void PathNode::Render() {

	Texture::Render();

	for (auto link : mConnections) {
		mGraphics->DrawLine(this->Position().x,this->Position().y,link->Position().x,link->Position().y);
	}

}