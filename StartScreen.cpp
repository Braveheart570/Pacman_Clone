#include "StartScreen.h"

StartScreen::StartScreen() {

	mTimer = Timer::Instance();
	mInputManager = InputManager::Instance();

	std::string redName = "SHADOW";
	std::string pinkName = "SPEEDY";
	std::string blueName = "BASHFUL";
	std::string orangeName = "POKEY";
	redName = redName + std::string(10 - redName.length(),'-') + "\"BLINKY\"";
	pinkName = pinkName + std::string(11 - pinkName.length(),'-') + "\"PINKY\"";
	blueName = blueName + std::string(12 - blueName.length(), '-') + "\"INKY\"";
	orangeName = orangeName + std::string(11 - orangeName.length(),'-') + "\"CLYDE\"";

	mSpeed = 100;
	mPowerPelletFlashInterval = 0.3f;
	mPauseDurration = 0.5f;
	
	mPowerPelletEaten = false;
	mRedGhostEaten = false;
	mPinkGhostEaten = false;
	mBlueGhostEaten = false;
	mOrangeGhostEaten = false;
	mPowerPelletFlashTime = 0;
	mRenderPowerPellet = true;
	scrawlTime = 0;
	mPauseTime = 0;
	mPause = false;

	mOneUplabel = new Texture("1UP", "emulogic.ttf", 20, {255,255,255});
	HandleEntityInit(mOneUplabel, {100,25});
	mHighScoreLabel = new Texture("HIGH SCORE", "emulogic.ttf", 20, { 255,255,255 });
	HandleEntityInit(mHighScoreLabel, {Graphics::SCREEN_WIDTH/2,25});
	mTwoUpLabel = new Texture("2UP", "emulogic.ttf", 20, { 255,255,255 });
	HandleEntityInit(mTwoUpLabel,{Graphics::SCREEN_WIDTH-100,25});

	mPlayerOneScoreboard = new Scoreboard();
	HandleEntityInit(mPlayerOneScoreboard, mOneUplabel->Position() + Vector2(0,30));
	mHighScoreboard = new Scoreboard();
	HandleEntityInit(mHighScoreboard, mHighScoreLabel->Position() + Vector2(0, 30));
	mPlayerTwoScoreBoard = new Scoreboard();
	HandleEntityInit(mPlayerTwoScoreBoard, mTwoUpLabel->Position() + Vector2(0, 30));

	GhostTableLabel = new Texture("CHARACTER / NICKNAME", "emulogic.ttf", 20, {255,255,255});
	HandleEntityInit(GhostTableLabel, { (Graphics::SCREEN_WIDTH / 2)+50, 220 });

	mRedGhost = new Texture("PacmanAtlas.png", 457, 65, 14, 14);
	HandleEntityInit(mRedGhost, {100,300},Vect2_One*3);
	mRedGhostAnim = new AnimatedTexture("PacmanAtlas.png", 489, 65, 16, 14, 2, 0.5f, AnimatedTexture::Horizontal);
	HandleEntityInit(mRedGhostAnim, { Graphics::SCREEN_WIDTH + 200,600 }, Vect2_One * 3);
	mRedGhostLabel = new Texture(redName, "emulogic.ttf", 20, { 255,0,0 });
	HandleEntityInit(mRedGhostLabel, { (Graphics::SCREEN_WIDTH / 2)+50,300 });

	mPinkGhost = new Texture("PacmanAtlas.png", 457, 81, 14, 14);
	HandleEntityInit(mPinkGhost, { 100,350 }, Vect2_One * 3);
	mPinkGhostAnim = new AnimatedTexture("PacmanAtlas.png", 489, 81, 16, 14, 2, 0.5f, AnimatedTexture::Horizontal);
	HandleEntityInit(mPinkGhostAnim, { Graphics::SCREEN_WIDTH + 250,600 }, Vect2_One * 3);
	mPinkGhostLabel = new Texture(pinkName, "emulogic.ttf", 20, { 255,183,255 });
	HandleEntityInit(mPinkGhostLabel, { (Graphics::SCREEN_WIDTH / 2) + 50,350 });

	mBlueGhost = new Texture("PacmanAtlas.png", 457, 97, 14, 14);
	HandleEntityInit(mBlueGhost, { 100,400 }, Vect2_One * 3);
	mBlueGhostAnim = new AnimatedTexture("PacmanAtlas.png", 489, 97, 16, 14, 2, 0.5f, AnimatedTexture::Horizontal);
	HandleEntityInit(mBlueGhostAnim, { Graphics::SCREEN_WIDTH + 300,600 }, Vect2_One * 3);
	mBlueGhostLabel = new Texture(blueName, "emulogic.ttf", 20, { 0,255,255 });
	HandleEntityInit(mBlueGhostLabel, { (Graphics::SCREEN_WIDTH / 2) + 50,400 });

	mOrangeGhost = new Texture("PacmanAtlas.png", 457, 113, 14, 14);
	HandleEntityInit(mOrangeGhost, { 100,450 }, Vect2_One * 3);
	mOrangeGhostAnim = new AnimatedTexture("PacmanAtlas.png", 489, 113, 16, 14, 2, 0.5f, AnimatedTexture::Horizontal);
	HandleEntityInit(mOrangeGhostAnim, { Graphics::SCREEN_WIDTH + 350,600 }, Vect2_One * 3);
	mOrangeGhostLabel = new Texture(orangeName, "emulogic.ttf", 20, { 255,183,81 });
	HandleEntityInit(mOrangeGhostLabel, { (Graphics::SCREEN_WIDTH / 2) + 50,450 });

	mFrightenedGhost1 = new AnimatedTexture("PacmanAtlas.png",584,65,16,14,2,0.5f, AnimatedTexture::Horizontal);
	HandleEntityInit(mFrightenedGhost1, Vect2_Zero, Vect2_One * 3);
	mFrightenedGhost2 = new AnimatedTexture("PacmanAtlas.png", 584, 65, 16, 14, 2, 0.5f, AnimatedTexture::Horizontal);
	HandleEntityInit(mFrightenedGhost2, Vect2_Zero, Vect2_One * 3);
	mFrightenedGhost3 = new AnimatedTexture("PacmanAtlas.png", 584, 65, 16, 14, 2, 0.5f, AnimatedTexture::Horizontal);
	HandleEntityInit(mFrightenedGhost3, Vect2_Zero, Vect2_One * 3);
	mFrightenedGhost4 = new AnimatedTexture("PacmanAtlas.png", 584, 65, 16, 14, 2, 0.5f, AnimatedTexture::Horizontal);
	HandleEntityInit(mFrightenedGhost4, Vect2_Zero, Vect2_One * 3);

	mPacmanLeft = new AnimatedTexture("PacmanAtlas.png", 455, 0, 16, 16,2,0.5f, AnimatedTexture::Horizontal);
	HandleEntityInit(mPacmanLeft, { 0,0 }, Vect2_One * 3);
	mPacmanRight = new AnimatedTexture("PacmanAtlas.png", 455, 16, 16, 16, 2, 0.5f, AnimatedTexture::Horizontal);
	HandleEntityInit(mPacmanRight, { Graphics::SCREEN_WIDTH + 100,600 }, Vect2_One * 3);

	mPowerPellet = new Texture("PacmanAtlas.png", 8, 24, 8, 8);
	HandleEntityInit(mPowerPellet, { (Graphics::SCREEN_WIDTH / 2)-50,750 }, Vect2_One * 3);
	mPowerPellet2 = new Texture("PacmanAtlas.png", 8, 24, 8, 8);
	HandleEntityInit(mPowerPellet2, { 100,600 }, Vect2_One * 3);
	mPellet = new Texture("PacmanAtlas.png", 11, 11, 2, 2);
	HandleEntityInit(mPellet, { (Graphics::SCREEN_WIDTH / 2)-50,700 }, Vect2_One * 3);

	mPowerPelletPTS = new Texture("50 PTS", "emulogic.ttf", 15, {255,255,255});
	HandleEntityInit(mPowerPelletPTS,mPowerPellet->Position()+Vector2(80,0));
	mPelletPTS = new Texture("10 PTS", "emulogic.ttf", 15, { 255,255,255 });
	HandleEntityInit(mPelletPTS, mPellet->Position() + Vector2(80, 0));

	mNamcoLabel = new Texture("NAMCO", "emulogic.ttf", 40, {255,0,0});
	HandleEntityInit(mNamcoLabel, {Graphics::SCREEN_WIDTH/2,900});

	m200pts = new Texture("pacmanAtlas.png",456,133,15,7);
	HandleEntityInit(m200pts, Vect2_Zero,Vect2_One*3);
	m400pts = new Texture("pacmanAtlas.png", 472, 133, 15, 7);
	HandleEntityInit(m400pts, Vect2_Zero, Vect2_One * 3);
	m800pts = new Texture("pacmanAtlas.png", 488, 133, 15, 7);
	HandleEntityInit(m800pts, Vect2_Zero, Vect2_One * 3);
	m1600pts = new Texture("pacmanAtlas.png", 504, 133, 16, 7);
	HandleEntityInit(m1600pts, Vect2_Zero, Vect2_One * 3);

}

