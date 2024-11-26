#include "AssetManager.h"

namespace SDLFramework {


	AssetManager* AssetManager::sInstance = nullptr;


	AssetManager* AssetManager::Instance() {
		if (sInstance == nullptr) {
			sInstance = new AssetManager();
		}

		return sInstance;
	}

	void AssetManager::Release() {
		delete sInstance;
		sInstance = nullptr;
	}


	AssetManager::AssetManager() {

	}

	AssetManager::~AssetManager() {

		for (auto tex : mTextures) {
			if (tex.second != nullptr) {
				SDL_DestroyTexture(tex.second);
			}
		}

		mTextures.clear();


	}

	SDL_Texture* AssetManager::GetTexture(std::string fileName, bool managed) {
		std::string fullPath = SDL_GetBasePath();
		fullPath.append("Assets/" + fileName);

		if (mTextures[fullPath] == nullptr) {
			//we have not yet created this img.
			mTextures[fullPath] = Graphics::Instance()->LoadTexture(fullPath);
		}

		if (mTextures[fullPath] != nullptr && managed) {
			mTextureRefCount[mTextures[fullPath]] != 1;
		}

		return mTextures[fullPath];
	}


	SDL_Texture* AssetManager::GetText(std::string text, std::string fileName, int size, SDL_Color color, bool managed) {
		
		std::stringstream ss;

		ss << size << (int)color.r << (int)color.g << (int)color.b;

		std::string key = text + fileName + ss.str();

		if (mTextures[key] == nullptr) {
			TTF_Font* font = GetFont(fileName, size);
			mTextures[key] = Graphics::Instance()->CreateTextTexture(font, text, color);
		}

		if (mTextures[key] != nullptr && managed) {
			mTextureRefCount[mTextures[key]] += 1;
		}

		return mTextures[key];

	}


	TTF_Font* AssetManager::GetFont(std::string fileName, int size) {

		std::string fullpath = SDL_GetBasePath();
		fullpath.append("Assets/" + fileName);


		std::stringstream ss;
		ss << size;
		std::string key = fullpath + ss.str();


		if (mFonts[key] == nullptr) {
			mFonts[key] = TTF_OpenFont(fullpath.c_str(), size);

			if (mFonts[key] == nullptr) {
				std::cout << "Unable to load font: " << fileName << "! TTF Error: " << TTF_GetError() << std::endl;
				return nullptr;
			}

		}

		return mFonts[key];

	}


	Mix_Music* AssetManager::GetMusic(std::string fileName, bool managed) {

		std::string fullpath = SDL_GetBasePath();
		fullpath.append("Assets/" + fileName);

		if (mMusic[fullpath] == nullptr) {
			mMusic[fullpath] = Mix_LoadMUS(fullpath.c_str());
		}

		if (mMusic[fullpath] == nullptr) {

			std::cerr << "Unabe to load music " << fileName << "! Mix error: " << Mix_GetError() << std::endl;
			return nullptr;

		}
		else if (managed) {

			mMusicRefCount[mMusic[fullpath]] += 1;

		}

		return mMusic[fullpath];



	}

	Mix_Chunk* AssetManager::GetSFX(std::string fileName, bool managed) {

		std::string fullpath = SDL_GetBasePath();
		fullpath.append("Assets/" + fileName);

		if (mSFX[fullpath] == nullptr) {
			mSFX[fullpath] = Mix_LoadWAV(fullpath.c_str());
		}

		if (mSFX[fullpath] == nullptr) {

			std::cerr << "Unabe to load SFX " << fileName << "! Mix error: " << Mix_GetError() << std::endl;
			return nullptr;

		}
		else if (managed) {

			mSFXRefCount[mSFX[fullpath]] += 1;

		}

		return mSFX[fullpath];

	}


	void AssetManager::DestroyTexture(SDL_Texture* texture) {
		std::map<SDL_Texture*, unsigned int>::iterator it = mTextureRefCount.find(texture);

		if (it != mTextureRefCount.end()) {
			it->second -= 1;
			if (it->second == 0) {
				UnloadTexture(it->first);
				mTextureRefCount.erase(it->first);
			}
		}
		else {
			//something is still referencing this texture.
			UnloadTexture(texture);
		}


	}

	void AssetManager::UnloadTexture(SDL_Texture* texture) {

		bool found = false;
		std::string key;
		std::map<std::string, SDL_Texture*>::iterator it;

		for (it = mTextures.begin(); it != mTextures.end() && !found; it++) {
			if ((found = it->second == texture)) {
				//success.
				SDL_DestroyTexture(it->second);
				key = it->first;
			}
		}

		if (found) {
			mTextures.erase(key);
		}


	}

	void AssetManager::DestroyMusic(Mix_Music* music) {

		std::map<Mix_Music*, unsigned int>::iterator it = mMusicRefCount.find(music);

		if (it != mMusicRefCount.end()) {
			it->second -= 1;

			if (it->second == 0) {
				UnloadMusic(it->first);
				mMusicRefCount.erase(it->first);
			}

		}
		else {
			UnloadMusic(music);
		}

	}

	void AssetManager::UnloadMusic(Mix_Music* music) {

		bool found = false;
		std::string key;
		std::map<std::string, Mix_Music*>::iterator it;

		for (it = mMusic.begin(); it != mMusic.end() && !found; it++) {

			if ((found = it->second == music)) {

				Mix_FreeMusic(it->second);
				key = it->first;

			}

		}

		if (found) {
			mMusic.erase(key);
		}

	}



	void AssetManager::DestroySFX(Mix_Chunk* sfx) {

		std::map<Mix_Chunk*, unsigned int>::iterator it = mSFXRefCount.find(sfx);

		if (it != mSFXRefCount.end()) {

			it->second - 1;
			if (it->second ==0) {
				UnloadSFX(it->first);
				mSFXRefCount.erase(it->first);
			}

		}
		else {
			UnloadSFX(sfx);
		}

	}


	void AssetManager::UnloadSFX(Mix_Chunk* sfx) {

		bool found = false;
		std::string key;
		std::map<std::string, Mix_Chunk*>::iterator it;

		for (it = mSFX.begin(); it != mSFX.end() && !found; it++) {

			if ((found = it->second == sfx)) {

				Mix_FreeChunk(it->second);
				key = it->first;

			}

		}

		if (found) {
			mSFX.erase(key);
		}

	}


}
