#pragma once
# include "Texture.h"

namespace SDLFramework {

	class Collider : public GameEntity {

	public:

		enum class ColliderType { Box, Circle };

		Collider(ColliderType type);
		virtual ~Collider();

		virtual void Render();
		
		virtual Vector2 GetFurthestPoint() = 0;

		ColliderType getType();


	protected:


		void SetDebugTexture(Texture* texture);


		ColliderType mType;

		static const bool DEBUG_COLLIDERS = true;
		Texture* mDebugTexture;

	};

}