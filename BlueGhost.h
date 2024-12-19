#pragma once
#include "Ghost.h"
#include "RedGhost.h"

class BlueGhost : public Ghost {

public:

	BlueGhost(PathNode* start, RedGhost* red);
	~BlueGhost();

	void setNewTargetNode() override;
	void setTextures() override;

private:

	RedGhost* mRedGhost;

};