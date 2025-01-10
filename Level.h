#pragma once
#include "Texture.h"
#include "Ghost.h"
#include "Player.h"
#include "Scoreboard.h"
#include "NodeManager.h"
#include "Pellet.h"
#include "RedGhost.h"
#include "PinkGhost.h"
#include "BlueGhost.h"
#include "OrangeGhost.h"
#include "PowerPellet.h"
#include "AudioManager.h"
#include "Fruit.h"
#include "ScoreBubbleSingleton.h"

using namespace SDLFramework;

class Level : public GameEntity {

public:

	Level();
	~Level();

	void Update() override;
	void Render() override;

	bool GameOver();

	void setLifeIcons();

private:

	Timer* mTimer;
	Player* mPlayer;
	NodeManager* mNodeManager;
	AudioManager* mAudioManager;

	Texture* mLevelBackground;

	RedGhost* mRedGhost;
	PinkGhost* mPinkGhost;
	BlueGhost* mBlueGhost;
	OrangeGhost* mOrangeGhost;

	std::vector<Pellet*> mPellets;

	Fruit* mFruit;

	Texture* mHighScoreLabel;
	Texture* mScoreLabel;

	Scoreboard* mHighScoreboard;
	Scoreboard* mScoreboard;

	Texture* mReadyLabel;
	Texture* mGameOverLabel;

	std::vector<Texture*> mPlayerLives;

	int mFruitIndex;
	int mNumOfFruitSpawned;

	float mPowerPelletFlashTime;
	float mPowerPelletFlashInterval;
	bool mRenderPowerPellet;

	bool mStageStarted;
	float mReadyDuration;
	float mReadyTime;

	bool mGameOver;

	float mPinkGhostReleaseDelay;
	float mPinkGhostReleaseTime;

	static const int ROWS = 10;
	float mRows[ROWS];

	static const int COLS = 8;
	float mCols[COLS];

	int mLivesGiven;

	static const int mEnrageLevels = 8;
	int mEnrage1Triggers[mEnrageLevels];
	int mEnrage2Triggers[mEnrageLevels];

	void CreatePellets();

	void resetLevel(bool newGame = false);

	
};