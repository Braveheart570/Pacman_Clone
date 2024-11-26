#include "Timer.h"

namespace SDLFramework {

	Timer* Timer::sInstance = nullptr;

	Timer* Timer::Instance() {
		if (sInstance == nullptr) {
			sInstance = new Timer();
		}

		return sInstance;
	}

	void Timer::Release() {
		delete sInstance;
		sInstance = nullptr;
	}


	void Timer::Reset() {
		mStartTicks = SDL_GetTicks();
	}

	float Timer::DeltaTime() {
		return mDeltaTime;
	}

	void Timer::TimeScale(float timeScale) {
		mTimeScale = timeScale;
	}

	float Timer::TimeScale() {
		return mTimeScale;
	}

	void Timer::Update() {
		
		mElapsedTicks = SDL_GetTicks() - mStartTicks;
		// convert to seconds
		mDeltaTime = mElapsedTicks * 0.001f;
	}

	Timer::Timer() {
		Reset();
		mElapsedTicks = 0;
		mDeltaTime = 0.0f;
		mTimeScale = 1.0f; // running at normal speed.
	}

	Timer::~Timer() {

	}

}