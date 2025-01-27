#include "ScreenManager.h"

ScreenManager* ScreenManager::sInstance = nullptr;

ScreenManager* ScreenManager::Instance() {
	if (sInstance == nullptr) {
		sInstance = new ScreenManager();
	}
	return sInstance;
}

void ScreenManager::Release() {
	delete sInstance;
	sInstance = nullptr;
}

ScreenManager::ScreenManager() {
	mInputManager = InputManager::Instance();
	mAudioManager = AudioManager::Instance();
	mPlayer = Player::Instance();
	mStartScreen = new StartScreen();
	mLevel = new Level();
	mLevel->setLifeIcons();
	mCurrentScreen = Start;
}

ScreenManager::~ScreenManager() {

	mInputManager = nullptr;
	mAudioManager = nullptr;
	mPlayer = nullptr;

	delete mStartScreen;
	mStartScreen = nullptr;

	delete mLevel;
	mLevel = nullptr;

}

void ScreenManager::Update() {

	switch (mCurrentScreen) {
	case Start:
		mStartScreen->Update();

		if (mInputManager->KeyPressed(SDL_SCANCODE_RETURN)) {
			mCurrentScreen = Play;
			mAudioManager->PlayMusic("pacman_beginning.wav",0);
		}

		break;
	case Play:
		mLevel->Update();

		if (mLevel->GameOver() && mInputManager->KeyPressed(SDL_SCANCODE_RETURN)) {
			delete mLevel;
			mLevel = new Level();
			mCurrentScreen = Start;
			mStartScreen->ResetAnimation();
			mPlayer->addLife();
			mPlayer->addLife();
			mPlayer->addLife();
			mPlayer->Respawn();
			mPlayer->ResetPelletsEaten();
			mLevel->setLifeIcons();
		}

		break;
	default:
		std::cerr << "Invalad screen type in ScreenManager." << std::endl;
	}

}

void ScreenManager::Render() {

	switch (mCurrentScreen) {
	case Start:
		mStartScreen->Render();
		break;
	case Play:
		mLevel->Render();
		break;
	}


}