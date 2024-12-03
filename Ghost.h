#pragma once
#include "PhysEntity.h"
#include "AnimatedTexture.h"
#include "NodeManager.h"

using namespace SDLFramework;

class Ghost : public PhysEntity {

public:

	Ghost(Vector2 pos);
	~Ghost();

	void Update() override;
	void Render() override;

private:

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