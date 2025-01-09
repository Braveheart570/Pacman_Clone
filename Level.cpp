#include "Level.h"

Level::Level() {
	mTimer = Timer::Instance();
	mNodeManager = NodeManager::Instance();
	mAudioManager = AudioManager::Instance();
	CreatePellets();
	mPlayer = Player::Instance();

	mFruitIndex = 0;
	mNumOfFruitSpawned = 0;
	mFruit = new Fruit(mFruitIndex);


	mStageStarted = false;
	mReadyDuration = 5.0f;
	mReadyTime = 0;

	mLevelNum = 1;
	mGameOver = false;

	mLivesGiven = 0;

	mPinkGhostReleaseDelay = 5.0f;

	mLevelBackground = new Texture("PacmanAtlas.png",227,0,225,248);
	mLevelBackground->Parent(this);
	mLevelBackground->Scale(Vect2_One * ((Graphics::SCREEN_WIDTH / 225.0f)-0.2f));
	mLevelBackground->Position(Vect2_Zero);

	mRedGhost = new RedGhost(mNodeManager->getNode(66));
	mPinkGhost = new PinkGhost(mNodeManager->getNode(67));
	mBlueGhost = new BlueGhost(mNodeManager->getNode(69),mRedGhost);
	mOrangeGhost = new OrangeGhost(mNodeManager->getNode(68));
	
	mScoreboard = new Scoreboard();
	mScoreboard->Parent(this);
	mScoreboard->Position(-200.0f, -400.0f);
	mScoreboard->Score(mPlayer->Score());

	mHighScoreboard = new Scoreboard();
	mHighScoreboard->Parent(this);
	mHighScoreboard->Position(0,-400.0f);
	mHighScoreboard->Score(mPlayer->HighScore());

	mHighScoreLabel = new Texture("High Score", "emulogic.ttf", 25, {255,255,255});
	mHighScoreLabel->Parent(this);
	mHighScoreLabel->Position(0,-435.0f);

	mScoreLabel = new Texture("1UP", "emulogic.ttf", 25, {255,255,255});
	mScoreLabel->Parent(this);
	mScoreLabel->Position(-250.0f, -435.0f);

	mReadyLabel = new Texture("Ready!", "emulogic.ttf", 20, {255,255,0});
	mReadyLabel->Parent(this);
	mReadyLabel->Position(Vect2_Zero + Vector2{ 0,50 });

	mGameOverLabel = new Texture("Game Over", "emulogic.ttf", 20, { 255,0,0 });
	mGameOverLabel->Parent(this);
	mGameOverLabel->Position(Vect2_Zero + Vector2{ 0,50 });

	Position(Graphics::SCREEN_WIDTH/2,Graphics::SCREEN_HEIGHT/2);//call this last
}

Level::~Level() {

	mTimer = nullptr;
	mPlayer = nullptr;
	mNodeManager = nullptr;
	mAudioManager = nullptr;


	delete mLevelBackground;
	mLevelBackground = nullptr;

	delete mRedGhost;
	mRedGhost = nullptr;
	delete mPinkGhost;
	mPinkGhost = nullptr;
	delete mBlueGhost;
	mBlueGhost = nullptr;
	delete mOrangeGhost;
	mOrangeGhost = nullptr;

	delete mHighScoreboard;
	mHighScoreboard = nullptr;
	delete mScoreboard;
	mScoreboard = nullptr;

	delete mHighScoreLabel;
	mHighScoreLabel = nullptr;
	delete mScoreLabel;
	mScoreLabel = nullptr;

	delete mReadyLabel;
	mReadyLabel = nullptr;

	delete mGameOverLabel;
	mGameOverLabel = nullptr;

	for (auto l : mPlayerLives) {
		delete l;
		l = nullptr;
	}

	for (auto p : mPellets) {
		delete p;
		p = nullptr;
	}

	delete mFruit;
	mFruit = nullptr;
	
}

