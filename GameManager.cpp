#include "GameManager.h"


namespace SDLFramework {

	GameManager* GameManager::sInstance = nullptr;

	GameManager* GameManager::Instance() {

		if (sInstance == nullptr) {
			sInstance = new GameManager();
		}

		return sInstance;

	}

	void GameManager::Release() {
		delete sInstance;
		sInstance = nullptr;
	}


	void GameManager::Run() {
		//main game loops
		while (!mQuit) {

			mTimer->Update();

			// while there are events inside of events variable.
			while (SDL_PollEvent(&mEvents)) {
				switch (mEvents.type) {
				case SDL_QUIT:
					mQuit = true;
					break;
				}
			}

			// frame rate independence
			if (mTimer->DeltaTime() >= 1.0f / FRAME_RATE) {
				
				mTimer->Reset();
				Update();
				LateUpdate();
				Render();

			}

			



		}
	}


	void GameManager::Update() {

		mInputManager->Update();

		//update code here
		mScreenManager->Update();
		
	}

	void GameManager::LateUpdate() {
		mPhysicsManager->Update();
		mInputManager->updatePreviewInput();
		
	}

	void GameManager::Render() {
		//old frame to clear
		mGraphics->ClearBackBuffer();

		//render calls here
		mScreenManager->Render();

		//draw to screem
		mGraphics->Render();
	}

	GameManager::GameManager() : mQuit(false) {
		// this is how you access a singleton;
		mGraphics = Graphics::Instance();

		if (!Graphics::Initialized()) {
			mQuit = true;
		}


		mTimer = Timer::Instance();
		mAssetManager = AssetManager::Instance();
		mInputManager = InputManager::Instance();
		mAudioManager = AudioManager::Instance();
		mPhysicsManager = PhysicsManager::Instance();
		mScreenManager = ScreenManager::Instance();
		mNodeManager = NodeManager::Instance();
		mPlayer = Player::Instance();


		//Create Physics Layers
		mPhysicsManager->SetLayerCollisionMask(PhysicsManager::CollisionLayers::Friendly, 
			PhysicsManager::CollisionFlags::Hostile | 
			PhysicsManager::CollisionFlags::HostileProjectile
		);
		mPhysicsManager->SetLayerCollisionMask(PhysicsManager::CollisionLayers::Hostile,
			PhysicsManager::CollisionFlags::Friendly |
			PhysicsManager::CollisionFlags::FriendlyProjectile
		);
		mPhysicsManager->SetLayerCollisionMask(PhysicsManager::CollisionLayers::Consumable,
			PhysicsManager::CollisionFlags::Friendly |
			PhysicsManager::CollisionFlags::FriendlyProjectile
		);
		mPhysicsManager->SetLayerCollisionMask(PhysicsManager::CollisionLayers::FriendlyProjectile,
			PhysicsManager::CollisionFlags::Hostile |
			PhysicsManager::CollisionFlags::HostileProjectile
		);

		//define objects here
		

	}

	GameManager::~GameManager() {
		//release modules
		Graphics::Release();
		mGraphics = nullptr;

		Timer::Release();
		mTimer = nullptr;

		AssetManager::Release();
		mAssetManager = nullptr;

		InputManager::Release();
		mInputManager = nullptr;

		AudioManager::Release();
		mAudioManager = nullptr;

		PhysicsManager::Release();
		mPhysicsManager = nullptr;

		ScreenManager::Release();
		mScreenManager = nullptr;

		NodeManager::Release();
		mNodeManager = nullptr;

		Player::Release();
		mPlayer = nullptr;

		ScoreBubble::Release();

		//quit sdl subsystems
		SDL_Quit();
	}

}