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
	CreateNodes();
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

void NodeManager::CreateNodes() {

	mRows[0] = Graphics::SCREEN_HEIGHT * 0.16f;
	mRows[1] = Graphics::SCREEN_HEIGHT * 0.26f;
	mRows[2] = Graphics::SCREEN_HEIGHT * 0.33f;
	mRows[3] = Graphics::SCREEN_HEIGHT * 0.4f;
	mRows[4] = Graphics::SCREEN_HEIGHT * 0.475f;
	mRows[5] = Graphics::SCREEN_HEIGHT * 0.55f;
	mRows[6] = Graphics::SCREEN_HEIGHT * 0.62f;
	mRows[7] = Graphics::SCREEN_HEIGHT * 0.69f;
	mRows[8] = Graphics::SCREEN_HEIGHT * 0.765f;
	mRows[9] = Graphics::SCREEN_HEIGHT * 0.84f;

	mCols[0] = Graphics::SCREEN_WIDTH * 0.1f;
	mCols[1] = Graphics::SCREEN_WIDTH * 0.255f;
	mCols[2] = Graphics::SCREEN_WIDTH * 0.35f;
	mCols[3] = Graphics::SCREEN_WIDTH * 0.45f;
	mCols[4] = Graphics::SCREEN_WIDTH * 0.555f;
	mCols[5] = Graphics::SCREEN_WIDTH * 0.65f;
	mCols[6] = Graphics::SCREEN_WIDTH * 0.75f;
	mCols[7] = Graphics::SCREEN_WIDTH * 0.915f;


	AddNode(Vector2(mCols[0], mRows[0]));
	AddNode(Vector2(mCols[1], mRows[0]));
	AddNode(Vector2(mCols[3], mRows[0]));
	AddNode(Vector2(mCols[4], mRows[0]));
	AddNode(Vector2(mCols[6], mRows[0]));
	AddNode(Vector2(mCols[7], mRows[0]));

	AddNode(Vector2(mCols[0], mRows[1]));
	AddNode(Vector2(mCols[1], mRows[1]));
	AddNode(Vector2(mCols[2], mRows[1]));
	AddNode(Vector2(mCols[3], mRows[1]));
	AddNode(Vector2(mCols[4], mRows[1]));
	AddNode(Vector2(mCols[5], mRows[1]));
	AddNode(Vector2(mCols[6], mRows[1]));
	AddNode(Vector2(mCols[7], mRows[1]));

	AddNode(Vector2(mCols[0], mRows[2]));
	AddNode(Vector2(mCols[1], mRows[2]));
	AddNode(Vector2(mCols[2], mRows[2]));
	AddNode(Vector2(mCols[3], mRows[2]));
	AddNode(Vector2(mCols[4], mRows[2]));
	AddNode(Vector2(mCols[5], mRows[2]));
	AddNode(Vector2(mCols[6], mRows[2]));
	AddNode(Vector2(mCols[7], mRows[2]));

	AddNode(Vector2(mCols[2], mRows[3]));
	AddNode(Vector2(mCols[3], mRows[3]));
	AddNode(Vector2(mCols[4], mRows[3]));
	AddNode(Vector2(mCols[5], mRows[3]));

	AddNode(Vector2(mCols[1], mRows[4]));
	AddNode(Vector2(mCols[2], mRows[4]));
	AddNode(Vector2(mCols[5], mRows[4]));
	AddNode(Vector2(mCols[6], mRows[4]));

	AddNode(Vector2(mCols[2], mRows[5]));
	AddNode(Vector2(mCols[3], mRows[5]));
	AddNode(Vector2(mCols[4], mRows[5]));
	AddNode(Vector2(mCols[5], mRows[5]));

	AddNode(Vector2(mCols[0], mRows[6]));
	AddNode(Vector2(mCols[1], mRows[6]));
	AddNode(Vector2(mCols[2], mRows[6]));
	AddNode(Vector2(mCols[3], mRows[6]));
	AddNode(Vector2(mCols[4], mRows[6]));
	AddNode(Vector2(mCols[5], mRows[6]));
	AddNode(Vector2(mCols[6], mRows[6]));
	AddNode(Vector2(mCols[7], mRows[6]));

	AddNode(Vector2(mCols[0], mRows[7]));
	AddNode(Vector2(mCols[0] + ((mCols[1] - mCols[0]) / 5) * 2, mRows[7]));
	AddNode(Vector2(mCols[1], mRows[7]));
	AddNode(Vector2(mCols[2], mRows[7]));
	AddNode(Vector2(mCols[3], mRows[7]));
	AddNode(Vector2(mCols[4], mRows[7]));
	AddNode(Vector2(mCols[5], mRows[7]));
	AddNode(Vector2(mCols[6], mRows[7]));
	AddNode(Vector2(mCols[6] + ((mCols[7] - mCols[6]) / 5) * 3, mRows[7]));
	AddNode(Vector2(mCols[7], mRows[7]));

	AddNode(Vector2(mCols[0], mRows[8]));
	AddNode(Vector2(mCols[0] + ((mCols[1] - mCols[0]) / 5) * 2, mRows[8]));
	AddNode(Vector2(mCols[1], mRows[8]));
	AddNode(Vector2(mCols[2], mRows[8]));
	AddNode(Vector2(mCols[3], mRows[8]));
	AddNode(Vector2(mCols[4], mRows[8]));
	AddNode(Vector2(mCols[5], mRows[8]));
	AddNode(Vector2(mCols[6], mRows[8]));
	AddNode(Vector2(mCols[6] + ((mCols[7] - mCols[6]) / 5) * 3, mRows[8]));
	AddNode(Vector2(mCols[7], mRows[8]));

	AddNode(Vector2(mCols[0], mRows[9]));
	AddNode(Vector2(mCols[3], mRows[9]));
	AddNode(Vector2(mCols[4], mRows[9]));
	AddNode(Vector2(mCols[7], mRows[9]));



	//horizontal links
	linkNodes(0, 1);
	linkNodes(1, 2);

	linkNodes(3, 4);
	linkNodes(4, 5);

	linkNodes(6, 7);
	linkNodes(7, 8);
	linkNodes(8, 9);
	linkNodes(9, 10);
	linkNodes(10, 11);
	linkNodes(11, 12);
	linkNodes(12, 13);

	linkNodes(14, 15);

	linkNodes(16, 17);

	linkNodes(18, 19);

	linkNodes(20, 21);

	linkNodes(22, 23);
	//intentional gap here
	linkNodes(24, 25);

	linkNodes(26, 27);

	linkNodes(28, 29);

	linkNodes(30, 31);
	linkNodes(31, 32);
	linkNodes(32, 33);

	linkNodes(34, 35);
	linkNodes(35, 36);
	linkNodes(36, 37);

	linkNodes(38, 39);
	linkNodes(39, 40);
	linkNodes(40, 41);

	linkNodes(42, 43);

	linkNodes(44, 45);
	linkNodes(45, 46);
	linkNodes(46, 47);
	linkNodes(47, 48);
	linkNodes(48, 49);

	linkNodes(50, 51);

	linkNodes(52, 53);
	linkNodes(53, 54);

	linkNodes(55, 56);

	linkNodes(57, 58);

	linkNodes(59, 60);
	linkNodes(60, 61);

	linkNodes(62, 63);
	linkNodes(63, 64);
	linkNodes(64, 65);

	//vertical links

	linkNodes(0, 6);
	linkNodes(1, 7);
	linkNodes(2, 9);
	linkNodes(3, 10);
	linkNodes(4, 12);
	linkNodes(5, 13);

	linkNodes(14, 6);
	linkNodes(15, 7);
	linkNodes(16, 8);
	linkNodes(19, 11);
	linkNodes(20, 12);
	linkNodes(21, 13);

	linkNodes(23, 17);
	linkNodes(24, 18);

	linkNodes(26, 15);
	linkNodes(27, 22);
	linkNodes(28, 25);
	linkNodes(29, 20);

	linkNodes(30, 27);
	linkNodes(33, 28);

	linkNodes(35, 26);
	linkNodes(36, 30);
	linkNodes(39, 33);
	linkNodes(40, 29);

	linkNodes(42, 34);
	linkNodes(44, 35);
	linkNodes(46, 37);
	linkNodes(47, 38);
	linkNodes(49, 40);
	linkNodes(51, 41);

	linkNodes(53, 43);
	linkNodes(54, 44);
	linkNodes(55, 45);
	linkNodes(58, 48);
	linkNodes(59, 49);
	linkNodes(60, 50);

	linkNodes(62, 52);
	linkNodes(63, 56);
	linkNodes(64, 57);
	linkNodes(65, 61);

	//ghost house

	AddNode({ Graphics::SCREEN_WIDTH / 2,mRows[3] });
	AddNode({ Graphics::SCREEN_WIDTH / 2,mRows[4] + 5.0f });
	AddNode({ (Graphics::SCREEN_WIDTH / 2) - 48,mRows[4] + 5.0f });
	AddNode({ (Graphics::SCREEN_WIDTH / 2) + 48,mRows[4] + 5.0f });

	linkNodes(23, 66);
	linkNodes(66, 24);
	getNode(67)->AddConnection(getNode(66));
	getNode(68)->AddConnection(getNode(67));
	getNode(69)->AddConnection(getNode(67));

	//wrapnodes
	AddWrapNodes({ 0,mRows[4] }, { Graphics::SCREEN_WIDTH,mRows[4] }, 26, 29);
}