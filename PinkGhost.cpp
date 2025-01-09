#include "PinkGhost.h"

PinkGhost::PinkGhost(PathNode* start) : Ghost(start) {

	setTextures();
	mScatterTarget = { Graphics::SCREEN_WIDTH,0 };
	mGhostTex = mGhostRight;
}

void PinkGhost::setTextures() {

	mGhostUp = new AnimatedTexture("PacmanAtlas.png", 520, 81, 16, 14, 2, 0.5f, AnimatedTexture::Horizontal);
	mGhostUp->Parent(this);
	mGhostUp->Position(Vect2_Zero);
	mGhostUp->Scale(Vect2_One * 3);

	mGhostRight = new AnimatedTexture("PacmanAtlas.png", 488, 81, 16, 14, 2, 0.5f, AnimatedTexture::Horizontal);
	mGhostRight->Parent(this);
	mGhostRight->Position(Vect2_Zero);
	mGhostRight->Scale(Vect2_One * 3);

	mGhostDown = new AnimatedTexture("PacmanAtlas.png", 552, 81, 16, 14, 2, 0.5f, AnimatedTexture::Horizontal);
	mGhostDown->Parent(this);
	mGhostDown->Position(Vect2_Zero);
	mGhostDown->Scale(Vect2_One * 3);

	mGhostLeft = new AnimatedTexture("PacmanAtlas.png", 456, 81, 16, 14, 2, 0.5f, AnimatedTexture::Horizontal);
	mGhostLeft->Parent(this);
	mGhostLeft->Position(Vect2_Zero);
	mGhostLeft->Scale(Vect2_One * 3);
}

void PinkGhost::setNewTargetNode() {

	Vector2 aheadOfPlayer = Player::Instance()->nextTurn() * 50 * 4;

	mTarget = Player::Instance()->Position() + aheadOfPlayer;

	mTargetNode = mCurrentNode->ClosestConnection(mTarget);

}