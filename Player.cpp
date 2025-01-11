#include "Player.h"
#include "ghost.h"
#include "Pellet.h"

Player* Player::sInstance = nullptr;


Player* Player::Instance() {

	if (sInstance == nullptr) {
		sInstance = new Player();
	}
	return sInstance;

}

void Player::Release() {
	delete sInstance;
	sInstance = nullptr;
}

Vector2 Player::Dir() {

	Vector2 retVal = (mTargetNode->Position() - Position()).Normalized();

	if (retVal.x == retVal.x && retVal.y == retVal.y) { //nan check. comparing a nan to itself will return false.
		return retVal;
	}
	else {
		return Vect2_Zero;
	}

	

}

Vector2 Player::nextTurn() {
	return mNextTurn;
}

int Player::Score() {
	return mScore;
}

void Player::AddScore(int change) {
	mScore += change;
}

int Player::Lives() {
	return mLives;
}

void Player::addLife() {
	mLives++;
}

void Player::GhostEaten() {
	switch (mGhostsEaten) {
	case 0:
		AddScore(200);
		break;
	case 1:
		AddScore(400);
		break;
	case 2:
		AddScore(800);
		break;
	case 3:
		AddScore(1600);
		break;
	default:
		AddScore(1600);
		break;
	}
	mGhostsEaten++;
}

Player::Player() {

	mTimer = Timer::Instance();
	mInputManager = InputManager::Instance();
	mAudioManager = AudioManager::Instance();

	mHighScore = 1600;
	mSpeed = 100;
	mLives = 2;
	mWallHit = false;
	ResetPelletsEaten();

	mStartNode = NodeManager::Instance()->getNode(47);
	
	mEnergized = false;
	mFrightenedDurations[0] = 6.0f;
	mFrightenedDurations[1] = 6.0f;
	mFrightenedDurations[2] = 5.0f;
	mFrightenedDurations[3] = 5.0f;
	mFrightenedDurations[4] = 4.0f;
	mFrightenedDurations[5] = 4.0f;
	mFrightenedDurations[6] = 4.0f;
	mFrightenedDurations[7] = 3.0f;
	mFrightenedTime = 0.0f;

	mPlayingWaka = false;
	mWakaBufferTime = 0.0f;
	mWakaBufferDuration = 0.25f;

	Respawn();

	mPacmanUp = new AnimatedTexture("PacmanAtlas.png", 456,32,15,15,2,0.5f,AnimatedTexture::Horizontal);
	mPacmanUp->Parent(this);
	mPacmanUp->Position(Vect2_Zero);
	mPacmanUp->Scale(Vect2_One*3);

	mPacmanRight = new AnimatedTexture("PacmanAtlas.png", 456, 16, 15, 15, 2, 0.5f, AnimatedTexture::Horizontal);
	mPacmanRight->Parent(this);
	mPacmanRight->Position(Vect2_Zero);
	mPacmanRight->Scale(Vect2_One * 3);

	mPacmanDown = new AnimatedTexture("PacmanAtlas.png", 456, 48, 15, 15, 2, 0.5f, AnimatedTexture::Horizontal);
	mPacmanDown->Parent(this);
	mPacmanDown->Position(Vect2_Zero);
	mPacmanDown->Scale(Vect2_One * 3);

	mPacmanLeft = new AnimatedTexture("PacmanAtlas.png", 456, 0, 15, 15, 2, 0.5f, AnimatedTexture::Horizontal);
	mPacmanLeft->Parent(this);
	mPacmanLeft->Position(Vect2_Zero);
	mPacmanLeft->Scale(Vect2_One * 3);

	mPacmanStopped = new Texture("PacmanAtlas.png", 488, 0, 15, 15);
	mPacmanStopped->Parent(this);
	mPacmanStopped->Position(Vect2_Zero);
	mPacmanStopped->Scale(Vect2_One * 3);

	mPacmanDeath = new AnimatedTexture("PacmanAtlas.png",503,0,16,16,12,1.0f,AnimatedTexture::Horizontal);
	mPacmanDeath->Parent(this);
	mPacmanDeath->Position(Vect2_Zero);
	mPacmanDeath->Scale(Vect2_One * 3);
	mPacmanDeath->SetWrapMode(AnimatedTexture::Once);

	AddCollider(new CircleCollider(10,true));
	AddCollider(new CircleCollider(10));
	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Friendly);
	

}

