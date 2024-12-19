#pragma once
#include "Ghost.h"

class OrangeGhost : public Ghost {

public:

	OrangeGhost(PathNode* start);

	void setNewTargetNode() override;
	void setTextures() override;

private:


};