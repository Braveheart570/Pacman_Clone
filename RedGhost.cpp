#include "RedGhost.h"

RedGhost::RedGhost(PathNode* start) : Ghost(start) {

	setTextures();
	mScatterTarget = {0,0};
	mCruiseElroySpeedMultiplier1 = 1.5f;
	mCruiseElroySpeedMultiplier2 = 2.0f;
	mGhostTex = mGhostUp; // temp? TODO
	mDefaultSpeed = mSpeed;
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

	mTarget = Player::Instance()->Position();
	mTargetNode = mCurrentNode->ClosestConnection(mTarget);

}

void RedGhost::Reset() {
	mCurrentNode = mStartNode;
	mTargetNode = mCurrentNode->GetConnectionByIndex(0);
	Position(mStartNode->Position());
	mHousedState = Unhoused;
	mState = Scatter;
	mSpeed = mDefaultSpeed;
	mScatterOverride = false;
	
}

void RedGhost::Enrage() {

	if (mSpeed == mDefaultSpeed) {
		mSpeed *= mCruiseElroySpeedMultiplier1;
	}
	else {
		mSpeed = mDefaultSpeed * mCruiseElroySpeedMultiplier2;
		mScatterOverride = true;
	}
}

bool RedGhost::Enraged() {
	if (mSpeed != mDefaultSpeed) {
		return true;
	}
	else {
		return false;
	}
}


void RedGhost::handleScatter() {

	if (mScatterOverride) {
		mTargetNode = mCurrentNode->ClosestConnection(Player::Instance()->Position());
	}
	else {
		mTargetNode = mCurrentNode->ClosestConnection(mScatterTarget);
	}
	

}