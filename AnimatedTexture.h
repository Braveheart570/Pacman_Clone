#pragma once
#include "Texture.h"
#include "Timer.h"

namespace SDLFramework {

	class AnimatedTexture : public Texture {
	public:
		enum WrapMode { Once = 0, Loop };
		enum AnimDir{Horizontal = 0, Vertical};

		AnimatedTexture(std::string filename, int x, int y, int width, int height, int frameCount, float animationSpeed, AnimDir AnimationDir, bool managed = true);
		~AnimatedTexture();

		void SetWrapMode(WrapMode mode);

		bool IsAnimating();

		virtual void ResetAnimation();

		void Update();


	protected:

		virtual void RunAnimation();

		Timer* mTimer;
		int mStartX;
		int mStartY;
		int mFrameCount;
		float mAnimationSpeed; // in seconds
		float mTimePerFrame; // time to display
		float mAnimationTimer; // time displayed

		WrapMode mWrapMode;
		AnimDir mAnimationDirection;

		bool mAnimationDone;

	};


}
