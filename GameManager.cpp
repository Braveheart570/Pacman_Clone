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
		
	}

	void GameManager::LateUpdate() {
		mPhysicsManager->Update();
		mInputManager->updatePreviewInput();
		
	}

	void GameManager::Render() {
		//old frame to clear
		mGraphics->ClearBackBuffer();

		//render calls here
		for (auto node : nodes) {
			node->Render();
		}
		mGhost->Render();

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
		nodes.push_back(new PathNode(Vector2(Graphics::SCREEN_WIDTH*0.12f,Graphics::SCREEN_HEIGHT*0.12f)));
		nodes.push_back(new PathNode(Vector2(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.12f)));
		nodes.push_back(new PathNode(Vector2(Graphics::SCREEN_WIDTH * 0.88f, Graphics::SCREEN_HEIGHT * 0.12f)));
		nodes.push_back(new PathNode(Vector2(Graphics::SCREEN_WIDTH * 0.88f, Graphics::SCREEN_HEIGHT * 0.5f)));
		nodes.push_back(new PathNode(Vector2(Graphics::SCREEN_WIDTH * 0.88f, Graphics::SCREEN_HEIGHT * 0.88f)));
		nodes.push_back(new PathNode(Vector2(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.88f)));
		nodes.push_back(new PathNode(Vector2(Graphics::SCREEN_WIDTH * 0.12f, Graphics::SCREEN_HEIGHT * 0.88f)));
		nodes.push_back(new PathNode(Vector2(Graphics::SCREEN_WIDTH * 0.12f, Graphics::SCREEN_HEIGHT * 0.5f)));
		nodes.push_back(new PathNode(Vector2(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.5f)));

		
		linkNodes(nodes[0],nodes[1]);
		linkNodes(nodes[0], nodes[7]);

		linkNodes(nodes[1], nodes[2]);
		linkNodes(nodes[1], nodes[8]);

		linkNodes(nodes[2], nodes[3]);
		
		linkNodes(nodes[3], nodes[4]);
		linkNodes(nodes[3], nodes[8]);

		linkNodes(nodes[4], nodes[5]);

		linkNodes(nodes[5], nodes[6]);
		linkNodes(nodes[5], nodes[8]);

		linkNodes(nodes[6], nodes[7]);

		linkNodes(nodes[7], nodes[8]);

		mGhost = new Ghost(nodes, nodes[2]->Position());

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

		//quit sdl subsystems
		SDL_Quit();
	}

}