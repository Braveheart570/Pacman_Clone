#include "BlueGhost.h"

BlueGhost::BlueGhost(PathNode* start, RedGhost* red) : Ghost(start){

	mGhostTex = new AnimatedTexture("PacmanAtlas.png", 488, 97, 16, 14, 2, 0.5f, AnimatedTexture::Horizontal);
	mGhostTex->Parent(this);
	mGhostTex->Position(Vect2_Zero);
	mGhostTex->Scale(Vect2_One * 3);

	mRedGhost = red;

}

void BlueGhost::setNewTargetNode() {

	Vector2 posAheadOfPlayer = (Player::Instance()->nextTurn() * 50 * 2) + Player::Instance()->Position();

	Vector2 redToAheadOfPlayer = posAheadOfPlayer - mRedGhost->Position();

	target = posAheadOfPlayer + redToAheadOfPlayer;

	targetNode = CurrentNode->ClosestConnection(target);


}

BlueGhost::~BlueGhost() {

	mRedGhost = nullptr;

}