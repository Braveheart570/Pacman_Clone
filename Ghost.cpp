#include "Ghost.h"

Ghost::Ghost(std::vector<PathNode*> map, Vector2 pos) {

	mMap = map;
	target = Vector2(0,0);
	
	mGhostTex = new AnimatedTexture("PacmanAtlas.png",457,65,14,14,2,0.5f,AnimatedTexture::Horizontal);
	mGhostTex->Parent(this);
	mGhostTex->Scale(Vect2_One*3);

	Position(pos);

}

void Ghost::Render() {

	PhysEntity::Render();

	mGhostTex->Render();

}

Ghost::~Ghost() {

	delete mGhostTex;
	mGhostTex = nullptr;


}

void Ghost::Update() {


	if (Position() == targetNode->Position()) { //must be a better way

	}


	//if reached target node
		// set target node to current node
		//select new target node

	//lerp to target node.

}