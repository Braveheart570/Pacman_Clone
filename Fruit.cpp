#include "Fruit.h"

Fruit::Fruit(int fruitIndex) {

	if (fruitIndex == 0) {
		mTexture = new Texture("PacmanAtlas.png", 490, 50, 12, 12);
		mScoreVal = 100;
	}
	else if (fruitIndex == 1) {
		mTexture = new Texture("PacmanAtlas.png", 506, 50, 11, 12);
		mScoreVal = 300;
	}
	else if (fruitIndex == 2) {
		mTexture = new Texture("PacmanAtlas.png", 522, 50, 12, 12);
		mScoreVal = 500;
	}
	else if (fruitIndex == 3) {
		mTexture = new Texture("PacmanAtlas.png", 538, 50, 12, 12);
		mScoreVal = 700;
	}
	else if (fruitIndex == 4) {
		mTexture = new Texture("PacmanAtlas.png", 555, 49, 11, 14);
		mScoreVal = 1000;
	}
	else if (fruitIndex == 5) {
		mTexture = new Texture("PacmanAtlas.png", 570, 51, 11, 12);
		mScoreVal = 2000;
	}
	else if (fruitIndex == 6) {
		mTexture = new Texture("PacmanAtlas.png", 586, 50, 12, 13);
		mScoreVal = 3000;
	}
	else {
		mTexture = new Texture("PacmanAtlas.png", 604, 50, 7, 13);
		mScoreVal = 5000;
	}
	
	mTexture->Parent(this);
	mTexture->Scale(Vect2_One * 3);

	AddCollider(new CircleCollider(10, true));
	AddCollider(new CircleCollider(10));

	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Consumable);

	Position({ Graphics::SCREEN_WIDTH / 2,(Graphics::SCREEN_HEIGHT / 2) + 50.0f});

	Active(false);

}

Fruit::~Fruit() {
	delete mTexture;
	mTexture = nullptr;
}

void Fruit::Render() {
	if (Active()) {
		mTexture->Render();
		//PhysEntity::Render();
	}
}

void Fruit::Hit(PhysEntity* entity) {
	Player::Instance()->AddScore(mScoreVal);
	Active(false);
	PlaySound();
}

bool Fruit::IgnoreCollisions() {

	return !Active();

}

void Fruit::PlaySound() {

	AudioManager::Instance()->PlaySFX("fruit.wav", 0, 1);

}