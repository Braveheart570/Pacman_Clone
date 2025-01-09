#pragma once
#include "PhysicsManager.h"
#include "PhysEntity.h"
#include "CircleCollider.h"
#include "AudioManager.h"
#include "Player.h"
#include "ScoreBubbleSingleton.h"

using namespace SDLFramework;

class Fruit : public PhysEntity {

public:

	Fruit(int fruitIndex);
	~Fruit();

	void Render() override;
	void Update() override;

	void Hit(PhysEntity* entity) override;
	bool IgnoreCollisions() override;

protected:

	Timer* mTimer;
	ScoreBubble* mScoreBubble;

	float mActiveTime;
	float mActiveDurration;

	int mScoreVal;

	Texture* mTexture;

	virtual void PlaySound();

};