StartScreen::~StartScreen() {

	mTimer = nullptr;
	mInputManager = nullptr;

	delete mOneUplabel;
	mOneUplabel = nullptr;
	delete mHighScoreLabel;
	mHighScoreLabel = nullptr;
	delete mTwoUpLabel;
	mTwoUpLabel = nullptr;

	delete mPlayerOneScoreboard;
	mPlayerOneScoreboard = nullptr;
	delete mHighScoreboard;
	mHighScoreboard = nullptr;
	delete mPlayerTwoScoreBoard;
	mPlayerTwoScoreBoard = nullptr;

	delete GhostTableLabel;
	GhostTableLabel = nullptr;

	delete mRedGhost;
	mRedGhost = nullptr;
	delete mRedGhostAnim;
	mRedGhostAnim = nullptr;
	delete mRedGhostLabel;
	mRedGhostLabel = nullptr;

	delete mPinkGhost;
	mPinkGhost = nullptr;
	delete mPinkGhostAnim;
	mPinkGhostAnim = nullptr;
	delete mPinkGhostLabel;
	mPinkGhostLabel = nullptr;

	delete mBlueGhost;
	mBlueGhost = nullptr;
	delete mBlueGhostAnim;
	mBlueGhostAnim = nullptr;
	delete mBlueGhostLabel;
	mBlueGhostLabel = nullptr;

	delete mOrangeGhost;
	mOrangeGhost = nullptr;
	delete mOrangeGhostAnim;
	mOrangeGhostAnim = nullptr;
	delete mOrangeGhostLabel;
	mOrangeGhostLabel = nullptr;

	delete mFrightenedGhost1;
	mFrightenedGhost1 = nullptr;
	delete mFrightenedGhost2;
	mFrightenedGhost2 = nullptr;
	delete mFrightenedGhost3;
	mFrightenedGhost3 = nullptr;
	delete mFrightenedGhost4;
	mFrightenedGhost4 = nullptr;

	delete mPacmanLeft;
	mPacmanLeft = nullptr;
	delete mPacmanRight;
	mPacmanRight = nullptr;

	delete mPowerPellet;
	mPowerPellet = nullptr;
	delete mPowerPellet2;
	mPowerPellet2 = nullptr;
	delete mPellet;
	mPellet = nullptr;

	delete mPowerPelletPTS;
	mPowerPelletPTS = nullptr;
	delete mPelletPTS;
	mPelletPTS = nullptr;

	delete mNamcoLabel;
	mNamcoLabel = nullptr;

	delete m200pts;
	m200pts = nullptr;
	delete m400pts;
	m400pts = nullptr;
	delete m800pts;
	m800pts = nullptr;
	delete m1600pts;
	m1600pts = nullptr;

}


