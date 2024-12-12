#pragma once
#include "Texture.h"
#include "Ghost.h"
#include "Player.h"
#include "Scoreboard.h"
#include "NodeManager.h"

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

	Ghost* mRedGhost;
	Ghost* mPinkGhost;
	Ghost* mBlueGhost;
	Ghost* mOrangeGhost;

	Scoreboard* mHighScoreboard;
	Scoreboard* mScoreboard;

	void CreateNodes();

};