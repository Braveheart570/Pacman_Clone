#include "PowerPellet.h"

PowerPellet::PowerPellet(Vector2 pos) : Pellet(pos) {

	delete mTexture;
	mTexture = new Texture("PacmanAtlas.png", 8, 24, 8, 8);
	mTexture->Parent(this);
	mTexture->Position(0, 0);
	mTexture->Scale(Vect2_One * 3);

	mScoreVal = 50;
}


void Pellet::Hit(PhysEntity* entity) {

	//todo

	Player::Instance()->AddScore(mScoreVal);
	Active(false);
}