#include "ScoreBubbleSingleton.h"

ScoreBubble* ScoreBubble::sInstance = nullptr;

ScoreBubble* ScoreBubble::Instance() {
	if (sInstance == nullptr) {
		sInstance = new ScoreBubble();
	}
	return sInstance;
}

void ScoreBubble::Release() {
	delete sInstance;
	sInstance = nullptr;
}

ScoreBubble::ScoreBubble() {

	mTimer = Timer::Instance();
	mPlayer = Player::Instance();

	m200pts = new Texture("pacmanAtlas.png", 456, 133, 15, 7);
	m200pts->Parent(this);
	m200pts->Position(Vect2_Zero);
	m200pts->Scale(Vect2_One * 3);
	m200pts->Active(false);
	m400pts = new Texture("pacmanAtlas.png", 472, 133, 15, 7);
	m400pts->Parent(this);
	m400pts->Position(Vect2_Zero);
	m400pts->Scale(Vect2_One * 3);
	m400pts->Active(false);
	m800pts = new Texture("pacmanAtlas.png", 488, 133, 15, 7);
	m800pts->Parent(this);
	m800pts->Position(Vect2_Zero);
	m800pts->Scale(Vect2_One * 3);
	m800pts->Active(false);
	m1600pts = new Texture("pacmanAtlas.png", 504, 133, 16, 7);
	m1600pts->Parent(this);
	m1600pts->Position(Vect2_Zero);
	m1600pts->Scale(Vect2_One * 3);
	m1600pts->Active(false);

	mDisplayDurration = 2.0f;

	Active(false);

}

ScoreBubble::~ScoreBubble() {

	mTimer = nullptr;
	mPlayer = nullptr;

	delete m200pts;
	m200pts = nullptr;
	delete m400pts;
	m400pts = nullptr;
	delete m800pts;
	m800pts = nullptr;
	delete m1600pts;
	m1600pts = nullptr;

}

void ScoreBubble::Render() {
	if (Active()) {
		mTex->Render();
	}
}

void ScoreBubble::Update() {

	if (Active()) {
		mDisplayTime += mTimer->DeltaTime();
		if (mDisplayTime >= mDisplayDurration) {
			Active(false);
		}
	}

}

void ScoreBubble::DisplayScore(Vector2 pos) {



	switch (mPlayer->GhostsEaten()) {
	case 1:
		mTex = m200pts;
		break;
	case 2:
		mTex = m400pts;
		break;
	case 3:
		mTex = m800pts;
		break;
	case 4:
		mTex = m1600pts;
		break;
	default:
		mTex = m1600pts;
		break;
	}

	mDisplayTime = 0;
	Position(pos);
	Active(true);

}