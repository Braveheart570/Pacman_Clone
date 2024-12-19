#include "Level.h"

Level::Level() {
	mTimer = Timer::Instance();
	mNodeManager = NodeManager::Instance();
	CreateNodes();
	mPlayer = Player::Instance();

	mScore = 0;

	mLevelBackground = new Texture("PacmanAtlas.png",227,0,225,248);
	mLevelBackground->Parent(this);
	mLevelBackground->Scale(Vect2_One * ((Graphics::SCREEN_WIDTH / 225.0f)-0.2f));
	mLevelBackground->Position(Vect2_Zero);

	mRedGhost = new RedGhost(mNodeManager->getNode(66));
	mPinkGhost = new PinkGhost(mNodeManager->getNode(1));
	mBlueGhost = new BlueGhost(mNodeManager->getNode(16),mRedGhost);
	mOrangeGhost = new OrangeGhost(mNodeManager->getNode(71));
	
	mScoreboard = new Scoreboard();
	mScoreboard->Parent(this);
	mScoreboard->Position(-300.0f, -400.0f);
	mScoreboard->Score(mScore);

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

	for (auto p : mPellets) {
		delete p;
		p = nullptr;
	}
	
}

void Level::Update() {
	mPlayer->Update();
	mRedGhost->Update();
	mPinkGhost->Update();
	mBlueGhost->Update();
	mOrangeGhost->Update();
}

void Level::Render() {

	mLevelBackground->Render();
	mNodeManager->Render();
	for (auto p : mPellets) {
		p->Render();
	}
	mPlayer->Render();
	mRedGhost->Render();
	mPinkGhost->Render();
	mBlueGhost->Render();
	mOrangeGhost->Render();

	mHighScoreboard->Render();
	mScoreboard->Render();

}

