#pragma once
#include "PhysEntity.h"
#include "AnimatedTexture.h"
#include "InputManager.h"
#include "AudioManager.h"

using namespace SDLFramework;

class Player : public PhysEntity {

public:

	Player();
	~Player();

	void Update() override;
	void Render() override;


	//inherited
	//bool IgnoreCollisions() override;
	//void Hit(PhysEntity* other) override;

private:

	const static int EPSILON = 5;

	float mSpeed;

	Timer* mTimer;
	InputManager* mInputManager;
	AudioManager* mAudioManager;

	//temp
	Texture* mTex;

};