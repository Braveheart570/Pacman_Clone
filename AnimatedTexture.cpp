#include "AnimatedTexture.h"

namespace SDLFramework {

	AnimatedTexture::AnimatedTexture(std::string filename, int x, int y, int width, int height, int frameCount, float animationSpeed, AnimDir AnimationDir, bool managed) : Texture(filename, x, y, width, height) {

		mTimer = Timer::Instance();

		mStartX = x;
		mStartY = y;

		mFrameCount = frameCount;
		mAnimationSpeed = animationSpeed;
		mTimePerFrame = mAnimationSpeed / mFrameCount;
		mAnimationTimer = 0.0f;

		mWrapMode = Loop;
		mAnimationDirection = AnimationDir;

		mAnimationDone = false;
	}


	AnimatedTexture::~AnimatedTexture() {

		mTimer = nullptr;

	}


	void AnimatedTexture::SetWrapMode(WrapMode wrapMode) {

		mWrapMode = wrapMode;

	}


	bool AnimatedTexture::IsAnimating() {

		return !mAnimationDone;

	}



	void AnimatedTexture::ResetAnimation() {

		mAnimationTimer = 0.0f;
		mAnimationDone = false;

	}


	void AnimatedTexture::Update() {
		RunAnimation();
	}

	void AnimatedTexture::RunAnimation() {
		if (!mAnimationDone) {

			mAnimationTimer += mTimer->DeltaTime();


			if (mAnimationTimer >= mAnimationSpeed) {


				if (mWrapMode == Loop) {
					mAnimationTimer -= mAnimationSpeed;
				}
				else {
					mAnimationDone = true;
					mAnimationTimer = mAnimationSpeed - mTimePerFrame;
				}

			}

			if (mAnimationDirection == Horizontal) {
				mSourceRect.x = mStartX + (int)(mAnimationTimer / mTimePerFrame) * mWidth;
			}
			else {
				mSourceRect.y = mStartY + (int)(mAnimationTimer / mTimePerFrame) * mHeight;
			}


		}
	}

}