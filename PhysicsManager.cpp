#include "PhysicsManager.h"

namespace SDLFramework{

	PhysicsManager* PhysicsManager::sInstance = nullptr;

	PhysicsManager* PhysicsManager::Instance() {

		if (sInstance == nullptr) {
			sInstance = new PhysicsManager();
		}

		return sInstance;

	}

	void PhysicsManager::Release() {
		delete sInstance;
		sInstance = nullptr;
	}


	PhysicsManager::PhysicsManager() {
		mlastID = 0;

		for (int i = 0; i < static_cast<unsigned int>(CollisionLayers::MaxLayers); i++) {
			mLayerMasks[i] = std::bitset<static_cast<unsigned int>(CollisionLayers::MaxLayers)>(static_cast<unsigned int>(CollisionFlags::None));
		}
	}

	PhysicsManager::~PhysicsManager() {
		for (auto layer : mCollisionLayers) {
			layer.clear();
		}
	}

	void PhysicsManager::SetLayerCollisionMask(CollisionLayers layer, CollisionFlags flag) {

		mLayerMasks[static_cast<unsigned int>(layer)] = std::bitset<static_cast<unsigned int>(CollisionLayers::MaxLayers)>(static_cast<unsigned int>(flag));

	}

	unsigned long PhysicsManager::RegisterEntity(PhysEntity* entity, PhysicsManager::CollisionLayers layer) {

		mCollisionLayers[static_cast<unsigned int>(layer)].push_back(entity);
		mlastID++;
		return mlastID;
	}

	void PhysicsManager::UnregisterEntity(unsigned long id) {

		bool found = false;

		// loop through all collision layers
		for (int i = 0; i < static_cast<unsigned int>(CollisionLayers::MaxLayers) && !found; i++) {
			//loop through all of the objects in a specific collision layer
			for (int j = 0; j < mCollisionLayers[i].size(); j++) {
				if (mCollisionLayers[i][j]->GetId() == id) {
					mCollisionLayers[i].erase(mCollisionLayers[i].begin() + j);
					found = true;
				}
			}
		}

	}


	void PhysicsManager::Update() {

		const unsigned int maxlayerCount = static_cast<unsigned int>(CollisionLayers::MaxLayers);

		//iteration 1 - looking through all of our layers
		for (int i = 0; i < maxlayerCount; i++) {
			//iteration 2 - looking through all of our layers
			for (int j = 0; j < maxlayerCount; j++) {
				// checking to see if these layers should collide.
				if (mLayerMasks[i].test(j) && i <= j) { // we do 1 <= j so we do not redo checks we have already done.
					//iteration 1 - looking through all of our objects on iteration 1's layer
					for (int k = 0; k < mCollisionLayers[i].size(); k++) {
						// iteration 2 - looking throught all of our objects on iteration 2's layer
						for (int l = 0; l < mCollisionLayers[j].size(); l++) {
							// this is where the actual collision check is happening
							if (mCollisionLayers[i][k]->CheckCollision(mCollisionLayers[j][l])) {
								// a collision has happened!
								mCollisionLayers[i][k]->Hit(mCollisionLayers[j][l]);
								mCollisionLayers[j][l]->Hit(mCollisionLayers[i][k]);
							}
						}
					}
				}
			}
		}

	}



}