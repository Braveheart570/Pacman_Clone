#pragma once
#include "PathNode.h"
#include <vector>
#include "WrapNode.h"

class NodeManager {

public:

	static NodeManager* Instance();
	static void Release();

	void Render();
	void Update() {}

	void linkNodes(PathNode* node1, PathNode* node2);
	void linkNodes(int node1, int node2);

	void AddNode(Vector2 pos);
	void AddNode(Vector2 pos, std::vector<PathNode*> connections);

	void AddWrapNodes(Vector2 pos1, Vector2 pos2, int wrap1Con, int wrap2Con);

	PathNode* getNode(int index);

	void RenderNodes(bool render);
	bool RenderNodes();

private:

	bool mRenderNodes;

	static NodeManager* sInstance;

	std::vector<PathNode*> mNodes;

	NodeManager();
	~NodeManager();

};