#pragma once
#include "Collider.h"
#include <vector>

namespace SDLFramework {

	class PhysEntity : public GameEntity {

	public:
		PhysEntity();
		virtual ~PhysEntity();

		unsigned long GetId();

		bool CheckCollision(PhysEntity* other);

		virtual void Hit(PhysEntity* other) { std::cout << "A collision has happened." << std::endl; }

		virtual void Render() override;


	protected:


		virtual bool IgnoreCollisions();

		void AddCollider(Collider* colliderm, Vector2 localPos = Vect2_Zero);



		std::vector<Collider*> mColliders;

		Collider* mBroadPhaseCollider;

		unsigned long int mId;
	};

}