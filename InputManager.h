#pragma once
#include <SDL.h>
#include "MathHelper.h"
#include <string>

namespace SDLFramework {


	class InputManager {
	public:
		static InputManager* Instance();
		static void Release();


		bool KeyDown(SDL_Scancode scancode);
		bool KeyPressed(SDL_Scancode scancode);
		bool keyReleased(SDL_Scancode scancode);

		enum MouseButton { Left = 0, Right, Middle, Back, Forward };

		bool MouseButtonDown(MouseButton button);
		bool MouseButtonPressed(MouseButton button);
		bool MouseButtonReleased(MouseButton button);
		Vector2 MousePosition();

		void Update();

		void updatePreviewInput();


	private:
		static InputManager* sInstance;
		const Uint8* mKeyboardState;
		Uint8* mPrevKeyboardState;
		int mKeyLength;


		Uint32 mPrevMouseState;
		Uint32 mMouseState;

		int mMouseXPos;
		int mMouseYPos;

		InputManager();
		~InputManager();


	};


}