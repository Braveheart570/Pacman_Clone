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

	void MoveKeys();

	void Update() override;
	void Render() override;

	Vector2 Dir();
	Vector2 nextTurn();

	int Score();
	void AddScore(int change);
	void ResetScore();

	int HighScore();
	void HighScore(int highscore);

	void GhostEaten();
	int GhostsEaten();

	int Lives();
	void addLife();

	bool Energized();
	void Energize();
	float EnergizedTimeLeftPercent();

	void Hit(PhysEntity* other) override;

	void Die();

	bool IsDying();
	bool isDead();

	void Respawn();

	void ResetPelletsEaten();
	int PelletsEaten();

	int LevelNum();
	void IncrementLevelNum();
	void ResetLevelNum();


private:

	const static int EPSILON = 1;

	static Player* sInstance;

	int mLevelNum;

	static const int mSpeedLevels = 8;
	float mSpeeds[mSpeedLevels];

	int mScore;
	int mHighScore;
	int mPelletsEaten;

	bool mIsDieing;
	bool mIsDead;

	int mLives;

	bool mWallHit;

	bool mEnergized;
	float mFrightenedTime;
	const static int mFrightenedLevels = 8;
	float mFrightenedDurations[mFrightenedLevels];
	int mGhostsEaten;

	bool mPlayingWaka;
	float mWakaBufferTime;
	float mWakaBufferDuration;
	const static int mWakaChannel = 1;

	PathNode* mTargetNode;
	PathNode* mCurrentNode;
	PathNode* mStartNode;


	Timer* mTimer;
	InputManager* mInputManager;
	AudioManager* mAudioManager;

	Vector2 mNextTurn;

	AnimatedTexture* mPacmanTex;

	AnimatedTexture* mPacmanUp;
	AnimatedTexture* mPacmanRight;
	AnimatedTexture* mPacmanDown;
	AnimatedTexture* mPacmanLeft;

	AnimatedTexture* mPacmanDeath;

	Texture* mPacmanStopped;

	Player();
	~Player();

	void HandleTexture();

};