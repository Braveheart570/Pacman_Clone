#pragma once
#include "Graphics.h"
#include "AnimatedTexture.h"
#include "InputManager.h"
#include "AudioManager.h"
#include "PhysicsManager.h"

#include "PathNode.h"


namespace SDLFramework {

	//Singleton
	class GameManager {
	public:
		// these functions are key in singletons
		static GameManager* Instance();
		static void Release();


		GameManager();
		~GameManager();


		void Update();
		void LateUpdate();

		void Render();

		void Run();


	private:
		const int FRAME_RATE = 60;
		// this is how we are creating this as a singleton
		static GameManager* sInstance;
		//loop cotrol
		bool mQuit;

		//modules
		Graphics* mGraphics;
		Timer* mTimer;
		AssetManager* mAssetManager;
		InputManager* mInputManager;
		AudioManager* mAudioManager;
		PhysicsManager* mPhysicsManager;


		//testing
		std::vector<PathNode*> nodes;


		SDL_Event mEvents;
	};

}