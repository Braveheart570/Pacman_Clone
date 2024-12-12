#include "Level.h"

Level::Level() {
	mTimer = Timer::Instance();
	mNodeManager = NodeManager::Instance();
	CreateNodes();
	mPlayer = Player::Instance();

	mLevelBackground = new Texture("PacmanAtlas.png",227,0,225,248);
	mLevelBackground->Parent(this);
	mLevelBackground->Scale(Vect2_One * ((Graphics::SCREEN_WIDTH / 225.0f)-0.2f));
	mLevelBackground->Position(Vect2_Zero);

	mRedGhost = new Ghost(mNodeManager->getNode(2));


	Position(Graphics::SCREEN_WIDTH/2,Graphics::SCREEN_HEIGHT/2);//call this last
}

Level::~Level() {

	Timer::Release();
	mTimer = nullptr;
	Player::Release();
	mPlayer = nullptr;
	NodeManager::Release();
	mNodeManager = nullptr;

	delete mLevelBackground;
	mLevelBackground = nullptr;

	delete mRedGhost;
	mRedGhost = nullptr;
	delete mPinkGhost;
	mPinkGhost = nullptr;
	delete mBlueGhost;
	mBlueGhost = nullptr;
	delete mOrangeGhost;
	mOrangeGhost = nullptr;

	delete mHighScoreboard;
	mHighScoreboard = nullptr;
	delete mScoreboard;
	mScoreboard = nullptr;

	
}

void Level::Update() {
	mPlayer->Update();
	mRedGhost->Update();
}

void Level::Render() {

	mLevelBackground->Render();
	mNodeManager->Render();
	mPlayer->Render();
	mRedGhost->Render();

}