void StartScreen::Update() {
	
	scrawlTime += mTimer->DeltaTime();
	mPowerPelletFlashTime += mTimer->DeltaTime();

	if (mPause) {
		mPauseTime += mTimer->DeltaTime();
		if (mPauseTime >= mPauseDurration) {
			mPause = false;
			mPauseTime = 0;
		}
	}

	if (mPowerPelletFlashTime >= mPowerPelletFlashInterval) {
		mRenderPowerPellet = !mRenderPowerPellet;
		mPowerPelletFlashTime = 0;
	}

	if (scrawlTime < 6.0f) {
		return;
	}

	if (mPause) return;

	if (mPowerPelletEaten) {

		mFrightenedGhost1->Update();
		mFrightenedGhost2->Update();
		mFrightenedGhost3->Update();
		mFrightenedGhost4->Update();

		mPacmanLeft->Update();

		mPacmanLeft->Translate(Vect2_Right * mSpeed * mTimer->DeltaTime());
		mFrightenedGhost1->Translate(Vect2_Right * mSpeed * 0.5f * mTimer->DeltaTime());
		mFrightenedGhost2->Translate(Vect2_Right * mSpeed * 0.5f * mTimer->DeltaTime());
		mFrightenedGhost3->Translate(Vect2_Right * mSpeed * 0.5f * mTimer->DeltaTime());
		mFrightenedGhost4->Translate(Vect2_Right * mSpeed * 0.5f * mTimer->DeltaTime());

		if (mPacmanLeft->Position().x >= mFrightenedGhost1->Position().x - 35.0f) {
			if (!mRedGhostEaten) {
				mRedGhostEaten = true;
				mPause = true;
			}
		}
		if (mPacmanLeft->Position().x >= mFrightenedGhost2->Position().x - 35.0f) {
			if (!mPinkGhostEaten) {
				mPinkGhostEaten = true;
				mPause = true;
			}
		}
		if (mPacmanLeft->Position().x >= mFrightenedGhost3->Position().x - 35.0f) {
			if (!mBlueGhostEaten) {
				mBlueGhostEaten = true;
				mPause = true;
			}
		}
		if (mPacmanLeft->Position().x >= mFrightenedGhost4->Position().x - 35.0f) {
			if (!mOrangeGhostEaten) {
				mOrangeGhostEaten = true;
				mPause = true;
			}
		}

	}
	else {
		if (mPacmanRight->Position().x < mPowerPellet2->Position().x + 30) {
			mPowerPelletEaten = true;
			mPacmanLeft->Position(mPacmanRight->Position());

			mFrightenedGhost1->Position(mRedGhostAnim->Position());
			mFrightenedGhost2->Position(mPinkGhostAnim->Position());
			mFrightenedGhost3->Position(mBlueGhostAnim->Position());
			mFrightenedGhost4->Position(mOrangeGhostAnim->Position());

		}

		mPacmanRight->Translate(-Vect2_Right * mSpeed * mTimer->DeltaTime());
		mRedGhostAnim->Translate(-Vect2_Right * mSpeed * mTimer->DeltaTime());
		mPinkGhostAnim->Translate(-Vect2_Right * mSpeed * mTimer->DeltaTime());
		mBlueGhostAnim->Translate(-Vect2_Right * mSpeed * mTimer->DeltaTime());
		mOrangeGhostAnim->Translate(-Vect2_Right * mSpeed * mTimer->DeltaTime());

		mRedGhostAnim->Update();
		mPinkGhostAnim->Update();
		mBlueGhostAnim->Update();
		mOrangeGhostAnim->Update();

		mPacmanRight->Update();
	}
	

	

	
	

}

