#include "OrangeGhost.h"

OrangeGhost::OrangeGhost(PathNode* start) : Ghost(start) {

	mGhostTex = new AnimatedTexture("PacmanAtlas.png", 488, 113, 16, 14, 2, 0.5f, AnimatedTexture::Horizontal);
	mGhostTex->Parent(this);
	mGhostTex->Position(Vect2_Zero);
	mGhostTex->Scale(Vect2_One * 3);

}

void OrangeGhost::setNewTargetNode() {

	float distToPlayer = (Player::Instance()->Position() - Position()).Magnitude();

	if (distToPlayer > 8*50) {
		target = Player::Instance()->Position();
	}
	else {
		target = { 0,Graphics::SCREEN_HEIGHT };
	}

	targetNode = CurrentNode->ClosestConnection(target);

}