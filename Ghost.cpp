#include "Ghost.h"

Ghost::Ghost(PathNode* start) {

	mTimer = Timer::Instance();
	mNodeManager = NodeManager::Instance();
	
	CurrentNode = start;
	
	

	AddCollider(new CircleCollider(20,true));
	AddCollider(new CircleCollider(20));
	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Hostile);

	Position(start->Position());

	mSpeed = 100;

	target = Player::Instance()->Position();
	targetNode = CurrentNode->ClosestConnection(target);

}

void Ghost::Render() {

	mGhostTex->Render();
	PhysEntity::Render();
	Graphics::Instance()->DrawLine(Position().x,Position().y, target.x,target.y);

}

Ghost::~Ghost() {

	mNodeManager = nullptr;

	delete mGhostTex;
	mGhostTex = nullptr;


}

void Ghost::Update() {

	mGhostTex->Update();

	Vector2 dir = (targetNode->Position()-Position()).Normalized();

	Vector2 pos = Position() + dir * mSpeed * mTimer->DeltaTime();

	Vector2 dist = targetNode->Position() - pos;


	if (targetNode != nullptr) {

		

		if (Position() == targetNode->Position()) {
			std::cout << "at target" << std::endl;
		}
		else if (dist.MagnitudeSqr() < EPSILON * mSpeed / 25.0f) {
			Position(targetNode->Position());
			CurrentNode = targetNode;
			
			setNewTargetNode();
			
			


		}
		else {
			Position(pos);
		}
	}

}

void Ghost::Hit(PhysEntity* entity) {

}