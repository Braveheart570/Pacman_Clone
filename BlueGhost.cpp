#include "BlueGhost.h"

BlueGhost::BlueGhost(PathNode* start, RedGhost* red) : Ghost(start){

	setTextures();
	mRedGhost = red;
	mScatterTarget = {Graphics::SCREEN_WIDTH,Graphics::SCREEN_HEIGHT };
	mGhostTex = mGhostDown; // temp? TODO

}

void BlueGhost::setTextures() {
	mGhostUp = new AnimatedTexture("PacmanAtlas.png", 520, 97, 16, 14, 2, 0.5f, AnimatedTexture::Horizontal);
	mGhostUp->Parent(this);
	mGhostUp->Position(Vect2_Zero);
	mGhostUp->Scale(Vect2_One * 3);

	mGhostRight = new AnimatedTexture("PacmanAtlas.png", 488, 97, 16, 14, 2, 0.5f, AnimatedTexture::Horizontal);
	mGhostRight->Parent(this);
	mGhostRight->Position(Vect2_Zero);
	mGhostRight->Scale(Vect2_One * 3);

	mGhostDown = new AnimatedTexture("PacmanAtlas.png", 552, 97, 16, 14, 2, 0.5f, AnimatedTexture::Horizontal);
	mGhostDown->Parent(this);
	mGhostDown->Position(Vect2_Zero);
	mGhostDown->Scale(Vect2_One * 3);

	mGhostLeft = new AnimatedTexture("PacmanAtlas.png", 456, 97, 16, 14, 2, 0.5f, AnimatedTexture::Horizontal);
	mGhostLeft->Parent(this);
	mGhostLeft->Position(Vect2_Zero);
	mGhostLeft->Scale(Vect2_One * 3);
}

void BlueGhost::setNewTargetNode() {

	Vector2 posAheadOfPlayer = (Player::Instance()->nextTurn() * 50 * 2) + Player::Instance()->Position();

	Vector2 redToAheadOfPlayer = posAheadOfPlayer - mRedGhost->Position();

	mTarget = posAheadOfPlayer + redToAheadOfPlayer;

	mTargetNode = mCurrentNode->ClosestConnection(mTarget);


}

BlueGhost::~BlueGhost() {

	mRedGhost = nullptr;

}