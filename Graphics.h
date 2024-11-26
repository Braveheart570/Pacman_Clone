#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>

namespace SDLFramework {
	//singleton
	class Graphics {

	public:
		static const int SCREEN_WIDTH = 640;
		static const int SCREEN_HEIGHT = 480;

		static Graphics* Instance();

		//handle releaseing/ uninitializing/ dealocating memory.
		static void Release();
		static bool Initialized();

		SDL_Texture* LoadTexture(std::string path);

		void DrawTexture(
			SDL_Texture* texture, 
			SDL_Rect* srcRect = nullptr, 
			SDL_Rect* dstRect = nullptr, 
			float angle = 0.0f, 
			SDL_RendererFlip flip = SDL_FLIP_NONE
		);

		SDL_Texture* CreateTextTexture(TTF_Font* font, std::string text, SDL_Color color);

		void ClearBackBuffer();

		void Render();

		Graphics();
		~Graphics();

		bool Init();
		
	private:
		
		//this is going to hold the one instance of our graphics class.
		static Graphics* sInstance;
		static bool sInitialized;
		SDL_Window* mWindow = nullptr;
		SDL_Renderer* mRenderer = nullptr;
	};

}