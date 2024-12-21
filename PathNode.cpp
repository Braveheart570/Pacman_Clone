#include "PathNode.h"


PathNode::PathNode(Vector2 pos, int index) : Texture("CircleCollider.png") {

	Scale(Vect2_One * 0.5f);
	Position(pos);
	mLabelTex = new Texture(std::to_string(index), "emulogic.ttf", 10, {0,255,0});
	mLabelTex->Parent(this);
	mLabelTex->Position(Vect2_Zero);

}

PathNode::~PathNode() {

	for (auto conection : mConnections) {
		
		conection = nullptr;
	}

	delete mLabelTex;
	mLabelTex = nullptr;

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

		dirVec = dirVec * (25.0f*0.5f);

		mGraphics->DrawLine(this->Position().x+ dirVec.x,this->Position().y+ dirVec.y,link->Position().x,link->Position().y);

		dirVec = -dirVec;
		mGraphics->DrawLine(this->Position().x + dirVec.x, this->Position().y + dirVec.y, link->Position().x, link->Position().y);
	}

	mLabelTex->Render();

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

PathNode* PathNode::GetConnectionbyDir(Vector2 dir) {//TODO this is a mess

	if (mConnections.size() < 1) {
		return nullptr;
	}
	dir = dir.Normalized();



	float dirAngle = atan2(dir.y, dir.x)*RAD_TO_DEG;
	if (dirAngle < 0) {
		dirAngle += 360;
	}

	Vector2 connectionDir = (mConnections[0]->Position() - Position()).Normalized();
	float connectionAngle = atan2(connectionDir.y, connectionDir.x)*RAD_TO_DEG;
	if (connectionAngle < 0) {
		connectionAngle += 360;
	}

	PathNode* retVal = mConnections[0];
	float lowestDif = abs(connectionAngle - dirAngle);

	for (int i = 1; i < mConnections.size(); i++) {

		
		connectionDir = (mConnections[i]->Position() - Position()).Normalized();
		connectionAngle = atan2(connectionDir.y, connectionDir.x)*RAD_TO_DEG;
		if (connectionAngle < 0) {
			connectionAngle += 360;
		}

		float dif = abs(connectionAngle - dirAngle);

		if (dif < lowestDif) {
			lowestDif = dif;
			retVal = mConnections[i];

			if (lowestDif == 0) {
				break;
			}
		}
	}

	connectionDir = (retVal->Position() - Position()).Normalized();

	if (connectionDir.x != 0 || dir.x != 0) {
		if (connectionDir.x * dir.x <= 0) {
			return nullptr;
		}
	}

	if (connectionDir.y != 0 || dir.y != 0) {
		if (connectionDir.y * dir.y <= 0) {
			return nullptr;
		}
	}
	
	return retVal;

}

int PathNode::ConnectionsSize() {
	return mConnections.size();
}

PathNode* PathNode::GetConnectionByIndex(int index) {

	return mConnections[index];

}