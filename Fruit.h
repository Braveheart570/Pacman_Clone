#pragma once
#include "PhysicsManager.h"
#include "PhysEntity.h"
#include "CircleCollider.h"
#include "AudioManager.h"
#include "Player.h"

using namespace SDLFramework;

class Fruit : public PhysEntity {

public:

	Fruit(int fruitIndex);
	~Fruit();

	void Render() override;

	void Hit(PhysEntity* entity) override;
	bool IgnoreCollisions() override;

protected:

	int mScoreVal;

	Texture* mTexture;

	virtual void PlaySound();

};