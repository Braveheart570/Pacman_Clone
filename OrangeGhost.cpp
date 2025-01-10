#include "OrangeGhost.h"

OrangeGhost::OrangeGhost(PathNode* start) : Ghost(start) {

	setTextures();
	mScatterTarget = { 0,Graphics::SCREEN_HEIGHT };
	mGhostTex = mGhostDown;

}

void OrangeGhost::setTextures() {

	mGhostUp = new AnimatedTexture("PacmanAtlas.png", 520, 113, 16, 14, 2, 0.5f, AnimatedTexture::Horizontal);
	mGhostUp->Parent(this);
	mGhostUp->Position(Vect2_Zero);
	mGhostUp->Scale(Vect2_One * 3);

	mGhostRight = new AnimatedTexture("PacmanAtlas.png", 488, 113, 16, 14, 2, 0.5f, AnimatedTexture::Horizontal);
	mGhostRight->Parent(this);
	mGhostRight->Position(Vect2_Zero);
	mGhostRight->Scale(Vect2_One * 3);

	mGhostDown = new AnimatedTexture("PacmanAtlas.png", 552, 113, 16, 14, 2, 0.5f, AnimatedTexture::Horizontal);
	mGhostDown->Parent(this);
	mGhostDown->Position(Vect2_Zero);
	mGhostDown->Scale(Vect2_One * 3);

	mGhostLeft = new AnimatedTexture("PacmanAtlas.png", 456, 113, 16, 14, 2, 0.5f, AnimatedTexture::Horizontal);
	mGhostLeft->Parent(this);
	mGhostLeft->Position(Vect2_Zero);
	mGhostLeft->Scale(Vect2_One * 3);

}

void OrangeGhost::setNewTargetNode() {

	float distToPlayer = (mPlayer->Position() - Position()).Magnitude();

	if (distToPlayer > 8*25) {
		mTarget = mPlayer->Position();
	}
	else {
		mTarget = mScatterTarget;
	}

	mTargetNode = mCurrentNode->ClosestConnection(mTarget);

}