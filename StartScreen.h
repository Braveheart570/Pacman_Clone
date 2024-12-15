#pragma once
#include "GameEntity.h"
#include "AnimatedTexture.h"
#include "Scoreboard.h"
#include "Timer.h"
#include "InputManager.h"

using namespace SDLFramework;

class startScreen : public GameEntity {

public:

	startScreen();
	~startScreen();

	void Update() override;
	void Render() override;

	void ResetAnimation();

private:

	Timer* mTimer;
	InputManager* mInputManager;

	Texture* mOneUplabel;
	Texture* mHighScoreLabel;
	Texture* mTwoUpLabel;

	Scoreboard* mPlayerOneScoreboard;
	Scoreboard* mHighScoreboard;
	Scoreboard* mPlayerTwoScoreBoard;

	Texture* GhostTableLabel;

	Texture* mRedGhost;
	AnimatedTexture* mRedGhostAnim;
	Texture* mRedGhostLabel;

	Texture* mPinkGhost;
	AnimatedTexture* mPinkGhostAnim;
	Texture* mPinkGhostLabel;

	Texture* mBlueGhost;
	AnimatedTexture* mBlueGhostAnim;
	Texture* mBlueGhostLabel;

	Texture* mOrangeGhost;
	AnimatedTexture* mOrangeGhostAnim;
	Texture* mOrangeGhostLabel;

	AnimatedTexture* mPacmanLeft;
	AnimatedTexture* mPacmanRight;

	Texture* mPowerPellet;
	Texture* mPowerPellet2;
	Texture* mPellet;

	Texture* mPowerPelletPTS;
	Texture* mPelletPTS;

	Texture* mNamcoLabel;

	int mSpeed;

	void HandleEntityInit(GameEntity* tex, Vector2 pos = Vect2_Zero, Vector2 scale = Vect2_One);

};