#pragma once
#include "Pellet.h"

using namespace SDLFramework;

class PowerPellet : public Pellet {

public:

	PowerPellet(Vector2 pos);

	void Hit(PhysEntity* entity) override;

private:

};