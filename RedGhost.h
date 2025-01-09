#pragma once
#include "Ghost.h";

class RedGhost : public Ghost {

public:

	enum rageState {Unenraged,Enraged1,Enraged2};

	RedGhost(PathNode* start);

	void setNewTargetNode() override;
	void setTextures() override;

	void Reset() override;
	void handleScatter() override;

	//cruise elroy
	void RageState(rageState state);
	rageState RageState();

protected:
	// Cruise Elroy is the name for enraged mode in the original game.
	float mCruiseElroySpeedMultiplier1;
	float mCruiseElroySpeedMultiplier2;

	bool mScatterOverride;

	rageState mRageState;

};