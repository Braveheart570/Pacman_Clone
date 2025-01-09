#pragma once
#include "PhysEntity.h"
#include "AnimatedTexture.h"
#include "NodeManager.h"
#include "Player.h"
#include "CircleCollider.h"
#include "PhysicsManager.h"
#include "Random.h"
#include "Timer.h"
#include "ScoreBubbleSingleton.h"

using namespace SDLFramework;

class Ghost : public PhysEntity {

public:

	enum GhostState {Scatter,Hunt,Frightened,Dead};
	enum HousedState {Housed,Exiting,Unhoused};


	Ghost(PathNode* start);
	~Ghost();

	virtual void setTextures() = 0;

	void Update() override;
	void Render() override;

	virtual void setNewTargetNode() = 0;

	void Hit(PhysEntity* entity) override;

	void State(GhostState state, bool flip = true);
	GhostState State();

	virtual void Reset();

	HousedState HouseState();
	void Unhouse();

protected:

	void HandleTexture();

	void HandleHoused();

	virtual void handleScatter();

	void HandleDead();

	const static int EPSILON = 1;

	NodeManager* mNodeManager;
	Timer* mTimer;
	AudioManager* mAudioManager;
	Player* mPlayer;

	bool mCanFrighten;
	float mFlashSpeed;
	float mFlashTime;

	std::vector<PathNode*> mHouseNodes;

	Vector2 mTarget;
	Vector2 mScatterTarget;

	PathNode* mStartNode;

	PathNode* mTargetNode;
	PathNode* mCurrentNode;

	Texture* mGhostTex;

	AnimatedTexture* mGhostUp;
	AnimatedTexture* mGhostRight;
	AnimatedTexture* mGhostDown;
	AnimatedTexture* mGhostLeft;
	AnimatedTexture* mFrightened1;
	AnimatedTexture* mFrightened2;
	Texture* mGhostUpDead;
	Texture* mGhostRightDead;
	Texture* mGhostDownDead;
	Texture* mGhostLeftDead;

	float mSpeed;
	float mDefaultSpeed;

	float mStateSwitchDelay;
	float mStateSwitchTime;

	GhostState mState;
	HousedState mHousedState;

};