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
		mGhost->Update();
		mPlayer->Update();
		
	}

	void GameManager::LateUpdate() {
		mPhysicsManager->Update();
		mInputManager->updatePreviewInput();
		
	}

	void GameManager::Render() {
		//old frame to clear
		mGraphics->ClearBackBuffer();

		//render calls here
		mNodeManager->Render();
		mGhost->Render();
		mPlayer->Render();

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
		mNodeManager = NodeManager::Instance();


		//Create Physics Layers
		mPhysicsManager->SetLayerCollisionMask(PhysicsManager::CollisionLayers::Friendly, 
			PhysicsManager::CollisionFlags::Hostile | 
			PhysicsManager::CollisionFlags::HostileProjectile
		);
		mPhysicsManager->SetLayerCollisionMask(PhysicsManager::CollisionLayers::Hostile,
			PhysicsManager::CollisionFlags::Friendly |
			PhysicsManager::CollisionFlags::FriendlyProjectile
		);
		mPhysicsManager->SetLayerCollisionMask(PhysicsManager::CollisionLayers::HostileProjectile,
			PhysicsManager::CollisionFlags::Friendly |
			PhysicsManager::CollisionFlags::FriendlyProjectile
		);
		mPhysicsManager->SetLayerCollisionMask(PhysicsManager::CollisionLayers::FriendlyProjectile,
			PhysicsManager::CollisionFlags::Hostile |
			PhysicsManager::CollisionFlags::HostileProjectile
		);

		//define objects here
		mNodeManager->AddNode(Vector2(Graphics::SCREEN_WIDTH * 0.25f - Graphics::SCREEN_WIDTH * 0.125f, Graphics::SCREEN_HEIGHT * 0.25f - Graphics::SCREEN_WIDTH * 0.125f));
		mNodeManager->AddNode(Vector2(Graphics::SCREEN_WIDTH * 0.5f - Graphics::SCREEN_WIDTH * 0.125f, Graphics::SCREEN_HEIGHT * 0.25f - Graphics::SCREEN_WIDTH * 0.125f));
		mNodeManager->AddNode(Vector2(Graphics::SCREEN_WIDTH * 0.75f - Graphics::SCREEN_WIDTH * 0.125f, Graphics::SCREEN_HEIGHT * 0.25f - Graphics::SCREEN_WIDTH * 0.125f));
		mNodeManager->AddNode(Vector2(Graphics::SCREEN_WIDTH * 1.0f - Graphics::SCREEN_WIDTH * 0.125f, Graphics::SCREEN_HEIGHT * 0.25f - Graphics::SCREEN_WIDTH * 0.125f));

		mNodeManager->AddNode(Vector2(Graphics::SCREEN_WIDTH * 0.25f - Graphics::SCREEN_WIDTH * 0.125f, Graphics::SCREEN_HEIGHT * 0.5f - Graphics::SCREEN_WIDTH * 0.125f));
		mNodeManager->AddNode(Vector2(Graphics::SCREEN_WIDTH * 0.5f - Graphics::SCREEN_WIDTH * 0.125f, Graphics::SCREEN_HEIGHT * 0.5f - Graphics::SCREEN_WIDTH * 0.125f));
		mNodeManager->AddNode(Vector2(Graphics::SCREEN_WIDTH * 0.75f - Graphics::SCREEN_WIDTH * 0.125f, Graphics::SCREEN_HEIGHT * 0.5f - Graphics::SCREEN_WIDTH * 0.125f));
		mNodeManager->AddNode(Vector2(Graphics::SCREEN_WIDTH * 1.0f - Graphics::SCREEN_WIDTH * 0.125f, Graphics::SCREEN_HEIGHT * 0.5f - Graphics::SCREEN_WIDTH * 0.125f));

		mNodeManager->AddNode(Vector2(Graphics::SCREEN_WIDTH * 0.25f - Graphics::SCREEN_WIDTH * 0.125f, Graphics::SCREEN_HEIGHT * 0.75f - Graphics::SCREEN_WIDTH * 0.125f));
		mNodeManager->AddNode(Vector2(Graphics::SCREEN_WIDTH * 0.5f - Graphics::SCREEN_WIDTH * 0.125f, Graphics::SCREEN_HEIGHT * 0.75f - Graphics::SCREEN_WIDTH * 0.125f));
		mNodeManager->AddNode(Vector2(Graphics::SCREEN_WIDTH * 0.75f - Graphics::SCREEN_WIDTH * 0.125f, Graphics::SCREEN_HEIGHT * 0.75f - Graphics::SCREEN_WIDTH * 0.125f));
		mNodeManager->AddNode(Vector2(Graphics::SCREEN_WIDTH * 1.0f - Graphics::SCREEN_WIDTH * 0.125f, Graphics::SCREEN_HEIGHT * 0.75f - Graphics::SCREEN_WIDTH * 0.125f));

		mNodeManager->AddNode(Vector2(Graphics::SCREEN_WIDTH * 0.25f - Graphics::SCREEN_WIDTH * 0.125f, Graphics::SCREEN_HEIGHT * 1.0f - Graphics::SCREEN_WIDTH * 0.125f));
		mNodeManager->AddNode(Vector2(Graphics::SCREEN_WIDTH * 0.5f - Graphics::SCREEN_WIDTH * 0.125f, Graphics::SCREEN_HEIGHT * 1.0f - Graphics::SCREEN_WIDTH * 0.125f));
		mNodeManager->AddNode(Vector2(Graphics::SCREEN_WIDTH * 0.75f - Graphics::SCREEN_WIDTH * 0.125f, Graphics::SCREEN_HEIGHT * 1.0f - Graphics::SCREEN_WIDTH * 0.125f));
		mNodeManager->AddNode(Vector2(Graphics::SCREEN_WIDTH * 1.0f - Graphics::SCREEN_WIDTH * 0.125f, Graphics::SCREEN_HEIGHT * 1.0f - Graphics::SCREEN_WIDTH * 0.125f));


		mNodeManager->linkNodes(mNodeManager->getNode(0), mNodeManager->getNode(1));
		mNodeManager->linkNodes(mNodeManager->getNode(1), mNodeManager->getNode(2));
		mNodeManager->linkNodes(mNodeManager->getNode(2), mNodeManager->getNode(3));

		mNodeManager->linkNodes(mNodeManager->getNode(4), mNodeManager->getNode(0));
		mNodeManager->linkNodes(mNodeManager->getNode(5), mNodeManager->getNode(1));
		mNodeManager->linkNodes(mNodeManager->getNode(6), mNodeManager->getNode(2));
		mNodeManager->linkNodes(mNodeManager->getNode(7), mNodeManager->getNode(3));

		mNodeManager->linkNodes(mNodeManager->getNode(4), mNodeManager->getNode(5));
		mNodeManager->linkNodes(mNodeManager->getNode(5), mNodeManager->getNode(6));
		mNodeManager->linkNodes(mNodeManager->getNode(6), mNodeManager->getNode(7));

		mNodeManager->linkNodes(mNodeManager->getNode(8), mNodeManager->getNode(4));
		mNodeManager->linkNodes(mNodeManager->getNode(9), mNodeManager->getNode(5));
		mNodeManager->linkNodes(mNodeManager->getNode(10), mNodeManager->getNode(6));
		mNodeManager->linkNodes(mNodeManager->getNode(11), mNodeManager->getNode(7));

		mNodeManager->linkNodes(mNodeManager->getNode(8), mNodeManager->getNode(9));
		mNodeManager->linkNodes(mNodeManager->getNode(9), mNodeManager->getNode(10));
		mNodeManager->linkNodes(mNodeManager->getNode(10), mNodeManager->getNode(11));

		mNodeManager->linkNodes(mNodeManager->getNode(12), mNodeManager->getNode(8));
		mNodeManager->linkNodes(mNodeManager->getNode(13), mNodeManager->getNode(9));
		mNodeManager->linkNodes(mNodeManager->getNode(14), mNodeManager->getNode(10));
		mNodeManager->linkNodes(mNodeManager->getNode(15), mNodeManager->getNode(11));

		mNodeManager->linkNodes(mNodeManager->getNode(12), mNodeManager->getNode(13));
		mNodeManager->linkNodes(mNodeManager->getNode(13), mNodeManager->getNode(14));
		mNodeManager->linkNodes(mNodeManager->getNode(14), mNodeManager->getNode(15));


		mPlayer = Player::Instance();
		mGhost = new Ghost(mNodeManager->getNode(2));

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

		NodeManager::Release();
		mNodeManager = nullptr;

		//quit sdl subsystems
		SDL_Quit();
	}

}