Player::~Player() {

	
	mAudioManager = nullptr;
	mInputManager = nullptr;

	mPacmanTex = nullptr; // this points to one of the below textures, that is why we do not delete what it points to.
	delete mPacmanUp;
	mPacmanUp = nullptr;
	delete mPacmanRight;
	mPacmanRight = nullptr;
	delete mPacmanDown;
	mPacmanDown = nullptr;
	delete mPacmanLeft;
	mPacmanLeft = nullptr;

	delete mPacmanDeath;
	mPacmanDeath = nullptr;

	delete mPacmanStopped;
	mPacmanStopped = nullptr;

	mStartNode = nullptr;
	mCurrentNode = nullptr;
	mTargetNode = nullptr;

}

void Player::MoveKeys() {

	//movement keys
	if (mInputManager->KeyPressed(SDL_SCANCODE_W)) {
		mNextTurn = -Vect2_Up;
	}
	else if (mInputManager->KeyPressed(SDL_SCANCODE_A)) {
		mNextTurn = -Vect2_Right;
	}
	else if (mInputManager->KeyPressed(SDL_SCANCODE_S)) {
		mNextTurn = Vect2_Up;
	}
	else if (mInputManager->KeyPressed(SDL_SCANCODE_D)) {
		mNextTurn = Vect2_Right;
	}

}

void Player::Update() {
	HandleTexture();
	if (mIsDieing) {
		mPacmanDeath->Update();
		if (!mPacmanDeath->IsAnimating()) {
			mIsDieing = false;
			mIsDead = true;
		}
		return;
	}

	if (mPacmanTex != nullptr) {
		mPacmanTex->Update();
	}

	
	// waka sfx audio logic
	if (mPlayingWaka) {

		mWakaBufferTime += mTimer->DeltaTime();
		if (mWakaBufferTime >= mWakaBufferDuration) {
			mPlayingWaka = false;
			mAudioManager->StopSFX(mWakaChannel);
			mWakaBufferTime = 0.0f;
		}
	}

	if (mEnergized) {
		mFrightenedTime += mTimer->DeltaTime();
		int frightenedIndex = mLevelNum - 1;
		if (frightenedIndex >= mFrightenedLevels) frightenedIndex = mFrightenedLevels - 1;
		if (mFrightenedTime >= mFrightenedDurations[frightenedIndex]) {
			mEnergized = false;
			mGhostsEaten = 0;
			mAudioManager->ResumeMusic();
		}
	}


	Vector2 dir = Dir();

	if (-mNextTurn == dir) {
		PathNode* temp = mTargetNode;
		mTargetNode = mCurrentNode;
		mCurrentNode = temp;
		dir = -dir;
	}


	Vector2 pos = Position() + dir * mSpeed * mTimer->DeltaTime(); // new position
	Vector2 dist = mTargetNode->Position() - pos;
	
	if (dist.MagnitudeSqr() < EPSILON * mSpeed / 25.0f) { //check if reached target

		WrapNode* wrapNode;
		if (wrapNode = dynamic_cast<WrapNode*>(mTargetNode)) { //handling wrap nodes
			mCurrentNode = wrapNode->WrapTo();
			mTargetNode = mCurrentNode->GetConnectionByIndex(0);
			pos = mCurrentNode->Position();
		}
		else {
			pos = mTargetNode->Position(); // set position to target

			mCurrentNode = mTargetNode;

			mTargetNode = mCurrentNode->GetConnectionbyDir(mNextTurn); //attempt to find new target


			if (mTargetNode == nullptr && (dir == mNextTurn || dir == Vect2_Zero)) { //if there is no node in this direction and we are going straight then the player should stop
				mTargetNode = mCurrentNode;
			}
			else if (mTargetNode == nullptr) { // if we cannot go the chosen direction and we are not going straight then continue straight.
				mTargetNode = mCurrentNode->GetConnectionbyDir(dir);

				if (mTargetNode == nullptr) {// if we cannot go straight then stop
					mTargetNode = mCurrentNode;
				}
			}
		}

		

		
	}
	
	Position(pos);

}

