#pragma once
#include "PhysEntity.h"
#include "AnimatedTexture.h"
#include "InputManager.h"
#include "AudioManager.h"
#include "NodeManager.h"
#include "PhysicsManager.h"
#include "CircleCollider.h"
#include "WrapNode.h"

using namespace SDLFramework;

class Player : public PhysEntity {

public:

	
	static Player* Instance();
	static void Release();


	void Update() override;
	void Render() override;

	Vector2 Dir();
	Vector2 nextTurn();


	int Score();
	void AddScore(int change);

	int Lives();

	void Hit(PhysEntity* other) override;

private:

	const static int EPSILON = 1;

	static Player* sInstance;

	float mSpeed;

	int mScore;

	int mLives;

	bool mWallHit;

	PathNode* targetNode;
	PathNode* CurrentNode;


	Timer* mTimer;
	InputManager* mInputManager;
	AudioManager* mAudioManager;

	Vector2 mNextTurn;


	Player();
	~Player();

	void HandleTexture();

	//temp
	AnimatedTexture* mPacmanTex;

	AnimatedTexture* mPacmanUp;
	AnimatedTexture* mPacmanRight;
	AnimatedTexture* mPacmanDown;
	AnimatedTexture* mPacmanLeft;

	AnimatedTexture* mPacmanDeath;

	Texture* mPacmanStopped;

};