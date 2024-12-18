#include "Pellet.h"

Pellet::Pellet(Vector2 pos) {
	mTexture = new Texture("PacmanAtlas.png",11,11,2,2);
	mTexture->Parent(this);
	mTexture->Scale(Vect2_One*3);

	AddCollider(new CircleCollider(10,true));
	AddCollider(new CircleCollider(10));
	mId = PhysicsManager::Instance()->RegisterEntity(this,PhysicsManager::CollisionLayers::HostileProjectile);

	Position(pos);
}

Pellet::~Pellet() {
	delete mTexture;
	mTexture = nullptr;
}

void Pellet::Render() {

	mTexture->Render();
	PhysEntity::Render();

}
	


