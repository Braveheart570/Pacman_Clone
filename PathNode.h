#pragma once
#include "Texture.h"
#include <vector>

using namespace SDLFramework;

class PathNode : public Texture {

public:

	PathNode(Vector2 pos);
	~PathNode();

	void addConnection(PathNode* node);

private:

	PathNode* mConnections[4];

};