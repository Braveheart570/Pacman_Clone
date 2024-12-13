#pragma once
#include "gameentity.h"

using namespace SDLFramework;

class Tile : public GameEntity {

public:

	enum tileNeighborOrient {
		Up, Right, Down, Left
	};

	Tile();
	~Tile();

	void Update() override;
	void Render() override;

private:

	static const int MAX_NEIGHBORS = 4;

	Tile* mNeighbors[MAX_NEIGHBORS];

};