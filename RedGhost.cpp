#include "RedGhost.h"

RedGhost::RedGhost(PathNode* start) : Ghost(start) {

	setTextures();
	mScatterTarget = {0,0};
	CruiseElroySpeedMultiplier1 = 1.5f;
	CruiseElroySpeedMultiplier2 = 2.0f;
	mGhostTex = mGhostUp; // temp? TODO
	Reset();
}


void RedGhost::setTextures() {

	mGhostUp = new AnimatedTexture("PacmanAtlas.png", 520, 65, 16, 14, 2, 0.5f, AnimatedTexture::Horizontal);
	mGhostUp->Parent(this);
	mGhostUp->Position(Vect2_Zero);
	mGhostUp->Scale(Vect2_One * 3);

	mGhostRight = new AnimatedTexture("PacmanAtlas.png", 488, 65, 16, 14, 2, 0.5f, AnimatedTexture::Horizontal);
	mGhostRight->Parent(this);
	mGhostRight->Position(Vect2_Zero);
	mGhostRight->Scale(Vect2_One * 3);

	mGhostDown = new AnimatedTexture("PacmanAtlas.png", 552, 65, 16, 14, 2, 0.5f, AnimatedTexture::Horizontal);
	mGhostDown->Parent(this);
	mGhostDown->Position(Vect2_Zero);
	mGhostDown->Scale(Vect2_One * 3);

	mGhostLeft = new AnimatedTexture("PacmanAtlas.png", 456, 65, 16, 14, 2, 0.5f, AnimatedTexture::Horizontal);
	mGhostLeft->Parent(this);
	mGhostLeft->Position(Vect2_Zero);
	mGhostLeft->Scale(Vect2_One * 3);
}

void RedGhost::setNewTargetNode() {

	target = Player::Instance()->Position();
	targetNode = CurrentNode->ClosestConnection(target);

}

void RedGhost::Reset() {
	CurrentNode = mStartNode;
	targetNode = CurrentNode->GetConnectionByIndex(0);
	Position(mStartNode->Position());
	mHousedState = Unhoused;
	mState = Scatter;
	mDefaultSpeed = mSpeed;
	mSpeed = mDefaultSpeed;
	mScatterOverride = false;
	
}

void RedGhost::Enrage() {

	if (mSpeed == mDefaultSpeed) {
		mSpeed *= CruiseElroySpeedMultiplier1;
	}
	else {
		mSpeed = mDefaultSpeed * CruiseElroySpeedMultiplier2;
		mScatterOverride = true;
	}

}


void RedGhost::handleScatter() {

	if (mScatterOverride) {
		targetNode = CurrentNode->ClosestConnection(Player::Instance()->Position());
	}
	else {
		targetNode = CurrentNode->ClosestConnection(mScatterTarget);
	}
	

}