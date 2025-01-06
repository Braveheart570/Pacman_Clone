#pragma once
#include "Ghost.h";

class RedGhost : public Ghost {

public:

	RedGhost(PathNode* start);


	void setNewTargetNode() override;
	void setTextures() override;

	void Reset() override;
	void handleScatter() override;

	//cruise elroy
	void Enrage();
	bool Enraged();

protected:
	// Cruise Elroy is the name for enraged mode in the original game.
	float mCruiseElroySpeedMultiplier1;
	float mCruiseElroySpeedMultiplier2;

	bool mScatterOverride;

};