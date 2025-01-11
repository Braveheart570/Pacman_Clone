#pragma once
#include "PhysEntity.h"
#include "CircleCollider.h"
#include "PhysicsManager.h"
#include "Player.h"

using namespace SDLFramework;

class Pellet : public PhysEntity {

public:

	Pellet(Vector2 pos);
	~Pellet();

	void Render() override;

	void Hit(PhysEntity* entity) override;
	bool IgnoreCollisions() override;

protected:

	int mScoreVal;

	Texture* mTexture;
};