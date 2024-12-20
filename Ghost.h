#pragma once
#include "PhysEntity.h"
#include "AnimatedTexture.h"
#include "NodeManager.h"
#include "Player.h"
#include "CircleCollider.h"
#include "PhysicsManager.h"
#include "Random.h"
#include "Timer.h"

using namespace SDLFramework;

class Ghost : public PhysEntity {

public:

	enum GhostState {Scatter,Hunt,Frightened,Dead};


	Ghost(PathNode* start);
	~Ghost();

	virtual void setTextures() = 0;

	void Update() override;
	void Render() override;

	virtual void setNewTargetNode() = 0;

	void Hit(PhysEntity* entity) override;

protected:

	void HandleTexture();

	const static int EPSILON = 1;

	NodeManager* mNodeManager;
	Timer* mTimer;

	float mFlashSpeed;
	float mFlashTime;

	float mFrightenedTime;
	float mFrightenedDuration;

	Vector2 target;
	Vector2 mScatterTarget;

	PathNode* targetNode;
	PathNode* CurrentNode;

	AnimatedTexture* mGhostTex;

	AnimatedTexture* mGhostUp;
	AnimatedTexture* mGhostRight;
	AnimatedTexture* mGhostDown;
	AnimatedTexture* mGhostLeft;
	AnimatedTexture* mFrightened1;
	AnimatedTexture* mFrightened2;
	Texture* mEyes;

	float mSpeed;

	GhostState mState;


};