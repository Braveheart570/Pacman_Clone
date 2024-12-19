#pragma once
#include "Ghost.h"

using namespace SDLFramework;

class PinkGhost : public Ghost {

public:

	PinkGhost(PathNode* start);

	void setNewTargetNode() override;
	void setTextures() override;

private:



};