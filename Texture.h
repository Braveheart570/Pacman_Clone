#pragma once
#include "GameEntity.h"
#include "AssetManager.h"

namespace SDLFramework {


	class Texture :public GameEntity {

	public:
		Texture(std::string filename, bool managed = true);
		Texture(std::string filename,int x, int y, int width, int height, bool managed = true);
		// for text textures
		Texture(std::string text, std::string fontPath, int size, SDL_Color color, bool managed = true);

		~Texture();

		Vector2 ScaledDimensions();


		void SetSourceRect(SDL_Rect* sourceRect);


		void Render() override;

	protected:
		SDL_Texture* mTex;
		Graphics* mGraphics;

		int mWidth;
		int mHeight;

		bool mClipped; //clipping out a sprite from a spritesheet. that kind of thing.
		SDL_Rect mSourceRect; //the plain image
		SDL_Rect mDestinationRect; //source with modifications or effects.

	};



}
