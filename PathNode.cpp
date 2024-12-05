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

		Vector2 dirVec = Position() - link->Position();
		dirVec = dirVec.Normalized();

		dirVec = RotateVector(dirVec, 90);

		dirVec = dirVec*25;

		mGraphics->DrawLine(this->Position().x+ dirVec.x,this->Position().y+ dirVec.y,link->Position().x,link->Position().y);

		dirVec = -dirVec;
		mGraphics->DrawLine(this->Position().x + dirVec.x, this->Position().y + dirVec.y, link->Position().x, link->Position().y);
	}

}


PathNode* PathNode::ClosestConnection(Vector2 target) {

	if (mConnections.size() < 1) {
		return nullptr;
	}

	PathNode* closestNode = mConnections[0];
	float shortestDist = (mConnections[0]->Position() - target).Magnitude();

	for (int i = 1; i < mConnections.size(); i++) {

		float dist = (mConnections[i]->Position() - target).Magnitude();
		if (dist < shortestDist) {
			closestNode = mConnections[i];
			shortestDist = dist;
		}

	}

	return closestNode;

}