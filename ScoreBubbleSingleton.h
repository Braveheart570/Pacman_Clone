#pragma once
#include "Texture.h"
#include "Timer.h"
#include "Player.h"

using namespace SDLFramework;

class ScoreBubble : public GameEntity {

public:

	enum Scores {g200,g400,g800,g1600,f100,f300,f500,f700,f1000,f2000,f3000,f5000};

	static ScoreBubble* Instance();
	static void Release();

	void Render() override;
	void Update() override;

	void DisplayGhostScore(Vector2 pos);
	void DisplayFruitScore(Vector2 pos, Scores score);

private:

	static ScoreBubble* sInstance;

	Timer* mTimer;
	Player* mPlayer;

	Texture* mGhost200pts;
	Texture* mGhost400pts;
	Texture* mGhost800pts;
	Texture* mGhost1600pts;

	Texture* mFruit100pts;
	Texture* mFruit300pts;
	Texture* mFruit500pts;
	Texture* mFruit700pts;
	Texture* mFruit1000pts;
	Texture* mFruit2000pts;
	Texture* mFruit3000pts;
	Texture* mFruit5000pts;

	Texture* mTex;

	float mDisplayTime;
	float mDisplayDurration;

	ScoreBubble();
	~ScoreBubble();

};