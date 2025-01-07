#pragma once
#include "Texture.h"
#include "Timer.h"
#include "Player.h"

using namespace SDLFramework;

class ScoreBubble : public GameEntity {

public:

	enum Scores {s200,s400,s800,s1600};

	static ScoreBubble* Instance();
	static void Release();

	void Render() override;
	void Update() override;

	void DisplayScore(Vector2 pos);

private:

	static ScoreBubble* sInstance;

	Timer* mTimer;
	Player* mPlayer;

	Texture* m200pts;
	Texture* m400pts;
	Texture* m800pts;
	Texture* m1600pts;

	Texture* mTex;

	float mDisplayTime;
	float mDisplayDurration;

	ScoreBubble();
	~ScoreBubble();

};