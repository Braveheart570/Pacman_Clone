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

protected:

	float mDefaultSpeed;
	float CruiseElroySpeedMultiplier1;
	float CruiseElroySpeedMultiplier2;

	bool mScatterOverride;

};