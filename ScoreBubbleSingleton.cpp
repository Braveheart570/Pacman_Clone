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

	mGhost200pts = new Texture("pacmanAtlas.png", 456, 133, 15, 7);
	mGhost200pts->Parent(this);
	mGhost200pts->Position(Vect2_Zero);
	mGhost200pts->Scale(Vect2_One * 3);
	mGhost200pts->Active(false);
	mGhost400pts = new Texture("pacmanAtlas.png", 472, 133, 15, 7);
	mGhost400pts->Parent(this);
	mGhost400pts->Position(Vect2_Zero);
	mGhost400pts->Scale(Vect2_One * 3);
	mGhost400pts->Active(false);
	mGhost800pts = new Texture("pacmanAtlas.png", 488, 133, 15, 7);
	mGhost800pts->Parent(this);
	mGhost800pts->Position(Vect2_Zero);
	mGhost800pts->Scale(Vect2_One * 3);
	mGhost800pts->Active(false);
	mGhost1600pts = new Texture("pacmanAtlas.png", 504, 133, 16, 7);
	mGhost1600pts->Parent(this);
	mGhost1600pts->Position(Vect2_Zero);
	mGhost1600pts->Scale(Vect2_One * 3);
	mGhost1600pts->Active(false);

	mFruit100pts = new Texture("pacmanAtlas.png", 458, 148, 13, 7);
	mFruit100pts->Parent(this);
	mFruit100pts->Position(Vect2_Zero);
	mFruit100pts->Scale(Vect2_One * 3);
	mFruit100pts->Active(false);
	mFruit300pts = new Texture("pacmanAtlas.png", 472, 148, 15, 7);
	mFruit300pts->Parent(this);
	mFruit300pts->Position(Vect2_Zero);
	mFruit300pts->Scale(Vect2_One * 3);
	mFruit300pts->Active(false);
	mFruit500pts = new Texture("pacmanAtlas.png", 488, 148, 15, 7);
	mFruit500pts->Parent(this);
	mFruit500pts->Position(Vect2_Zero);
	mFruit500pts->Scale(Vect2_One * 3);
	mFruit500pts->Active(false);
	mFruit700pts = new Texture("pacmanAtlas.png", 504, 148, 15, 7);
	mFruit700pts->Parent(this);
	mFruit700pts->Position(Vect2_Zero);
	mFruit700pts->Scale(Vect2_One * 3);
	mFruit700pts->Active(false);
	mFruit1000pts = new Texture("pacmanAtlas.png", 520, 148, 18, 7);
	mFruit1000pts->Parent(this);
	mFruit1000pts->Position(Vect2_Zero);
	mFruit1000pts->Scale(Vect2_One * 3);
	mFruit1000pts->Active(false);
	mFruit2000pts = new Texture("pacmanAtlas.png", 518, 164, 20, 7);
	mFruit2000pts->Parent(this);
	mFruit2000pts->Position(Vect2_Zero);
	mFruit2000pts->Scale(Vect2_One * 3);
	mFruit2000pts->Active(false);
	mFruit3000pts = new Texture("pacmanAtlas.png", 518, 180, 20, 7);
	mFruit3000pts->Parent(this);
	mFruit3000pts->Position(Vect2_Zero);
	mFruit3000pts->Scale(Vect2_One * 3);
	mFruit3000pts->Active(false);
	mFruit5000pts = new Texture("pacmanAtlas.png", 518, 196, 20, 7);
	mFruit5000pts->Parent(this);
	mFruit5000pts->Position(Vect2_Zero);
	mFruit5000pts->Scale(Vect2_One * 3);
	mFruit5000pts->Active(false);

	mDisplayTime = 0.0f;
	mDisplayDurration = 2.0f;
	mTex = nullptr;

	Active(false);

}

ScoreBubble::~ScoreBubble() {

	mTimer = nullptr;
	mPlayer = nullptr;

	delete mGhost200pts;
	mGhost200pts = nullptr;
	delete mGhost400pts;
	mGhost400pts = nullptr;
	delete mGhost800pts;
	mGhost800pts = nullptr;
	delete mGhost1600pts;
	mGhost1600pts = nullptr;

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

void ScoreBubble::DisplayGhostScore(Vector2 pos) {



	switch (mPlayer->GhostsEaten()) {
	case 1:
		mTex = mGhost200pts;
		break;
	case 2:
		mTex = mGhost400pts;
		break;
	case 3:
		mTex = mGhost800pts;
		break;
	case 4:
		mTex = mGhost1600pts;
		break;
	default:
		mTex = mGhost1600pts;
		break;
	}

	mDisplayTime = 0;
	Position(pos);
	Active(true);

}

void ScoreBubble::DisplayFruitScore(Vector2 pos, Scores score) {

	switch (score) {
	case f100:
		mTex = mFruit100pts;
		break;
	case f300:
		mTex = mFruit300pts;
		break;
	case f500:
		mTex = mFruit500pts;
		break;
	case f700:
		mTex = mFruit700pts;
		break;
	case f1000:
		mTex = mFruit1000pts;
		break;
	case f2000:
		mTex = mFruit2000pts;
		break;
	case f3000:
		mTex = mFruit3000pts;
		break;
	case f5000:
		mTex = mFruit5000pts;
		break;
	}

	mDisplayTime = 0;
	Position(pos);
	Active(true);

}