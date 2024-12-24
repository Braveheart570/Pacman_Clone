#include "Fruit.h"

Fruit::Fruit() {

	mTexture = new Texture("PacmanAtlas.png", 490, 50, 12, 12);
	mTexture->Parent(this);
	mTexture->Scale(Vect2_One * 3);

	AddCollider(new CircleCollider(10, true));
	AddCollider(new CircleCollider(10));

	mScoreVal = 100;

	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Consumable);

	Position({ Graphics::SCREEN_WIDTH / 2,(Graphics::SCREEN_HEIGHT / 2) + 50.0f});

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