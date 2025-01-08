#pragma once
#include "StartScreen.h"
#include "Level.h"
#include <iostream>

class ScreenManager {

public:

	static ScreenManager* Instance();
	static void Release();

	void Update();
	void Render();

private:

	enum Screens {Start, Play};
	Screens mCurrentScreen;

	static ScreenManager* sInstance;

	InputManager* mInputManager;
	AudioManager* mAudioManager;
	Player* mPlayer;

	//screens
	StartScreen* mStartScreen;
	Level* mLevel;

	ScreenManager();
	~ScreenManager();

};