void Level::Update() {

	if (mGameOver) return;

	//debug keys
	if (InputManager::Instance()->KeyPressed(SDL_SCANCODE_E)) {
		if (mRedGhost->RageState() == mRedGhost->Unenraged) {
			mRedGhost->RageState(mRedGhost->Enraged1);
		}
		else if (mRedGhost->RageState() == mRedGhost->Enraged1) {
			mRedGhost->RageState(mRedGhost->Enraged2);
		}
		else if (mRedGhost->RageState() == mRedGhost->Enraged2) {
			mRedGhost->RageState(mRedGhost->Unenraged);
		}
	}
	if(InputManager::Instance()->KeyPressed(SDL_SCANCODE_M)){
		resetLevel(true);
	}


	// pause before game start logic
	if (!mStageStarted) {
		mReadyTime += mTimer->DeltaTime();
		if (mReadyTime >= mReadyDuration) {
			mStageStarted = true;
			if (mRedGhost->RageState() == RedGhost::Enraged2) {
				mAudioManager->PlayMusic("siren2.wav");
			}
			else {
				mAudioManager->PlayMusic("siren1.wav");
			}
		}
		return; 
	}
	//--- nothing beyond this line will run untill the game has started! ---//


	//check beat level
	bool allPelletsEaten = true;
	for (auto pellet : mPellets) {
		if (pellet->Active()) {
			allPelletsEaten = false;
			break;
		}
	}
	if(allPelletsEaten) resetLevel(true);




	//check release pink ghost
	if (mPinkGhost->HouseState() == Ghost::Housed) {
		mPinkGhostReleaseTime += mTimer->DeltaTime();
		if (mPinkGhostReleaseTime >= mPinkGhostReleaseDelay) {
			mPinkGhost->Unhouse();
		}
	}

	//check release blue ghost
	if (mBlueGhost->HouseState() == Ghost::Housed && mPlayer->PelletsEaten() >= 30) {
		mBlueGhost->Unhouse();
	}

	//check release orange ghost
	if (mOrangeGhost->HouseState() == Ghost::Housed && mPlayer->PelletsEaten() >= mPellets.size()/3) {
		mOrangeGhost->Unhouse();
	}


	// death check
	if (mPlayer->isDead()) {
		resetLevel();
		return;
	}

	// gaining extra lives
	if (mPlayer->Score() >= 10000 + (10000 * mLivesGiven)) {
		mPlayer->addLife();
		mAudioManager->PlaySFX("extraLife.wav");
		setLifeIcons();
		mLivesGiven++;
	}

	//fruit spawning
	if (mPlayer->PelletsEaten() >= 70 && mNumOfFruitSpawned == 0 && mFruit->Active() == false) {
		mFruit->Active(true);
		mNumOfFruitSpawned++;
	}
	else if (mPlayer->PelletsEaten() >= 170 && mNumOfFruitSpawned == 1 && mFruit->Active() == false) {
		mFruit->Active(true);
		mNumOfFruitSpawned++;
	}

	// Red Ghost Enrage
	if (mRedGhost->RageState() == RedGhost::Unenraged && mPlayer->PelletsEaten() >= mPellets.size() / 2) {
		mRedGhost->RageState(RedGhost::Enraged1);
	}
	if (mRedGhost->RageState() != RedGhost::Enraged2 && mPlayer->PelletsEaten() >= (mPellets.size() / 4)*3) {
		mRedGhost->RageState(RedGhost::Enraged2);
	}
	
	// general updates
	mPlayer->Update();
	if (!mPlayer->IsDying() && !mPlayer->isDead()) {
		mRedGhost->Update();
		mPinkGhost->Update();
		mBlueGhost->Update();
		mOrangeGhost->Update();
	}
	ScoreBubble::Instance()->Update();
	mScoreboard->Score(mPlayer->Score());
	if (mPlayer->Score() >= mPlayer->HighScore()) mHighScoreboard->Score(mPlayer->Score());
	mFruit->Update();

}

void Level::Render() {

	mLevelBackground->Render();
	mNodeManager->Render();

	if (!mGameOver) {
		for (auto p : mPellets) {
			p->Render();
		}

		mFruit->Render();

	}
	
	mPlayer->Render();
	if (!mPlayer->IsDying() && !mPlayer->isDead() && !mGameOver) {
		mRedGhost->Render();
		mPinkGhost->Render();
		mBlueGhost->Render();
		mOrangeGhost->Render();
	}
	

	for (auto l : mPlayerLives) {
		l->Render();
	}


	mHighScoreboard->Render();
	mScoreboard->Render();

	mHighScoreLabel->Render();
	mScoreLabel->Render();


	if (!mStageStarted && !mGameOver) {
		mReadyLabel->Render();
	}
	
	if (mGameOver) {
		mGameOverLabel->Render();
	}

	ScoreBubble::Instance()->Render();

}

