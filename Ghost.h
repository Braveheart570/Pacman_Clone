#pragma once
#include "PhysEntity.h"
#include "AnimatedTexture.h"
#include "NodeManager.h"
#include "Player.h"
#include "CircleCollider.h"
#include "PhysicsManager.h"

using namespace SDLFramework;

class Ghost : public PhysEntity {

public:

	Ghost(PathNode* start);
	~Ghost();

	void Update() override;
	void Render() override;

	void Hit(PhysEntity* entity) override;

private:

	const static int EPSILON = 1;

	NodeManager* mNodeManager;

	Vector2 target;

	PathNode* targetNode;
	PathNode* CurrentNode;

	AnimatedTexture* mGhostTex;
	AnimatedTexture* mFrightened;
	Texture* mEyes;

	float mSpeed;

	Timer* mTimer;


};