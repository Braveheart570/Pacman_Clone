#include "NodeManager.h"

NodeManager* NodeManager::sInstance = nullptr;


NodeManager* NodeManager::Instance() {

	if (sInstance == nullptr) {
		sInstance = new NodeManager();
	}
	return sInstance;

}

void NodeManager::Release() {
	delete sInstance;
	sInstance = nullptr;
}

void NodeManager::Render() {

	if (mRenderNodes) {
		for (auto n : mNodes) {
			n->Render();
		}
	}
	
}


NodeManager::NodeManager() {
	mRenderNodes = false;
}

NodeManager::~NodeManager() {

}

void NodeManager::AddNode(Vector2 pos) {
	int index = mNodes.size();
	mNodes.push_back(new PathNode(pos, index));
}

void NodeManager::AddNode(Vector2 pos, std::vector<PathNode*> connections) {
	int index = mNodes.size();
	mNodes.push_back(new PathNode(pos,index));
	for (auto c : connections) {
		mNodes[mNodes.size() - 1]->AddConnection(c);
	}
	

}

void NodeManager::AddWrapNodes(Vector2 pos1, Vector2 pos2, int wrap1Con, int wrap2Con) {

	int index = mNodes.size();
	mNodes.push_back(new WrapNode(pos1,index));
	index = mNodes.size();
	mNodes.push_back(new WrapNode(pos2, index));

	static_cast<WrapNode*>(mNodes[mNodes.size() - 2])->addWrapTo(static_cast<WrapNode*>(mNodes[mNodes.size() - 1]));
	static_cast<WrapNode*>(mNodes[mNodes.size() - 1])->addWrapTo(static_cast<WrapNode*>(mNodes[mNodes.size() - 2]));

	linkNodes(mNodes.size() - 2, wrap1Con);
	linkNodes(mNodes.size() - 1, wrap2Con);

}


PathNode* NodeManager::getNode(int index) {
	return mNodes[index];
}


void NodeManager::linkNodes(PathNode* node1, PathNode* node2) {
	node1->AddConnection(node2);
	node2->AddConnection(node1);
}

void NodeManager::linkNodes(int node1,int node2){

	getNode(node1)->AddConnection(getNode(node2));
	getNode(node2)->AddConnection(getNode(node1));

}

void NodeManager::RenderNodes(bool render) {
	mRenderNodes = render;
}

bool NodeManager::RenderNodes() {
	return mRenderNodes;
}