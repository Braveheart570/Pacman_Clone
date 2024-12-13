#include "Tile.h"

Tile::Tile() {

	for (int i = 0; i < MAX_NEIGHBORS; i++) {
		mNeighbors[i] = nullptr;
	}

}

Tile::~Tile() {

	for (int i = 0; i < MAX_NEIGHBORS; i++) {
		delete mNeighbors[i];
		mNeighbors[i] = nullptr;
	}

}