void StartScreen::Render() {
	if (scrawlTime >= 6.0f) {
		if (mPowerPelletEaten) {
			if (!mRedGhostEaten) {
				mFrightenedGhost1->Render();
			}
			if (!mPinkGhostEaten) {
				mFrightenedGhost2->Render();
			}
			if (!mBlueGhostEaten) {
				mFrightenedGhost3->Render();
			}
			if (!mOrangeGhostEaten) {
				mFrightenedGhost4->Render();
			}
			mPacmanLeft->Render();
		}
		else {
			mRedGhostAnim->Render();
			mPinkGhostAnim->Render();
			mBlueGhostAnim->Render();
			mOrangeGhostAnim->Render();
			mPacmanRight->Render();
			if(mRenderPowerPellet) mPowerPellet2->Render();
		}
	}
	

	mOneUplabel->Render();
	mHighScoreLabel->Render();
	mTwoUpLabel->Render();

	mPlayerOneScoreboard->Render();
	mHighScoreboard->Render();
	mPlayerTwoScoreBoard->Render();

	GhostTableLabel->Render();

	if (scrawlTime >= 1.0f) mRedGhost->Render();
	if (scrawlTime >= 1.5f) mRedGhostLabel->Render();

	if (scrawlTime >= 2.0f) mPinkGhost->Render();
	if (scrawlTime >= 2.5f) mPinkGhostLabel->Render();

	if (scrawlTime >= 3.0f) mBlueGhost->Render();
	if (scrawlTime >= 3.5f) mBlueGhostLabel->Render();

	if (scrawlTime >= 4.0f) mOrangeGhost->Render();
	if (scrawlTime >= 4.5f) mOrangeGhostLabel->Render();
	
	if (scrawlTime >= 5.0f) {
		if (mRenderPowerPellet) mPowerPellet->Render();
		mPellet->Render();

		mPowerPelletPTS->Render();
		mPelletPTS->Render();

		mNamcoLabel->Render();
	}
	
	if (mPause) {
		if (mOrangeGhostEaten) {
			m1600pts->Position(mFrightenedGhost4->Position());
			m1600pts->Render();
		}
		else if (mBlueGhostEaten) {
			m800pts->Position(mFrightenedGhost3->Position());
			m800pts->Render();
		}
		else if (mPinkGhostEaten) {
			m400pts->Position(mFrightenedGhost2->Position());
			m400pts->Render();
		}
		else if (mRedGhostEaten) {
			m200pts->Position(mFrightenedGhost1->Position());
			m200pts->Render();
		}
	}

}

void StartScreen::ResetAnimation() {
	mPowerPelletEaten = false;
	mRedGhostEaten = false;
	mPinkGhostEaten = false;
	mBlueGhostEaten = false;
	mOrangeGhostEaten = false;
	mPowerPelletFlashTime = 0;
	mRenderPowerPellet = true;
	scrawlTime = 0;
	mPauseTime = 0;
	mPause = false;

	mRedGhostAnim->Position({ Graphics::SCREEN_WIDTH + 200,600 });
	mPinkGhostAnim->Position({ Graphics::SCREEN_WIDTH + 250,600 });
	mBlueGhostAnim->Position({ Graphics::SCREEN_WIDTH + 300,600 });
	mOrangeGhostAnim->Position({ Graphics::SCREEN_WIDTH + 350,600 });

	mPacmanRight->Position({ Graphics::SCREEN_WIDTH + 100,600 });


}

void StartScreen::HandleEntityInit(GameEntity* tex, Vector2 pos, Vector2 scale) {
	
	tex->Parent(this);
	tex->Position(pos);
	tex->Scale(scale);

}