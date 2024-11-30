#pragma once
#include "PhysEntity.h"
#include "PathNode.h"
#include "AnimatedTexture.h"

using namespace SDLFramework;

class Ghost : public PhysEntity {

public:

	Ghost(std::vector<PathNode*> map, Vector2 pos);
	~Ghost();

	void Update() override;
	void Render() override;

private:

	std::vector<PathNode*> mMap;

	Vector2 target;

	PathNode* targetNode;
	PathNode* CurrentNode;

	AnimatedTexture* mGhostTex;
	AnimatedTexture* mFrightened;
	Texture* mEyes;



};