void Player::Render() {

	if (mIsDead) {
		return;
	}

	if (mPacmanTex != nullptr) {
		mPacmanTex->Render();
	}
	else {
		mPacmanStopped->Render();
	}
	
	//PhysEntity::Render();
}

void Player::Hit(PhysEntity* other) {

	if (dynamic_cast<Pellet*>(other)) {
		mPelletsEaten++;
		if (!mPlayingWaka && !mIsDieing && !mIsDead) {
			mAudioManager->PlaySFX("Waka.wav", -1, mWakaChannel);
			mPlayingWaka = true;
		}
		mWakaBufferTime = 0.0f;
		
	}

}

void Player::ResetPelletsEaten() {
	mPelletsEaten = 0;
}

int Player::PelletsEaten() {

	return mPelletsEaten;
}

void Player::Die() {

	mIsDieing = true;
	mPacmanDeath->ResetAnimation();
	mAudioManager->PauseMusic();
	mAudioManager->PlaySFX("playerDeath.wav",0,0);

	mPlayingWaka = false;
	mAudioManager->StopSFX(mWakaChannel);
}



void Player::HandleTexture() {

	if (mIsDieing) {
		mPacmanTex = mPacmanDeath;
		return;
	}

	Vector2 dir = (mCurrentNode->Position() - mTargetNode->Position()).Normalized();

	if (dir == Vect2_Up) {
		mPacmanTex = mPacmanUp;
	}
	else if (dir == Vect2_Right) {
		mPacmanTex = mPacmanRight;
	}
	else if (dir == -Vect2_Up) {
		mPacmanTex = mPacmanDown;
	}
	else if (dir == -Vect2_Right) {
		mPacmanTex = mPacmanLeft;
	}
	else {
		mPacmanTex = nullptr;
	}

}

bool Player::IsDying() {

	return mIsDieing;

}

bool Player::isDead() {

	return mIsDead;

}

void Player::Respawn() {
	if (isDead()) {
		mLives -= 1;
	}
	
	mCurrentNode = mStartNode;
	mTargetNode = mCurrentNode;
	Position(mCurrentNode->Position());
	mIsDead = false;
	mIsDieing = false;
	mNextTurn = Dir();
	mEnergized = false;

	mPacmanTex = nullptr; // will display as stopped pacman

	mPlayingWaka = false;
	mAudioManager->StopSFX(mWakaChannel);

}

void Player::Energize() {

	mEnergized = true;
	mFrightenedTime = 0;
	mAudioManager->PlaySFX("energized.wav",0,0);
	AudioManager::Instance()->PauseMusic();

}

bool Player::Energized() {
	return mEnergized;
}

float Player::EnergizedTimeLeftPercent() {
	int frightenedIndex = mLevelNum - 1;
	if (frightenedIndex >= mFrightenedLevels) frightenedIndex = mFrightenedLevels - 1;
	return mFrightenedTime / mFrightenedDurations[frightenedIndex];
}

int Player::GhostsEaten() {

	return mGhostsEaten;

}

int Player::HighScore() {

	return mHighScore;

}

void Player::HighScore(int highscore) {
	mHighScore = highscore;
}

void Player::ResetScore() {
	mScore = 0;
}

int Player::LevelNum() {
	return mLevelNum;
}

void Player::IncrementLevelNum() {
	mLevelNum++;
}

void Player::ResetLevelNum() {
	mLevelNum = 1;
}