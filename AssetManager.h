#pragma once
#include <SDL_Mixer.h>
#include "Graphics.h"
#include <sstream>
#include<map>

namespace SDLFramework {

	class AssetManager {

	public:

		static AssetManager* Instance();
		static void Release();



		SDL_Texture* GetTexture(std::string fileName, bool managed = true);
		SDL_Texture* GetText(std::string text, std::string fileName, int size, SDL_Color color, bool managed = true);

		Mix_Music* GetMusic(std::string fileName, bool managed = true);
		Mix_Chunk* GetSFX(std::string fileName, bool managed = true);



		void DestroyTexture(SDL_Texture* texture);

		void DestroyMusic(Mix_Music* music);
		void DestroySFX(Mix_Chunk* sfx);

		

	private:

		AssetManager();
		~AssetManager();

		void UnloadTexture(SDL_Texture* texture);

		void UnloadMusic(Mix_Music* music);
		void UnloadSFX(Mix_Chunk* sfx);


		TTF_Font* GetFont(std::string fileName, int size);



		static AssetManager* sInstance;

		// map texture to there path strings
		std::map<std::string, SDL_Texture*> mTextures;

		std::map<std::string, TTF_Font*> mFonts;

		// how many times is a texture being referenced.
		std::map<SDL_Texture*, unsigned int> mTextureRefCount;


		std::map<std::string, Mix_Music*> mMusic;
		std::map<std::string, Mix_Chunk*> mSFX;
		
		std::map<Mix_Music*, unsigned int> mMusicRefCount;
		std::map<Mix_Chunk*, unsigned int> mSFXRefCount;

	};
}
