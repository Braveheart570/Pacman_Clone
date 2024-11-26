#include "CircleCollider.h"

namespace SDLFramework {


	CircleCollider::CircleCollider(float radius, bool broadPhase) : Collider(ColliderType::Circle) {

		mRadius = radius;

		if (DEBUG_COLLIDERS) {
			if (broadPhase) {
				SetDebugTexture(new Texture("BroadPhaseCollider.png"));
			}
			else {
				SetDebugTexture(new Texture("CircleCollider.png"));
			}

			//collider size is 50px
			mDebugTexture->Scale(Vect2_One * (radius * 2 / 50.0f));
		}
	}


	CircleCollider::~CircleCollider(){}


	float CircleCollider::GetRadius() {

		return mRadius;

	}

	Vector2 CircleCollider::GetFurthestPoint() {

		return Vect2_Right * (mRadius + Position(GameEntity::LOCAL)).Magnitude(); // look into this line more later.

	}





}