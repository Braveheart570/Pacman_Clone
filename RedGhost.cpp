#include "RedGhost.h"

RedGhost::RedGhost(PathNode* start) : Ghost(start) {

	mGhostTex = new AnimatedTexture("PacmanAtlas.png", 488, 65, 16, 14, 2, 0.5f, AnimatedTexture::Horizontal);
	mGhostTex->Parent(this);
	mGhostTex->Position(Vect2_Zero);
	mGhostTex->Scale(Vect2_One * 3);

}


void RedGhost::setNewTargetNode() {

	target = Player::Instance()->Position();
	targetNode = CurrentNode->ClosestConnection(target);

}