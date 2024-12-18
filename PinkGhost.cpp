#include "PinkGhost.h"

PinkGhost::PinkGhost(PathNode* start) : Ghost(start) {

	mGhostTex = new AnimatedTexture("PacmanAtlas.png", 488, 81, 16, 14, 2, 0.5f, AnimatedTexture::Horizontal);
	mGhostTex->Parent(this);
	mGhostTex->Position(Vect2_Zero);
	mGhostTex->Scale(Vect2_One * 3);

}

void PinkGhost::setNewTargetNode() {

	Vector2 aheadOfPlayer = Player::Instance()->Dir() * 50 * 4;;
	if (aheadOfPlayer.x = aheadOfPlayer.x) {
		target = Player::Instance()->Position() + aheadOfPlayer;
	}
	std::cout << aheadOfPlayer.x << ", " << aheadOfPlayer.y << std::endl;
	

	targetNode = CurrentNode->ClosestConnection(target);

}