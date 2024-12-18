#pragma once
#include "PhysEntity.h"
#include "CircleCollider.h"
#include "PhysicsManager.h"

using namespace SDLFramework;

class Pellet : public PhysEntity {

public:

	Pellet(Vector2 pos);
	~Pellet();

	void Render() override;

	void Hit(PhysEntity* entity) override;
	bool IgnoreCollisions() override;

private:

	Texture* mTexture;

};