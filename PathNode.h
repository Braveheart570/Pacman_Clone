#pragma once
#include "Texture.h"
#include <vector>

using namespace SDLFramework;

class PathNode : public Texture {

public:

	PathNode(Vector2 pos, int index);
	~PathNode();

	void Render() override;

	void AddConnection(PathNode* node);

	PathNode* ClosestConnection(Vector2 target);

	PathNode* GetConnectionbyDir(Vector2 dir);

	int ConnectionsSize();

	PathNode* GetConnectionByIndex(int index);

protected:

	std::vector<PathNode*> mConnections;

	Texture* mLabelTex;

};