void Level::CreateNodes() {

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
	mCols[2] = Graphics::SCREEN_WIDTH * 0.35f;//
	mCols[3] = Graphics::SCREEN_WIDTH * 0.45f;
	mCols[4] = Graphics::SCREEN_WIDTH * 0.555f;
	mCols[5] = Graphics::SCREEN_WIDTH * 0.65f;//
	mCols[6] = Graphics::SCREEN_WIDTH * 0.75f;
	mCols[7] = Graphics::SCREEN_WIDTH * 0.915f;
	

	mNodeManager->AddNode(Vector2(mCols[0], mRows[0]));
	mNodeManager->AddNode(Vector2(mCols[1], mRows[0]));
	mNodeManager->AddNode(Vector2(mCols[3], mRows[0]));
	mNodeManager->AddNode(Vector2(mCols[4], mRows[0]));
	mNodeManager->AddNode(Vector2(mCols[6], mRows[0]));
	mNodeManager->AddNode(Vector2(mCols[7], mRows[0]));

	mNodeManager->AddNode(Vector2(mCols[0], mRows[1]));
	mNodeManager->AddNode(Vector2(mCols[1], mRows[1]));
	mNodeManager->AddNode(Vector2(mCols[2], mRows[1]));
	mNodeManager->AddNode(Vector2(mCols[3], mRows[1]));
	mNodeManager->AddNode(Vector2(mCols[4], mRows[1]));
	mNodeManager->AddNode(Vector2(mCols[5], mRows[1]));
	mNodeManager->AddNode(Vector2(mCols[6], mRows[1]));
	mNodeManager->AddNode(Vector2(mCols[7], mRows[1]));

	mNodeManager->AddNode(Vector2(mCols[0], mRows[2]));
	mNodeManager->AddNode(Vector2(mCols[1], mRows[2]));
	mNodeManager->AddNode(Vector2(mCols[2], mRows[2]));
	mNodeManager->AddNode(Vector2(mCols[3], mRows[2]));
	mNodeManager->AddNode(Vector2(mCols[4], mRows[2]));
	mNodeManager->AddNode(Vector2(mCols[5], mRows[2]));
	mNodeManager->AddNode(Vector2(mCols[6], mRows[2]));
	mNodeManager->AddNode(Vector2(mCols[7], mRows[2]));

	mNodeManager->AddNode(Vector2(mCols[2], mRows[3]));
	mNodeManager->AddNode(Vector2(mCols[3], mRows[3]));
	mNodeManager->AddNode(Vector2(mCols[4], mRows[3]));
	mNodeManager->AddNode(Vector2(mCols[5], mRows[3]));

	mNodeManager->AddNode(Vector2(mCols[1], mRows[4]));
	mNodeManager->AddNode(Vector2(mCols[2], mRows[4]));
	mNodeManager->AddNode(Vector2(mCols[5], mRows[4]));
	mNodeManager->AddNode(Vector2(mCols[6], mRows[4]));

	mNodeManager->AddNode(Vector2(mCols[2], mRows[5]));
	mNodeManager->AddNode(Vector2(mCols[3], mRows[5]));
	mNodeManager->AddNode(Vector2(mCols[4], mRows[5]));
	mNodeManager->AddNode(Vector2(mCols[5], mRows[5]));

	mNodeManager->AddNode(Vector2(mCols[0], mRows[6]));
	mNodeManager->AddNode(Vector2(mCols[1], mRows[6]));
	mNodeManager->AddNode(Vector2(mCols[2], mRows[6]));
	mNodeManager->AddNode(Vector2(mCols[3], mRows[6]));
	mNodeManager->AddNode(Vector2(mCols[4], mRows[6]));
	mNodeManager->AddNode(Vector2(mCols[5], mRows[6]));
	mNodeManager->AddNode(Vector2(mCols[6], mRows[6]));
	mNodeManager->AddNode(Vector2(mCols[7], mRows[6]));

	mNodeManager->AddNode(Vector2(mCols[0], mRows[7]));
	mNodeManager->AddNode(Vector2(mCols[0] + Graphics::SCREEN_WIDTH * 0.05f, mRows[7]));
	mNodeManager->AddNode(Vector2(mCols[1], mRows[7]));
	mNodeManager->AddNode(Vector2(mCols[2], mRows[7]));
	mNodeManager->AddNode(Vector2(mCols[3], mRows[7]));
	mNodeManager->AddNode(Vector2(mCols[4], mRows[7]));
	mNodeManager->AddNode(Vector2(mCols[5], mRows[7]));
	mNodeManager->AddNode(Vector2(mCols[6], mRows[7]));
	mNodeManager->AddNode(Vector2(mCols[7] - Graphics::SCREEN_WIDTH * 0.05f, mRows[7]));
	mNodeManager->AddNode(Vector2(mCols[7], mRows[7]));

	mNodeManager->AddNode(Vector2(mCols[0], mRows[8]));
	mNodeManager->AddNode(Vector2(mCols[0] + Graphics::SCREEN_WIDTH * 0.05f, mRows[8]));
	mNodeManager->AddNode(Vector2(mCols[1], mRows[8]));
	mNodeManager->AddNode(Vector2(mCols[2], mRows[8]));
	mNodeManager->AddNode(Vector2(mCols[3], mRows[8]));
	mNodeManager->AddNode(Vector2(mCols[4], mRows[8]));
	mNodeManager->AddNode(Vector2(mCols[5], mRows[8]));
	mNodeManager->AddNode(Vector2(mCols[6], mRows[8]));
	mNodeManager->AddNode(Vector2(mCols[7] - Graphics::SCREEN_WIDTH * 0.05f, mRows[8]));
	mNodeManager->AddNode(Vector2(mCols[7], mRows[8]));

	mNodeManager->AddNode(Vector2(mCols[0], mRows[9]));
	mNodeManager->AddNode(Vector2(mCols[3], mRows[9]));
	mNodeManager->AddNode(Vector2(mCols[4], mRows[9]));
	mNodeManager->AddNode(Vector2(mCols[7], mRows[9]));



	//horixontal links
	mNodeManager->linkNodes(0,1);
	mNodeManager->linkNodes(1,2);

	mNodeManager->linkNodes(3,4);
	mNodeManager->linkNodes(4,5);

	mNodeManager->linkNodes(6,7);
	mNodeManager->linkNodes(7,8);
	mNodeManager->linkNodes(8,9);
	mNodeManager->linkNodes(9,10);
	mNodeManager->linkNodes(10,11);
	mNodeManager->linkNodes(11,12);
	mNodeManager->linkNodes(12,13);

	mNodeManager->linkNodes(14,15);

	mNodeManager->linkNodes(16,17);

	mNodeManager->linkNodes(18,19);

	mNodeManager->linkNodes(20,21);

	mNodeManager->linkNodes(22,23);
	//intentional gap here
	mNodeManager->linkNodes(24,25);

	mNodeManager->linkNodes(26,27);

	mNodeManager->linkNodes(28,29);

	mNodeManager->linkNodes(30,31);
	mNodeManager->linkNodes(31,32);
	mNodeManager->linkNodes(32,33);

	mNodeManager->linkNodes(34,35);
	mNodeManager->linkNodes(35,36);
	mNodeManager->linkNodes(36,37);
	
	mNodeManager->linkNodes(38,39);
	mNodeManager->linkNodes(39,40);
	mNodeManager->linkNodes(40, 41);

	mNodeManager->linkNodes(42, 43);

	mNodeManager->linkNodes(44,45);
	mNodeManager->linkNodes(45,46);
	mNodeManager->linkNodes(46,47);
	mNodeManager->linkNodes(47,48);
	mNodeManager->linkNodes(48,49);

	mNodeManager->linkNodes(50,51);

	mNodeManager->linkNodes(52,53);
	mNodeManager->linkNodes(53,54);

	mNodeManager->linkNodes(55,56);

	mNodeManager->linkNodes(57,58);

	mNodeManager->linkNodes(59,60);
	mNodeManager->linkNodes(60,61);

	mNodeManager->linkNodes(62,63);
	mNodeManager->linkNodes(63,64);
	mNodeManager->linkNodes(64,65);

	//vertical links

	mNodeManager->linkNodes(0,6);
	mNodeManager->linkNodes(1,7);
	mNodeManager->linkNodes(2,9);
	mNodeManager->linkNodes(3,10);
	mNodeManager->linkNodes(4,12);
	mNodeManager->linkNodes(5,13);

	mNodeManager->linkNodes(14,6);
	mNodeManager->linkNodes(15, 7);
	mNodeManager->linkNodes(16, 8);
	mNodeManager->linkNodes(19, 11);
	mNodeManager->linkNodes(20, 12);
	mNodeManager->linkNodes(21, 13);

	mNodeManager->linkNodes(23, 17);
	mNodeManager->linkNodes(24, 18);

	mNodeManager->linkNodes(26, 15);
	mNodeManager->linkNodes(27, 22);
	mNodeManager->linkNodes(28, 25);
	mNodeManager->linkNodes(29, 20);

	mNodeManager->linkNodes(30, 27);
	mNodeManager->linkNodes(33, 28);

	mNodeManager->linkNodes(35,26);
	mNodeManager->linkNodes(36,30);
	mNodeManager->linkNodes(39,33);
	mNodeManager->linkNodes(40,29);

	mNodeManager->linkNodes(42,34);
	mNodeManager->linkNodes(44,35);
	mNodeManager->linkNodes(46,37);
	mNodeManager->linkNodes(47,38);
	mNodeManager->linkNodes(49,40);
	mNodeManager->linkNodes(51,41);

	mNodeManager->linkNodes(53,43);
	mNodeManager->linkNodes(54,44);
	mNodeManager->linkNodes(55,45);
	mNodeManager->linkNodes(58,48);
	mNodeManager->linkNodes(59,49);
	mNodeManager->linkNodes(60,50);

	mNodeManager->linkNodes(62,52);
	mNodeManager->linkNodes(63,56);
	mNodeManager->linkNodes(64,57);
	mNodeManager->linkNodes(65,61);

	//ghost house
	
	mNodeManager->AddNode({ Graphics::SCREEN_WIDTH / 2,mRows[3] });

	mNodeManager->AddNode({ Graphics::SCREEN_WIDTH / 2,mRows[4]+5.0f });
	mNodeManager->AddNode({ Graphics::SCREEN_WIDTH / 2,mRows[4] + 30.0f });
	mNodeManager->AddNode({ Graphics::SCREEN_WIDTH / 2,mRows[4] - 25.0f });

	mNodeManager->AddNode({ (Graphics::SCREEN_WIDTH / 2) - 45.0f,mRows[4] + 5.0f });
	mNodeManager->AddNode({ (Graphics::SCREEN_WIDTH / 2) - 45.0f,mRows[4] + 30.0f});
	mNodeManager->AddNode({ (Graphics::SCREEN_WIDTH / 2) - 45.0f,mRows[4] - 25.0f });

	mNodeManager->AddNode({ (Graphics::SCREEN_WIDTH / 2) + 45.0f,mRows[4] + 5.0f });
	mNodeManager->AddNode({ (Graphics::SCREEN_WIDTH / 2) + 45.0f,mRows[4] + 30.0f });
	mNodeManager->AddNode({ (Graphics::SCREEN_WIDTH / 2) + 45.0f,mRows[4] - 25.0f });

	mNodeManager->linkNodes(72,70);
	mNodeManager->linkNodes(70, 71);

	mNodeManager->linkNodes(69, 67);
	mNodeManager->linkNodes(67, 68);

	mNodeManager->linkNodes(75, 73);
	mNodeManager->linkNodes(73, 74);

	mNodeManager->getNode(70)->AddConnection(mNodeManager->getNode(67));
	mNodeManager->getNode(73)->AddConnection(mNodeManager->getNode(67));
	mNodeManager->getNode(69)->AddConnection(mNodeManager->getNode(66));

	mNodeManager->linkNodes(23,66);
	mNodeManager->linkNodes(66, 24);


	//pellets
	mPellets.push_back(new Pellet({mCols[0], mRows[0] }));
	mPellets.push_back(new Pellet({ mCols[0] + ((mCols[1] - mCols[0]) / 5), mRows[0] }));
	mPellets.push_back(new Pellet({ mCols[0] + ((mCols[1] - mCols[0]) / 5) * 2, mRows[0] }));
	mPellets.push_back(new Pellet({ mCols[0] + ((mCols[1] - mCols[0]) / 5) * 3, mRows[0] }));
	mPellets.push_back(new Pellet({ mCols[0] + ((mCols[1] - mCols[0]) / 5) * 4, mRows[0] }));
	mPellets.push_back(new Pellet({ mCols[1], mRows[0] }));

	mPellets.push_back(new Pellet({ mCols[1], mRows[0] }));
	mPellets.push_back(new Pellet({ mCols[1] + ((mCols[3] - mCols[1]) / 6), mRows[0]}));
	mPellets.push_back(new Pellet({ mCols[1] + ((mCols[3] - mCols[1]) / 6) * 2, mRows[0]}));
	mPellets.push_back(new Pellet({ mCols[1] + ((mCols[3] - mCols[1]) / 6) * 3, mRows[0] }));
	mPellets.push_back(new Pellet({ mCols[1] + ((mCols[3] - mCols[1]) / 6) * 4, mRows[0] }));
	mPellets.push_back(new Pellet({ mCols[1] + ((mCols[3] - mCols[1]) / 6) * 5, mRows[0] }));
	mPellets.push_back(new Pellet({ mCols[3], mRows[0] }));
}