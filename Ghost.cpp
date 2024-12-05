#include "Ghost.h"

Ghost::Ghost(PathNode* start) {

	mTimer = Timer::Instance();
	mNodeManager = NodeManager::Instance();
	
	CurrentNode = start;
	
	mGhostTex = new AnimatedTexture("PacmanAtlas.png",457,65,14,14,2,0.5f,AnimatedTexture::Horizontal);
	mGhostTex->Parent(this);
	mGhostTex->Scale(Vect2_One*3);

	Position(start->Position());

	mSpeed = 100;

	//TODO testing
	targetNode = mNodeManager->getNode(1);
	target = Vector2(0,Graphics::SCREEN_HEIGHT);

}

void Ghost::Render() {

	PhysEntity::Render();

	mGhostTex->Render();

}

Ghost::~Ghost() {

	mNodeManager = nullptr;

	delete mGhostTex;
	mGhostTex = nullptr;


}

void Ghost::Update() {

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

			//select new node
			targetNode = CurrentNode->ClosestConnection(target);


		}
		else {
			Position(pos);
		}
	}

}