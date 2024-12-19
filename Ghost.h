#pragma once
#include "PhysEntity.h"
#include "AnimatedTexture.h"
#include "NodeManager.h"
#include "Player.h"
#include "CircleCollider.h"
#include "PhysicsManager.h"
#include "Random.h"

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

	Vector2 target;
	Vector2 mScatterTarget;

	PathNode* targetNode;
	PathNode* CurrentNode;

	AnimatedTexture* mGhostTex;

	AnimatedTexture* mGhostUp;
	AnimatedTexture* mGhostRight;
	AnimatedTexture* mGhostDown;
	AnimatedTexture* mGhostLeft;
	AnimatedTexture* mFrightened;
	Texture* mEyes;

	float mSpeed;

	GhostState mState;

	Timer* mTimer;


};