#include "PhysEntity.h"
/* this prevents the cyclical reference issue. 
this is ok since we onloy need enums from the manager, and the other file is just a helper file. 
this is kind of a last resort */
#include "PhysicsManager.h"
#include "PhysicsHelper.h"

namespace SDLFramework {


	void PhysEntity::AddCollider(Collider* collider, Vector2 localPos) {
		collider->Parent(this);
		collider->Position(localPos);
		mColliders.push_back(collider);

		if (mColliders.size() > 1 || mColliders[0]->getType() != Collider::ColliderType::Circle) {
			float furthestDistance = mColliders[0]->GetFurthestPoint().Magnitude();
			float dist = 0.0f;

			for (int i = 1; i < mColliders.size(); i++) {
				dist = mColliders[i]->GetFurthestPoint().Magnitude();

				if (dist > furthestDistance) {
					furthestDistance = dist;
				}
			}

			delete mBroadPhaseCollider;
			mBroadPhaseCollider = new CircleCollider(furthestDistance, true);
			mBroadPhaseCollider->Parent(this);
			mBroadPhaseCollider->Position(Vect2_Zero);
		}

	}


	PhysEntity::PhysEntity() {
		mBroadPhaseCollider = nullptr;
		mId = 0;

	}

	PhysEntity::~PhysEntity() {

		for (auto collider : mColliders) {
			delete collider;
			collider = nullptr;
		}
		mColliders.clear();

		delete mBroadPhaseCollider;
		mBroadPhaseCollider = nullptr;

		if (mId != 0) {
			PhysicsManager::Instance()->UnregisterEntity(mId);
		}

	}

	unsigned long PhysEntity::GetId() {
		return mId;
	}


	bool PhysEntity::IgnoreCollisions() {
		return false;
	}


	void PhysEntity::Render() {
		
		for (auto collider : mColliders) {
			collider->Render();
		}

		if (mBroadPhaseCollider) {
			mBroadPhaseCollider->Render();
		}

	}

	bool PhysEntity::CheckCollision(PhysEntity* other) {
		if (IgnoreCollisions() || other->IgnoreCollisions()) {
			return false;
		}

		bool narrowPhaseCheck = false;

		if (mBroadPhaseCollider && other->mBroadPhaseCollider) {

			narrowPhaseCheck = ColliderVsColliderCheck(mBroadPhaseCollider, other->mBroadPhaseCollider);

		}

		if (narrowPhaseCheck) {
			for (int i = 0; i < mColliders.size(); i++) {
				for (int j = 0; j < other->mColliders.size(); j++) {
					if (ColliderVsColliderCheck(mColliders[i], other->mColliders[j])) {
						//A collision has happened!
						return true;
					}
				}
			}
		}

		return false;

	}


}