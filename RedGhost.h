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

	void RageState(rageState state);
	rageState RageState();

protected:
	
	float mRageSpeedMultiplier1;
	float mRageSpeedMultiplier2;

	bool mScatterOverride;

	rageState mRageState;

};