void Level::CreatePellets() {

	mRows[0] = Graphics::SCREEN_HEIGHT * 0.16f;
	mRows[1] = Graphics::SCREEN_HEIGHT * 0.26f;
	mRows[2] = Graphics::SCREEN_HEIGHT * 0.33f;
	mRows[3] = Graphics::SCREEN_HEIGHT * 0.4f;
	mRows[4] = Graphics::SCREEN_HEIGHT * 0.475f;
	mRows[5] = Graphics::SCREEN_HEIGHT * 0.55f;
	mRows[6] = Graphics::SCREEN_HEIGHT * 0.62f;
	mRows[7] = Graphics::SCREEN_HEIGHT * 0.69f;
	mRows[8] = Graphics::SCREEN_HEIGHT * 0.765f;
	mRows[9] = Graphics::SCREEN_HEIGHT * 0.84f;

	mCols[0] = Graphics::SCREEN_WIDTH * 0.1f;
	mCols[1] = Graphics::SCREEN_WIDTH * 0.255f;
	mCols[2] = Graphics::SCREEN_WIDTH * 0.35f;
	mCols[3] = Graphics::SCREEN_WIDTH * 0.45f;
	mCols[4] = Graphics::SCREEN_WIDTH * 0.555f;
	mCols[5] = Graphics::SCREEN_WIDTH * 0.65f;
	mCols[6] = Graphics::SCREEN_WIDTH * 0.75f;
	mCols[7] = Graphics::SCREEN_WIDTH * 0.915f;

	//rows
	mPellets.push_back(new Pellet({ mCols[0], mRows[0] }));
	mPellets.push_back(new Pellet({ mCols[0] + ((mCols[1] - mCols[0]) / 5), mRows[0] }));
	mPellets.push_back(new Pellet({ mCols[0] + ((mCols[1] - mCols[0]) / 5) * 2, mRows[0] }));
	mPellets.push_back(new Pellet({ mCols[0] + ((mCols[1] - mCols[0]) / 5) * 3, mRows[0] }));
	mPellets.push_back(new Pellet({ mCols[0] + ((mCols[1] - mCols[0]) / 5) * 4, mRows[0] }));
	mPellets.push_back(new Pellet({ mCols[1], mRows[0] }));

	mPellets.push_back(new Pellet({ mCols[1], mRows[0] }));
	mPellets.push_back(new Pellet({ mCols[1] + ((mCols[3] - mCols[1]) / 6), mRows[0] }));
	mPellets.push_back(new Pellet({ mCols[1] + ((mCols[3] - mCols[1]) / 6) * 2, mRows[0] }));
	mPellets.push_back(new Pellet({ mCols[1] + ((mCols[3] - mCols[1]) / 6) * 3, mRows[0] }));
	mPellets.push_back(new Pellet({ mCols[1] + ((mCols[3] - mCols[1]) / 6) * 4, mRows[0] }));
	mPellets.push_back(new Pellet({ mCols[1] + ((mCols[3] - mCols[1]) / 6) * 5, mRows[0] }));
	mPellets.push_back(new Pellet({ mCols[3], mRows[0] }));

	mPellets.push_back(new Pellet({ mCols[4], mRows[0] }));
	mPellets.push_back(new Pellet({ mCols[4] + ((mCols[6] - mCols[4]) / 6), mRows[0] }));
	mPellets.push_back(new Pellet({ mCols[4] + ((mCols[6] - mCols[4]) / 6) * 2, mRows[0] }));
	mPellets.push_back(new Pellet({ mCols[4] + ((mCols[6] - mCols[4]) / 6) * 3, mRows[0] }));
	mPellets.push_back(new Pellet({ mCols[4] + ((mCols[6] - mCols[4]) / 6) * 4, mRows[0] }));
	mPellets.push_back(new Pellet({ mCols[4] + ((mCols[6] - mCols[4]) / 6) * 5, mRows[0] }));
	mPellets.push_back(new Pellet({ mCols[6], mRows[0] }));

	mPellets.push_back(new Pellet({ mCols[6], mRows[0] }));
	mPellets.push_back(new Pellet({ mCols[6] + ((mCols[7] - mCols[6]) / 5), mRows[0] }));
	mPellets.push_back(new Pellet({ mCols[6] + ((mCols[7] - mCols[6]) / 5) * 2, mRows[0] }));
	mPellets.push_back(new Pellet({ mCols[6] + ((mCols[7] - mCols[6]) / 5) * 3, mRows[0] }));
	mPellets.push_back(new Pellet({ mCols[6] + ((mCols[7] - mCols[6]) / 5) * 4, mRows[0] }));
	mPellets.push_back(new Pellet({ mCols[7], mRows[0] }));



	mPellets.push_back(new Pellet({ mCols[0], mRows[1] }));
	mPellets.push_back(new Pellet({ mCols[0] + ((mCols[1] - mCols[0]) / 5), mRows[1] }));
	mPellets.push_back(new Pellet({ mCols[0] + ((mCols[1] - mCols[0]) / 5) * 2, mRows[1] }));
	mPellets.push_back(new Pellet({ mCols[0] + ((mCols[1] - mCols[0]) / 5) * 3, mRows[1] }));
	mPellets.push_back(new Pellet({ mCols[0] + ((mCols[1] - mCols[0]) / 5) * 4, mRows[1] }));
	mPellets.push_back(new Pellet({ mCols[1], mRows[1] }));

	mPellets.push_back(new Pellet({ mCols[1], mRows[1] }));
	mPellets.push_back(new Pellet({ mCols[1] + ((mCols[3] - mCols[1]) / 6), mRows[1] }));
	mPellets.push_back(new Pellet({ mCols[1] + ((mCols[3] - mCols[1]) / 6) * 2, mRows[1] }));
	mPellets.push_back(new Pellet({ mCols[1] + ((mCols[3] - mCols[1]) / 6) * 3, mRows[1] }));
	mPellets.push_back(new Pellet({ mCols[1] + ((mCols[3] - mCols[1]) / 6) * 4, mRows[1] }));
	mPellets.push_back(new Pellet({ mCols[1] + ((mCols[3] - mCols[1]) / 6) * 5, mRows[1] }));
	mPellets.push_back(new Pellet({ mCols[3], mRows[1] }));

	mPellets.push_back(new Pellet({ mCols[3] + ((mCols[4] - mCols[3]) / 3), mRows[1] }));
	mPellets.push_back(new Pellet({ mCols[3] + ((mCols[4] - mCols[3]) / 3)*2, mRows[1] }));

	mPellets.push_back(new Pellet({ mCols[4], mRows[1] }));
	mPellets.push_back(new Pellet({ mCols[4] + ((mCols[6] - mCols[4]) / 6), mRows[1] }));
	mPellets.push_back(new Pellet({ mCols[4] + ((mCols[6] - mCols[4]) / 6) * 2, mRows[1] }));
	mPellets.push_back(new Pellet({ mCols[4] + ((mCols[6] - mCols[4]) / 6) * 3, mRows[1] }));
	mPellets.push_back(new Pellet({ mCols[4] + ((mCols[6] - mCols[4]) / 6) * 4, mRows[1] }));
	mPellets.push_back(new Pellet({ mCols[4] + ((mCols[6] - mCols[4]) / 6) * 5, mRows[1] }));
	mPellets.push_back(new Pellet({ mCols[6], mRows[1] }));

	mPellets.push_back(new Pellet({ mCols[6], mRows[1] }));
	mPellets.push_back(new Pellet({ mCols[6] + ((mCols[7] - mCols[6]) / 5), mRows[1] }));
	mPellets.push_back(new Pellet({ mCols[6] + ((mCols[7] - mCols[6]) / 5) * 2, mRows[1] }));
	mPellets.push_back(new Pellet({ mCols[6] + ((mCols[7] - mCols[6]) / 5) * 3, mRows[1] }));
	mPellets.push_back(new Pellet({ mCols[6] + ((mCols[7] - mCols[6]) / 5) * 4, mRows[1] }));
	mPellets.push_back(new Pellet({ mCols[7], mRows[1] }));



	mPellets.push_back(new Pellet({ mCols[0], mRows[2] }));
	mPellets.push_back(new Pellet({ mCols[0] + ((mCols[1] - mCols[0]) / 5), mRows[2] }));
	mPellets.push_back(new Pellet({ mCols[0] + ((mCols[1] - mCols[0]) / 5) * 2, mRows[2] }));
	mPellets.push_back(new Pellet({ mCols[0] + ((mCols[1] - mCols[0]) / 5) * 3, mRows[2] }));
	mPellets.push_back(new Pellet({ mCols[0] + ((mCols[1] - mCols[0]) / 5) * 4, mRows[2] }));
	mPellets.push_back(new Pellet({ mCols[1], mRows[2] }));

	mPellets.push_back(new Pellet({ mCols[1] + ((mCols[3] - mCols[1]) / 6) * 3, mRows[2] }));
	mPellets.push_back(new Pellet({ mCols[1] + ((mCols[3] - mCols[1]) / 6) * 4, mRows[2] }));
	mPellets.push_back(new Pellet({ mCols[1] + ((mCols[3] - mCols[1]) / 6) * 5, mRows[2] }));
	mPellets.push_back(new Pellet({ mCols[3], mRows[2] }));

	mPellets.push_back(new Pellet({ mCols[4], mRows[2] }));
	mPellets.push_back(new Pellet({ mCols[4] + ((mCols[6] - mCols[4]) / 6), mRows[2] }));
	mPellets.push_back(new Pellet({ mCols[4] + ((mCols[6] - mCols[4]) / 6) * 2, mRows[2] }));
	mPellets.push_back(new Pellet({ mCols[4] + ((mCols[6] - mCols[4]) / 6) * 3, mRows[2] }));

	mPellets.push_back(new Pellet({ mCols[6], mRows[2] }));
	mPellets.push_back(new Pellet({ mCols[6] + ((mCols[7] - mCols[6]) / 5), mRows[2] }));
	mPellets.push_back(new Pellet({ mCols[6] + ((mCols[7] - mCols[6]) / 5) * 2, mRows[2] }));
	mPellets.push_back(new Pellet({ mCols[6] + ((mCols[7] - mCols[6]) / 5) * 3, mRows[2] }));
	mPellets.push_back(new Pellet({ mCols[6] + ((mCols[7] - mCols[6]) / 5) * 4, mRows[2] }));
	mPellets.push_back(new Pellet({ mCols[7], mRows[2] }));



	mPellets.push_back(new Pellet({ mCols[1], mRows[3] }));
	mPellets.push_back(new Pellet({ mCols[6], mRows[3] }));



	mPellets.push_back(new Pellet({ mCols[1], mRows[4] }));
	mPellets.push_back(new Pellet({ mCols[6], mRows[4] }));



	mPellets.push_back(new Pellet({ mCols[1], mRows[5] }));
	mPellets.push_back(new Pellet({ mCols[6], mRows[5] }));



	mPellets.push_back(new Pellet({ mCols[0], mRows[6] }));
	mPellets.push_back(new Pellet({ mCols[0] + ((mCols[1] - mCols[0]) / 5), mRows[6] }));
	mPellets.push_back(new Pellet({ mCols[0] + ((mCols[1] - mCols[0]) / 5) * 2, mRows[6] }));
	mPellets.push_back(new Pellet({ mCols[0] + ((mCols[1] - mCols[0]) / 5) * 3, mRows[6] }));
	mPellets.push_back(new Pellet({ mCols[0] + ((mCols[1] - mCols[0]) / 5) * 4, mRows[6] }));
	mPellets.push_back(new Pellet({ mCols[1], mRows[6] }));

	mPellets.push_back(new Pellet({ mCols[1], mRows[6] }));
	mPellets.push_back(new Pellet({ mCols[1] + ((mCols[3] - mCols[1]) / 6), mRows[6] }));
	mPellets.push_back(new Pellet({ mCols[1] + ((mCols[3] - mCols[1]) / 6) * 2, mRows[6] }));
	mPellets.push_back(new Pellet({ mCols[1] + ((mCols[3] - mCols[1]) / 6) * 3, mRows[6] }));
	mPellets.push_back(new Pellet({ mCols[1] + ((mCols[3] - mCols[1]) / 6) * 4, mRows[6] }));
	mPellets.push_back(new Pellet({ mCols[1] + ((mCols[3] - mCols[1]) / 6) * 5, mRows[6] }));
	mPellets.push_back(new Pellet({ mCols[3], mRows[6] }));

	mPellets.push_back(new Pellet({ mCols[4], mRows[6] }));
	mPellets.push_back(new Pellet({ mCols[4] + ((mCols[6] - mCols[4]) / 6), mRows[6] }));
	mPellets.push_back(new Pellet({ mCols[4] + ((mCols[6] - mCols[4]) / 6) * 2, mRows[6] }));
	mPellets.push_back(new Pellet({ mCols[4] + ((mCols[6] - mCols[4]) / 6) * 3, mRows[6] }));
	mPellets.push_back(new Pellet({ mCols[4] + ((mCols[6] - mCols[4]) / 6) * 4, mRows[6] }));
	mPellets.push_back(new Pellet({ mCols[4] + ((mCols[6] - mCols[4]) / 6) * 5, mRows[6] }));
	mPellets.push_back(new Pellet({ mCols[6], mRows[6] }));

	mPellets.push_back(new Pellet({ mCols[6], mRows[6] }));
	mPellets.push_back(new Pellet({ mCols[6] + ((mCols[7] - mCols[6]) / 5), mRows[6] }));
	mPellets.push_back(new Pellet({ mCols[6] + ((mCols[7] - mCols[6]) / 5) * 2, mRows[6] }));
	mPellets.push_back(new Pellet({ mCols[6] + ((mCols[7] - mCols[6]) / 5) * 3, mRows[6] }));
	mPellets.push_back(new Pellet({ mCols[6] + ((mCols[7] - mCols[6]) / 5) * 4, mRows[6] }));
	mPellets.push_back(new Pellet({ mCols[7], mRows[6] }));



	mPellets.push_back(new PowerPellet({ mCols[0], mRows[7] }));
	mPellets.push_back(new Pellet({ mCols[0] + ((mCols[1] - mCols[0]) / 5), mRows[7] }));
	mPellets.push_back(new Pellet({ mCols[0] + ((mCols[1] - mCols[0]) / 5) * 2, mRows[7] }));

	mPellets.push_back(new Pellet({ mCols[1], mRows[7] }));

	mPellets.push_back(new Pellet({ mCols[1], mRows[7] }));
	mPellets.push_back(new Pellet({ mCols[1] + ((mCols[3] - mCols[1]) / 6), mRows[7] }));
	mPellets.push_back(new Pellet({ mCols[1] + ((mCols[3] - mCols[1]) / 6) * 2, mRows[7] }));
	mPellets.push_back(new Pellet({ mCols[1] + ((mCols[3] - mCols[1]) / 6) * 3, mRows[7] }));
	mPellets.push_back(new Pellet({ mCols[1] + ((mCols[3] - mCols[1]) / 6) * 4, mRows[7] }));
	mPellets.push_back(new Pellet({ mCols[1] + ((mCols[3] - mCols[1]) / 6) * 5, mRows[7] }));
	mPellets.push_back(new Pellet({ mCols[3], mRows[7] }));

	mPellets.push_back(new Pellet({ mCols[3] + ((mCols[4] - mCols[3]) / 3), mRows[7] }));
	mPellets.push_back(new Pellet({ mCols[3] + ((mCols[4] - mCols[3]) / 3) * 2, mRows[7] }));

	mPellets.push_back(new Pellet({ mCols[4], mRows[7] }));
	mPellets.push_back(new Pellet({ mCols[4] + ((mCols[6] - mCols[4]) / 6), mRows[7] }));
	mPellets.push_back(new Pellet({ mCols[4] + ((mCols[6] - mCols[4]) / 6) * 2, mRows[7] }));
	mPellets.push_back(new Pellet({ mCols[4] + ((mCols[6] - mCols[4]) / 6) * 3, mRows[7] }));
	mPellets.push_back(new Pellet({ mCols[4] + ((mCols[6] - mCols[4]) / 6) * 4, mRows[7] }));
	mPellets.push_back(new Pellet({ mCols[4] + ((mCols[6] - mCols[4]) / 6) * 5, mRows[7] }));
	mPellets.push_back(new Pellet({ mCols[6], mRows[7] }));

	mPellets.push_back(new Pellet({ mCols[6], mRows[7] }));

	mPellets.push_back(new Pellet({ mCols[6] + ((mCols[7] - mCols[6]) / 5) * 3, mRows[7] }));
	mPellets.push_back(new Pellet({ mCols[6] + ((mCols[7] - mCols[6]) / 5) * 4, mRows[7] }));
	mPellets.push_back(new PowerPellet({ mCols[7], mRows[7] }));



	mPellets.push_back(new Pellet({ mCols[0], mRows[8] }));
	mPellets.push_back(new Pellet({ mCols[0] + ((mCols[1] - mCols[0]) / 5), mRows[8] }));
	mPellets.push_back(new Pellet({ mCols[0] + ((mCols[1] - mCols[0]) / 5) * 2, mRows[8] }));
	mPellets.push_back(new Pellet({ mCols[0] + ((mCols[1] - mCols[0]) / 5) * 3, mRows[8] }));
	mPellets.push_back(new Pellet({ mCols[0] + ((mCols[1] - mCols[0]) / 5) * 4, mRows[8] }));
	mPellets.push_back(new Pellet({ mCols[1], mRows[8] }));

	mPellets.push_back(new Pellet({ mCols[1] + ((mCols[3] - mCols[1]) / 6) * 3, mRows[8] }));
	mPellets.push_back(new Pellet({ mCols[1] + ((mCols[3] - mCols[1]) / 6) * 4, mRows[8] }));
	mPellets.push_back(new Pellet({ mCols[1] + ((mCols[3] - mCols[1]) / 6) * 5, mRows[8] }));
	mPellets.push_back(new Pellet({ mCols[3], mRows[8] }));

	mPellets.push_back(new Pellet({ mCols[4], mRows[8] }));
	mPellets.push_back(new Pellet({ mCols[4] + ((mCols[6] - mCols[4]) / 6), mRows[8] }));
	mPellets.push_back(new Pellet({ mCols[4] + ((mCols[6] - mCols[4]) / 6) * 2, mRows[8] }));
	mPellets.push_back(new Pellet({ mCols[4] + ((mCols[6] - mCols[4]) / 6) * 3, mRows[8] }));

	mPellets.push_back(new Pellet({ mCols[6], mRows[8] }));
	mPellets.push_back(new Pellet({ mCols[6] + ((mCols[7] - mCols[6]) / 5), mRows[8] }));
	mPellets.push_back(new Pellet({ mCols[6] + ((mCols[7] - mCols[6]) / 5) * 2, mRows[8] }));
	mPellets.push_back(new Pellet({ mCols[6] + ((mCols[7] - mCols[6]) / 5) * 3, mRows[8] }));
	mPellets.push_back(new Pellet({ mCols[6] + ((mCols[7] - mCols[6]) / 5) * 4, mRows[8] }));
	mPellets.push_back(new Pellet({ mCols[7], mRows[8] }));



	mPellets.push_back(new Pellet({ mCols[0], mRows[9] }));
	mPellets.push_back(new Pellet({ mCols[0] + ((mCols[1] - mCols[0]) / 5), mRows[9] }));
	mPellets.push_back(new Pellet({ mCols[0] + ((mCols[1] - mCols[0]) / 5) * 2, mRows[9] }));
	mPellets.push_back(new Pellet({ mCols[0] + ((mCols[1] - mCols[0]) / 5) * 3, mRows[9] }));
	mPellets.push_back(new Pellet({ mCols[0] + ((mCols[1] - mCols[0]) / 5) * 4, mRows[9] }));
	mPellets.push_back(new Pellet({ mCols[1], mRows[9] }));

	mPellets.push_back(new Pellet({ mCols[1], mRows[9] }));
	mPellets.push_back(new Pellet({ mCols[1] + ((mCols[3] - mCols[1]) / 6), mRows[9] }));
	mPellets.push_back(new Pellet({ mCols[1] + ((mCols[3] - mCols[1]) / 6) * 2, mRows[9] }));
	mPellets.push_back(new Pellet({ mCols[1] + ((mCols[3] - mCols[1]) / 6) * 3, mRows[9] }));
	mPellets.push_back(new Pellet({ mCols[1] + ((mCols[3] - mCols[1]) / 6) * 4, mRows[9] }));
	mPellets.push_back(new Pellet({ mCols[1] + ((mCols[3] - mCols[1]) / 6) * 5, mRows[9] }));
	mPellets.push_back(new Pellet({ mCols[3], mRows[9] }));

	mPellets.push_back(new Pellet({ mCols[3] + ((mCols[4] - mCols[3]) / 3), mRows[9] }));
	mPellets.push_back(new Pellet({ mCols[3] + ((mCols[4] - mCols[3]) / 3) * 2, mRows[9] }));

	mPellets.push_back(new Pellet({ mCols[4], mRows[9] }));
	mPellets.push_back(new Pellet({ mCols[4] + ((mCols[6] - mCols[4]) / 6), mRows[9] }));
	mPellets.push_back(new Pellet({ mCols[4] + ((mCols[6] - mCols[4]) / 6) * 2, mRows[9] }));
	mPellets.push_back(new Pellet({ mCols[4] + ((mCols[6] - mCols[4]) / 6) * 3, mRows[9] }));
	mPellets.push_back(new Pellet({ mCols[4] + ((mCols[6] - mCols[4]) / 6) * 4, mRows[9] }));
	mPellets.push_back(new Pellet({ mCols[4] + ((mCols[6] - mCols[4]) / 6) * 5, mRows[9] }));
	mPellets.push_back(new Pellet({ mCols[6], mRows[9] }));

	mPellets.push_back(new Pellet({ mCols[6], mRows[9] }));
	mPellets.push_back(new Pellet({ mCols[6] + ((mCols[7] - mCols[6]) / 5), mRows[9] }));
	mPellets.push_back(new Pellet({ mCols[6] + ((mCols[7] - mCols[6]) / 5) * 2, mRows[9] }));
	mPellets.push_back(new Pellet({ mCols[6] + ((mCols[7] - mCols[6]) / 5) * 3, mRows[9] }));
	mPellets.push_back(new Pellet({ mCols[6] + ((mCols[7] - mCols[6]) / 5) * 4, mRows[9] }));
	mPellets.push_back(new Pellet({ mCols[7], mRows[9] }));



	//cols
	mPellets.push_back(new Pellet({ mCols[0], mRows[0] + ((mRows[1] - mRows[0]) / 3) }));
	mPellets.push_back(new PowerPellet({ mCols[0], mRows[0] + ((mRows[1] - mRows[0]) / 3)*2 }));

	mPellets.push_back(new Pellet({ mCols[1], mRows[0] + ((mRows[1] - mRows[0]) / 3) }));
	mPellets.push_back(new Pellet({ mCols[1], mRows[0] + ((mRows[1] - mRows[0]) / 3) * 2 }));

	mPellets.push_back(new Pellet({ mCols[3], mRows[0] + ((mRows[1] - mRows[0]) / 3) }));
	mPellets.push_back(new Pellet({ mCols[3], mRows[0] + ((mRows[1] - mRows[0]) / 3) * 2 }));

	mPellets.push_back(new Pellet({ mCols[4], mRows[0] + ((mRows[1] - mRows[0]) / 3) }));
	mPellets.push_back(new Pellet({ mCols[4], mRows[0] + ((mRows[1] - mRows[0]) / 3) * 2 }));

	mPellets.push_back(new Pellet({ mCols[6], mRows[0] + ((mRows[1] - mRows[0]) / 3) }));
	mPellets.push_back(new Pellet({ mCols[6], mRows[0] + ((mRows[1] - mRows[0]) / 3) * 2 }));

	mPellets.push_back(new Pellet({ mCols[7], mRows[0] + ((mRows[1] - mRows[0]) / 3) }));
	mPellets.push_back(new PowerPellet({ mCols[7], mRows[0] + ((mRows[1] - mRows[0]) / 3) * 2 }));



	mPellets.push_back(new Pellet({ mCols[0], mRows[1] + ((mRows[2] - mRows[1]) / 3) }));
	mPellets.push_back(new Pellet({ mCols[0], mRows[1] + ((mRows[2] - mRows[1]) / 3) * 2 }));

	mPellets.push_back(new Pellet({ mCols[1], mRows[1] + ((mRows[2] - mRows[1]) / 3) }));
	mPellets.push_back(new Pellet({ mCols[1], mRows[1] + ((mRows[2] - mRows[1]) / 3) * 2 }));
	//the bellow 4 are being weird, has to do with how we are defining the rows (corrected)
	mPellets.push_back(new Pellet({ mCols[1] + ((mCols[3] - mCols[1]) / 6) * 3, mRows[1] + ((mRows[2] - mRows[1]) / 3) }));
	mPellets.push_back(new Pellet({ mCols[1] + ((mCols[3] - mCols[1]) / 6) * 3, mRows[1] + ((mRows[2] - mRows[1]) / 3) * 2 }));

	mPellets.push_back(new Pellet({ mCols[4] + ((mCols[6] - mCols[4]) / 6) * 3, mRows[1] + ((mRows[2] - mRows[1]) / 3)}));
	mPellets.push_back(new Pellet({ mCols[4] + ((mCols[6] - mCols[4]) / 6) * 3, mRows[1] + ((mRows[2] - mRows[1]) / 3) * 2 }));

	mPellets.push_back(new Pellet({ mCols[6], mRows[1] + ((mRows[2] - mRows[1]) / 3) }));
	mPellets.push_back(new Pellet({ mCols[6], mRows[1] + ((mRows[2] - mRows[1]) / 3) * 2 }));

	mPellets.push_back(new Pellet({ mCols[7], mRows[1] + ((mRows[2] - mRows[1]) / 3) }));
	mPellets.push_back(new Pellet({ mCols[7], mRows[1] + ((mRows[2] - mRows[1]) / 3) * 2 }));



	mPellets.push_back(new Pellet({ mCols[1], mRows[2] + ((mRows[3] - mRows[2]) / 3) }));
	mPellets.push_back(new Pellet({ mCols[1], mRows[2] + ((mRows[3] - mRows[2]) / 3) * 2 }));

	mPellets.push_back(new Pellet({ mCols[6], mRows[2] + ((mRows[3] - mRows[2]) / 3) }));
	mPellets.push_back(new Pellet({ mCols[6], mRows[2] + ((mRows[3] - mRows[2]) / 3) * 2 }));



	mPellets.push_back(new Pellet({ mCols[1], mRows[3] + ((mRows[4] - mRows[3]) / 3) }));
	mPellets.push_back(new Pellet({ mCols[1], mRows[3] + ((mRows[4] - mRows[3]) / 3) * 2 }));

	mPellets.push_back(new Pellet({ mCols[6], mRows[3] + ((mRows[4] - mRows[3]) / 3) }));
	mPellets.push_back(new Pellet({ mCols[6], mRows[3] + ((mRows[4] - mRows[3]) / 3) * 2 }));



	mPellets.push_back(new Pellet({ mCols[1], mRows[4] + ((mRows[5] - mRows[4]) / 3) }));
	mPellets.push_back(new Pellet({ mCols[1], mRows[4] + ((mRows[5] - mRows[4]) / 3) * 2 }));

	mPellets.push_back(new Pellet({ mCols[6], mRows[4] + ((mRows[5] - mRows[4]) / 3) }));
	mPellets.push_back(new Pellet({ mCols[6], mRows[4] + ((mRows[5] - mRows[4]) / 3) * 2 }));



	mPellets.push_back(new Pellet({ mCols[1], mRows[5] + ((mRows[6] - mRows[5]) / 3) }));
	mPellets.push_back(new Pellet({ mCols[1], mRows[5] + ((mRows[6] - mRows[5]) / 3) * 2 }));

	mPellets.push_back(new Pellet({ mCols[6], mRows[5] + ((mRows[6] - mRows[5]) / 3) }));
	mPellets.push_back(new Pellet({ mCols[6], mRows[5] + ((mRows[6] - mRows[5]) / 3) * 2 }));



	mPellets.push_back(new Pellet({ mCols[0], mRows[6] + ((mRows[7] - mRows[6]) / 3) }));
	mPellets.push_back(new Pellet({ mCols[0], mRows[6] + ((mRows[7] - mRows[6]) / 3) * 2 }));
	
	mPellets.push_back(new Pellet({ mCols[1], mRows[6] + ((mRows[7] - mRows[6]) / 3) }));
	mPellets.push_back(new Pellet({ mCols[1], mRows[6] + ((mRows[7] - mRows[6]) / 3) * 2 }));

	mPellets.push_back(new Pellet({ mCols[3], mRows[6] + ((mRows[7] - mRows[6]) / 3) }));
	mPellets.push_back(new Pellet({ mCols[3], mRows[6] + ((mRows[7] - mRows[6]) / 3) * 2 }));

	mPellets.push_back(new Pellet({ mCols[4], mRows[6] + ((mRows[7] - mRows[6]) / 3) }));
	mPellets.push_back(new Pellet({ mCols[4], mRows[6] + ((mRows[7] - mRows[6]) / 3) * 2 }));

	mPellets.push_back(new Pellet({ mCols[6], mRows[6] + ((mRows[7] - mRows[6]) / 3) }));
	mPellets.push_back(new Pellet({ mCols[6], mRows[6] + ((mRows[7] - mRows[6]) / 3) * 2 }));

	mPellets.push_back(new Pellet({ mCols[7], mRows[6] + ((mRows[7] - mRows[6]) / 3) }));
	mPellets.push_back(new Pellet({ mCols[7], mRows[6] + ((mRows[7] - mRows[6]) / 3) * 2 }));



	mPellets.push_back(new Pellet({ mCols[0] + ((mCols[1] - mCols[0])/5)*2, mRows[7] + ((mRows[8] - mRows[7]) / 3) }));
	mPellets.push_back(new Pellet({ mCols[0] + ((mCols[1] - mCols[0])/5)*2, mRows[7] + ((mRows[8] - mRows[7]) / 3) * 2 }));

	mPellets.push_back(new Pellet({ mCols[1], mRows[7] + ((mRows[8] - mRows[7]) / 3) }));
	mPellets.push_back(new Pellet({ mCols[1], mRows[7] + ((mRows[8] - mRows[7]) / 3) * 2 }));
	//the below 4 are misaligned as well (corrected)
	mPellets.push_back(new Pellet({ mCols[1] + ((mCols[3] - mCols[1]) / 6) * 3, mRows[7] + ((mRows[8] - mRows[7]) / 3)}));
	mPellets.push_back(new Pellet({ mCols[1] + ((mCols[3] - mCols[1]) / 6) * 3, mRows[7] + ((mRows[8] - mRows[7]) / 3) * 2 }));

	mPellets.push_back(new Pellet({ mCols[4] + ((mCols[6] - mCols[4]) / 6 ) * 3, mRows[7] + ((mRows[8] - mRows[7]) / 3)}));
	mPellets.push_back(new Pellet({ mCols[4] + ((mCols[6] - mCols[4]) / 6 ) * 3, mRows[7] + ((mRows[8] - mRows[7]) / 3) * 2 }));

	mPellets.push_back(new Pellet({ mCols[6], mRows[7] + ((mRows[8] - mRows[7]) / 3) }));
	mPellets.push_back(new Pellet({ mCols[6], mRows[7] + ((mRows[8] - mRows[7]) / 3) * 2 }));

	mPellets.push_back(new Pellet({ mCols[6] + ((mCols[7] - mCols[6]) / 5) * 3, mRows[7] + ((mRows[8] - mRows[7]) / 3) }));
	mPellets.push_back(new Pellet({ mCols[6] + ((mCols[7] - mCols[6]) / 5) * 3, mRows[7] + ((mRows[8] - mRows[7]) / 3) * 2 }));



	mPellets.push_back(new Pellet({ mCols[0], mRows[8] + ((mRows[9] - mRows[8]) / 3) }));
	mPellets.push_back(new Pellet({ mCols[0], mRows[8] + ((mRows[9] - mRows[8]) / 3) * 2 }));

	mPellets.push_back(new Pellet({ mCols[3], mRows[8] + ((mRows[9] - mRows[8]) / 3) }));
	mPellets.push_back(new Pellet({ mCols[3], mRows[8] + ((mRows[9] - mRows[8]) / 3) * 2 }));

	mPellets.push_back(new Pellet({ mCols[4], mRows[8] + ((mRows[9] - mRows[8]) / 3) }));
	mPellets.push_back(new Pellet({ mCols[4], mRows[8] + ((mRows[9] - mRows[8]) / 3) * 2 }));

	mPellets.push_back(new Pellet({ mCols[7], mRows[8] + ((mRows[9] - mRows[8]) / 3) }));
	mPellets.push_back(new Pellet({ mCols[7], mRows[8] + ((mRows[9] - mRows[8]) / 3) * 2 }));

}

