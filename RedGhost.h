#pragma once
#include "Ghost.h";

class RedGhost : public Ghost {

public:

	RedGhost(PathNode* start);


	void setNewTargetNode() override;

private:


};