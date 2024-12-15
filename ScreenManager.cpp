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
	mStartScreen = new startScreen();
	mCurrentScreen = Start;
}

ScreenManager::~ScreenManager() {

	mInputManager = nullptr;

	delete mStartScreen;
	mStartScreen = nullptr;

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

		break;
	}


}