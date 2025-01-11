#include "RedGhost.h"

RedGhost::RedGhost(PathNode* start) : Ghost(start) {

	setTextures();
	mScatterTarget = {0,0};
	mRageSpeedMultiplier1 = 1.05f;
	mRageSpeedMultiplier2 = 1.1f;
	mGhostTex = mGhostUp;
	Reset();
	RageState(Unenraged);
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

	mTarget = mPlayer->Position();
	mTargetNode = mCurrentNode->ClosestConnection(mTarget);

}

void RedGhost::Reset() {
	mCurrentNode = mStartNode;
	mTargetNode = mCurrentNode->GetConnectionByIndex(0);
	Position(mStartNode->Position());
	mHousedState = Unhoused;
	mState = Scatter;
}


void RedGhost::handleScatter() {

	if (mScatterOverride) {
		mTargetNode = mCurrentNode->ClosestConnection(mPlayer->Position());
	}
	else {
		mTargetNode = mCurrentNode->ClosestConnection(mScatterTarget);
	}
	

}

void RedGhost::RageState(rageState state) {
	mRageState = state;

	int speedIndex = mPlayer->LevelNum() - 1;
	if (speedIndex >= mSpeedLevels) speedIndex = mSpeedLevels - 1;

	switch (mRageState) {
	case Unenraged:
		mSpeed = mDefaultSpeeds[speedIndex];
		mScatterOverride = false;
		break;
	case Enraged1:
		mSpeed = mDefaultSpeeds[speedIndex] * mRageSpeedMultiplier1;
		mScatterOverride = false;
		break;
	case Enraged2:
		mSpeed = mDefaultSpeeds[speedIndex] * mRageSpeedMultiplier2;
		mScatterOverride = true;
		mAudioManager->PlayMusic("siren2.wav");
		break;
	}
}

RedGhost::rageState RedGhost::RageState() {
	return mRageState;
}