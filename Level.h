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

using namespace SDLFramework;

class Level : public GameEntity {

public:

	Level();
	~Level();

	void Update() override;
	void Render() override;

private:

	Timer* mTimer;
	Player* mPlayer;
	NodeManager* mNodeManager;

	Texture* mLevelBackground;

	RedGhost* mRedGhost;
	PinkGhost* mPinkGhost;
	BlueGhost* mBlueGhost;
	OrangeGhost* mOrangeGhost;

	std::vector<Pellet*> mPellets;

	Scoreboard* mHighScoreboard;
	Scoreboard* mScoreboard;

	Texture* mReadyLabel;
	Texture* mGameOverLabel;

	std::vector<Texture*> mPlayerLives;

	static const int ROWS = 10;
	float mRows[ROWS];

	static const int COLS = 8;
	float mCols[COLS];

	int mScore;

	bool mStageStarted;
	float mReadyDuration;
	float mReadyTime;

	void CreateNodes();

	void resetLevel(bool newGame = false);

	void setLifeIcons();
};