#pragma once
#include "Ghost.h"
#include "RedGhost.h"

class BlueGhost : public Ghost {

public:

	BlueGhost(PathNode* start, RedGhost* red);
	~BlueGhost();

	void setNewTargetNode() override;

private:

	RedGhost* mRedGhost;

};