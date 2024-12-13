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
	
	mHighScoreboard = new Scoreboard();
	mHighScoreboard->Parent(this);
	mHighScoreboard->Position(0,-400.0f);


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
	mHighScoreboard->Render();

}

void Level::CreateNodes() {
	mNodeManager->AddNode(Vector2(Graphics::SCREEN_WIDTH * 0.1f, Graphics::SCREEN_HEIGHT * 0.16f));
	mNodeManager->AddNode(Vector2(Graphics::SCREEN_WIDTH * 0.255f, Graphics::SCREEN_HEIGHT * 0.16f));
	mNodeManager->AddNode(Vector2(Graphics::SCREEN_WIDTH * 0.45f, Graphics::SCREEN_HEIGHT * 0.16f));

	mNodeManager->AddNode(Vector2(Graphics::SCREEN_WIDTH * 0.1f, Graphics::SCREEN_HEIGHT * 0.26f));
	mNodeManager->AddNode(Vector2(Graphics::SCREEN_WIDTH * 0.255f, Graphics::SCREEN_HEIGHT * 0.26f));
	mNodeManager->AddNode(Vector2(Graphics::SCREEN_WIDTH * 0.45f, Graphics::SCREEN_HEIGHT * 0.26f));

	mNodeManager->linkNodes(mNodeManager->getNode(0),mNodeManager->getNode(1));
	mNodeManager->linkNodes(mNodeManager->getNode(1), mNodeManager->getNode(2));
	mNodeManager->linkNodes(mNodeManager->getNode(0), mNodeManager->getNode(3));

	mNodeManager->linkNodes(mNodeManager->getNode(3), mNodeManager->getNode(4));
	mNodeManager->linkNodes(mNodeManager->getNode(4), mNodeManager->getNode(1));
	mNodeManager->linkNodes(mNodeManager->getNode(4), mNodeManager->getNode(5));
	mNodeManager->linkNodes(mNodeManager->getNode(5), mNodeManager->getNode(2));
	
}