void Level::CreateNodes() {
	mNodeManager->AddNode(Vector2(Graphics::SCREEN_WIDTH * 0.25f - Graphics::SCREEN_WIDTH * 0.125f, Graphics::SCREEN_HEIGHT * 0.25f - Graphics::SCREEN_WIDTH * 0.125f));
	mNodeManager->AddNode(Vector2(Graphics::SCREEN_WIDTH * 0.5f - Graphics::SCREEN_WIDTH * 0.125f, Graphics::SCREEN_HEIGHT * 0.25f - Graphics::SCREEN_WIDTH * 0.125f));
	mNodeManager->AddNode(Vector2(Graphics::SCREEN_WIDTH * 0.75f - Graphics::SCREEN_WIDTH * 0.125f, Graphics::SCREEN_HEIGHT * 0.25f - Graphics::SCREEN_WIDTH * 0.125f));
	mNodeManager->AddNode(Vector2(Graphics::SCREEN_WIDTH * 1.0f - Graphics::SCREEN_WIDTH * 0.125f, Graphics::SCREEN_HEIGHT * 0.25f - Graphics::SCREEN_WIDTH * 0.125f));

	mNodeManager->AddNode(Vector2(Graphics::SCREEN_WIDTH * 0.25f - Graphics::SCREEN_WIDTH * 0.125f, Graphics::SCREEN_HEIGHT * 0.5f - Graphics::SCREEN_WIDTH * 0.125f));
	mNodeManager->AddNode(Vector2(Graphics::SCREEN_WIDTH * 0.5f - Graphics::SCREEN_WIDTH * 0.125f, Graphics::SCREEN_HEIGHT * 0.5f - Graphics::SCREEN_WIDTH * 0.125f));
	mNodeManager->AddNode(Vector2(Graphics::SCREEN_WIDTH * 0.75f - Graphics::SCREEN_WIDTH * 0.125f, Graphics::SCREEN_HEIGHT * 0.5f - Graphics::SCREEN_WIDTH * 0.125f));
	mNodeManager->AddNode(Vector2(Graphics::SCREEN_WIDTH * 1.0f - Graphics::SCREEN_WIDTH * 0.125f, Graphics::SCREEN_HEIGHT * 0.5f - Graphics::SCREEN_WIDTH * 0.125f));

	mNodeManager->AddNode(Vector2(Graphics::SCREEN_WIDTH * 0.25f - Graphics::SCREEN_WIDTH * 0.125f, Graphics::SCREEN_HEIGHT * 0.75f - Graphics::SCREEN_WIDTH * 0.125f));
	mNodeManager->AddNode(Vector2(Graphics::SCREEN_WIDTH * 0.5f - Graphics::SCREEN_WIDTH * 0.125f, Graphics::SCREEN_HEIGHT * 0.75f - Graphics::SCREEN_WIDTH * 0.125f));
	mNodeManager->AddNode(Vector2(Graphics::SCREEN_WIDTH * 0.75f - Graphics::SCREEN_WIDTH * 0.125f, Graphics::SCREEN_HEIGHT * 0.75f - Graphics::SCREEN_WIDTH * 0.125f));
	mNodeManager->AddNode(Vector2(Graphics::SCREEN_WIDTH * 1.0f - Graphics::SCREEN_WIDTH * 0.125f, Graphics::SCREEN_HEIGHT * 0.75f - Graphics::SCREEN_WIDTH * 0.125f));

	mNodeManager->AddNode(Vector2(Graphics::SCREEN_WIDTH * 0.25f - Graphics::SCREEN_WIDTH * 0.125f, Graphics::SCREEN_HEIGHT * 1.0f - Graphics::SCREEN_WIDTH * 0.125f));
	mNodeManager->AddNode(Vector2(Graphics::SCREEN_WIDTH * 0.5f - Graphics::SCREEN_WIDTH * 0.125f, Graphics::SCREEN_HEIGHT * 1.0f - Graphics::SCREEN_WIDTH * 0.125f));
	mNodeManager->AddNode(Vector2(Graphics::SCREEN_WIDTH * 0.75f - Graphics::SCREEN_WIDTH * 0.125f, Graphics::SCREEN_HEIGHT * 1.0f - Graphics::SCREEN_WIDTH * 0.125f));
	mNodeManager->AddNode(Vector2(Graphics::SCREEN_WIDTH * 1.0f - Graphics::SCREEN_WIDTH * 0.125f, Graphics::SCREEN_HEIGHT * 1.0f - Graphics::SCREEN_WIDTH * 0.125f));


	mNodeManager->linkNodes(mNodeManager->getNode(0), mNodeManager->getNode(1));
	mNodeManager->linkNodes(mNodeManager->getNode(1), mNodeManager->getNode(2));
	mNodeManager->linkNodes(mNodeManager->getNode(2), mNodeManager->getNode(3));

	mNodeManager->linkNodes(mNodeManager->getNode(4), mNodeManager->getNode(0));
	mNodeManager->linkNodes(mNodeManager->getNode(5), mNodeManager->getNode(1));
	mNodeManager->linkNodes(mNodeManager->getNode(6), mNodeManager->getNode(2));
	mNodeManager->linkNodes(mNodeManager->getNode(7), mNodeManager->getNode(3));

	mNodeManager->linkNodes(mNodeManager->getNode(4), mNodeManager->getNode(5));
	mNodeManager->linkNodes(mNodeManager->getNode(5), mNodeManager->getNode(6));
	mNodeManager->linkNodes(mNodeManager->getNode(6), mNodeManager->getNode(7));

	mNodeManager->linkNodes(mNodeManager->getNode(8), mNodeManager->getNode(4));
	mNodeManager->linkNodes(mNodeManager->getNode(9), mNodeManager->getNode(5));
	mNodeManager->linkNodes(mNodeManager->getNode(10), mNodeManager->getNode(6));
	mNodeManager->linkNodes(mNodeManager->getNode(11), mNodeManager->getNode(7));

	mNodeManager->linkNodes(mNodeManager->getNode(8), mNodeManager->getNode(9));
	mNodeManager->linkNodes(mNodeManager->getNode(9), mNodeManager->getNode(10));
	mNodeManager->linkNodes(mNodeManager->getNode(10), mNodeManager->getNode(11));

	mNodeManager->linkNodes(mNodeManager->getNode(12), mNodeManager->getNode(8));
	mNodeManager->linkNodes(mNodeManager->getNode(13), mNodeManager->getNode(9));
	mNodeManager->linkNodes(mNodeManager->getNode(14), mNodeManager->getNode(10));
	mNodeManager->linkNodes(mNodeManager->getNode(15), mNodeManager->getNode(11));

	mNodeManager->linkNodes(mNodeManager->getNode(12), mNodeManager->getNode(13));
	mNodeManager->linkNodes(mNodeManager->getNode(13), mNodeManager->getNode(14));
	mNodeManager->linkNodes(mNodeManager->getNode(14), mNodeManager->getNode(15));
}