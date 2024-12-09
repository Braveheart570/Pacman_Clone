#pragma once
#include "PhysEntity.h"
#include "AnimatedTexture.h"
#include "InputManager.h"
#include "AudioManager.h"
#include "NodeManager.h"

using namespace SDLFramework;

class Player : public PhysEntity {

public:

	
	static Player* Instance();
	static void Release();


	void Update() override;
	void Render() override;


	//inherited
	//bool IgnoreCollisions() override;
	//void Hit(PhysEntity* other) override;

private:

	const static int EPSILON = 5;

	static Player* sInstance;

	float mSpeed;

	PathNode* targetNode;
	PathNode* CurrentNode;


	Timer* mTimer;
	InputManager* mInputManager;
	AudioManager* mAudioManager;

	Player();
	~Player();

	//temp
	Texture* mTex;

};