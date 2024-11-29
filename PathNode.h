#pragma once
#include "Texture.h"
#include <vector>

using namespace SDLFramework;

class PathNode : public Texture {

public:

	PathNode(Vector2 pos);
	~PathNode();

	void Render() override;

	void AddConnection(PathNode* node);

private:

	std::vector<PathNode*> mConnections;

};


void linkNodes(PathNode* node1, PathNode* node2);