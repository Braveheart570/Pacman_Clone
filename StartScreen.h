#pragma once
#include "GameEntity.h"
#include "AnimatedTexture.h"
#include "Scoreboard.h"
#include "Timer.h"
#include "InputManager.h"
#include "Player.h"

using namespace SDLFramework;

class StartScreen : public GameEntity {

public:

	StartScreen();
	~StartScreen();

	void Update() override;
	void Render() override;

	void ResetAnimation();

private:

	Timer* mTimer;
	InputManager* mInputManager;

	float scrawlTime;
	float mPowerPelletFlashTime;
	float mPowerPelletFlashInterval;
	float mRenderPowerPellet;

	float mPauseTime;
	float mPauseDurration;
	bool mPause;

	Texture* mOneUplabel;
	Texture* mHighScoreLabel;
	Texture* mTwoUpLabel;

	Scoreboard* mPlayerOneScoreboard;
	Scoreboard* mHighScoreboard;
	Scoreboard* mPlayerTwoScoreBoard;

	Texture* mGhostTableLabel;

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

	AnimatedTexture* mFrightenedGhost1;
	AnimatedTexture* mFrightenedGhost2;
	AnimatedTexture* mFrightenedGhost3;
	AnimatedTexture* mFrightenedGhost4;

	AnimatedTexture* mPacmanLeft;
	AnimatedTexture* mPacmanRight;

	Texture* mPowerPellet;
	Texture* mPowerPellet2;
	Texture* mPellet;

	Texture* mPowerPelletPTS;
	Texture* mPelletPTS;

	Texture* mNamcoLabel;

	Texture* m200pts;
	Texture* m400pts;
	Texture* m800pts;
	Texture* m1600pts;


	int mSpeed;

	bool mPowerPelletEaten;

	bool mRedGhostEaten;
	bool mPinkGhostEaten;
	bool mBlueGhostEaten;
	bool mOrangeGhostEaten;

	void HandleEntityInit(GameEntity* tex, Vector2 pos = Vect2_Zero, Vector2 scale = Vect2_One);

};