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
	mStartScreen = new StartScreen();
	mLevel = new Level();
	mCurrentScreen = Start;
}

ScreenManager::~ScreenManager() {

	mInputManager = nullptr;

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
			mStartScreen->ResetAnimation();
		}

		break;
	case Play:
		mLevel->Update();

		if (mLevel->GameOver() && mInputManager->KeyPressed(SDL_SCANCODE_RETURN)) {
			delete mLevel;
			mLevel = new Level();
			mCurrentScreen = Start;
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