void Level::setLifeIcons() {
	for (auto l : mPlayerLives) {
		delete l;
		l = nullptr;
	}
	mPlayerLives.clear();
	for (int i = 1; i <= mPlayer->Lives(); i++) {
		mPlayerLives.push_back(new Texture("PacmanAtlas.png", 472, 0, 14, 14));
		mPlayerLives[mPlayerLives.size() - 1]->Parent(this);
		mPlayerLives[mPlayerLives.size() - 1]->Scale(Vect2_One * 3);
		mPlayerLives[mPlayerLives.size() - 1]->Position(-275, 410);
		mPlayerLives[mPlayerLives.size() - 1]->Translate({ 42.0f * (mPlayerLives.size() - 1.0f) ,0 });
	}
}

// this function is not called in the constructor
void Level::resetLevel(bool newGame) {

	if (newGame) {
		for (auto p : mPellets) {
			p->Active(true);
		}
		mLevelNum++;
		mPlayer->ResetPelletsEaten();
		mNumOfFruitSpawned = 0;
		mFruitIndex++;
		delete mFruit;
		mFruit = new Fruit(mFruitIndex);
		mRedGhost->RageState(RedGhost::Unenraged);
		mAudioManager->PauseMusic();
	}
	else if (mPlayer->Lives() == 0) {
		mGameOver = true;
		if (mPlayer->Score() > mPlayer->HighScore()) {
			mPlayer->HighScore(mPlayer->Score());
		}
		mPlayer->ResetScore();
		mNumOfFruitSpawned = 0;
		mLivesGiven = 0;
		mRedGhost->RageState(RedGhost::Unenraged);
		mAudioManager->PauseMusic();
	}
	
	

	mRedGhost->Position(mNodeManager->getNode(66)->Position());
	mRedGhost->Reset();
	mPinkGhost->Reset();
	mBlueGhost->Reset();
	mOrangeGhost->Reset();

	if (!mGameOver) {
		mPlayer->Position({ 0,-400.0f });
		mPlayer->Respawn();
	}
	
	setLifeIcons();

	mStageStarted = false;
	mReadyTime = 0;
	mPinkGhostReleaseTime = 0.0f;
}


bool Level::GameOver() {
	return mGameOver;
}