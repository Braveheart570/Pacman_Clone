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

	PathNode* ClosestConnection(Vector2 target);

	PathNode* GetConnectionbyDir(Vector2 dir);

private:

	std::vector<PathNode*> mConnections;

};