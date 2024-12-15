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
	mRenderNodes = true;
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