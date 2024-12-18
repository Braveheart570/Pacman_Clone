#include "Ghost.h"

Ghost::Ghost(PathNode* start) {

	mTimer = Timer::Instance();
	mNodeManager = NodeManager::Instance();
	
	CurrentNode = start;
	
	mGhostTex = new AnimatedTexture("PacmanAtlas.png",457,65,14,14,2,0.5f,AnimatedTexture::Horizontal);
	mGhostTex->Parent(this);
	mGhostTex->Scale(Vect2_One*3);

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

}

Ghost::~Ghost() {

	mNodeManager = nullptr;

	delete mGhostTex;
	mGhostTex = nullptr;


}

void Ghost::Update() {

	target = Player::Instance()->Position();

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
			
			targetNode = CurrentNode->ClosestConnection(target);
			
			


		}
		else {
			Position(pos);
		}
	}

}

void Ghost::Hit(PhysEntity* entity) {

}