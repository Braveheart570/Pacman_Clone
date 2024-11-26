#pragma once
#include <bitset>
#include "PhysEntity.h"


namespace SDLFramework {

	class PhysicsManager {

	public:

		enum class CollisionLayers {
			Friendly,
			FriendlyProjectile,
			Hostile,
			HostileProjectile,
			MaxLayers // this acts as a stop of sorts
		};

		enum class CollisionFlags {
			None = 0x00,// 0000 0000
			Friendly = 0x01,
			FriendlyProjectile = 0x02,
			//some other friendly layer could go here
			Hostile = 0x04,
			HostileProjectile = 0x08
		};

		static PhysicsManager* Instance();
		static void Release();

		unsigned long RegisterEntity(PhysEntity* entity, CollisionLayers layer);
		void UnregisterEntity(unsigned long id);

		void SetLayerCollisionMask(CollisionLayers layer, CollisionFlags flag);

		void Update();


	private:

		PhysicsManager();
		~PhysicsManager();

		static PhysicsManager* sInstance;
		std::vector<PhysEntity*> mCollisionLayers[static_cast<unsigned int>(CollisionLayers::MaxLayers)]; // this is how you get the value of an Enum class memeber (in static memory)
		//mulidimensional array
		std::bitset<static_cast<unsigned int>(CollisionLayers::MaxLayers)> mLayerMasks[static_cast<unsigned int>(CollisionLayers::MaxLayers)];

		unsigned long mlastID;


	};


	inline PhysicsManager::CollisionFlags operator|(PhysicsManager::CollisionFlags a, PhysicsManager::CollisionFlags b) {

		return static_cast<PhysicsManager::CollisionFlags>(static_cast<unsigned int>(a) | static_cast <unsigned int>(b));

	}

	inline PhysicsManager::CollisionFlags operator&(PhysicsManager::CollisionFlags a, PhysicsManager::CollisionFlags b) {

		return static_cast<PhysicsManager::CollisionFlags>(static_cast<unsigned int>(a) & static_cast <unsigned int>(b));

	}

}