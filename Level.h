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

	static const int ROWS = 10;
	float mRows[ROWS];

	static const int COLS = 8;
	float mCols[COLS];

	int mScore;

	void CreateNodes();

};