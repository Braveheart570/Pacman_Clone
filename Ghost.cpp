#include "Ghost.h"

Ghost::Ghost(Vector2 pos) {

	
	target = Vector2(0,0);
	
	mGhostTex = new AnimatedTexture("PacmanAtlas.png",457,65,14,14,2,0.5f,AnimatedTexture::Horizontal);
	mGhostTex->Parent(this);
	mGhostTex->Scale(Vect2_One*3);

	Position(pos);

	mSpeed = 100;

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

	float distance = (CurrentNode->Position() - targetNode->Position()).Magnitude();

	float lerpVar = mSpeed / distance; // idk what I'm doing here.

	if (lerpVar >= 1) { //must be a better way

	}


	//if reached target node
		// set target node to current node
		//select new target node

	//lerp to target node.

}