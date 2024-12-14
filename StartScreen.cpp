#include "StartScreen.h"

startScreen::startScreen() {

	mTimer = Timer::Instance();
	mInputManager = InputManager::Instance();

	std::string redName = "SHADOW";
	std::string pinkName = "SPEEDY";
	std::string blueName = "BASHFUL";
	std::string orangeName = "POKEY";
	redName = redName + std::string(10 - redName.length(),'-') + "\"BLINKY\"";
	pinkName = pinkName + std::string(11 - pinkName.length(),'-') + "\"PINKY\"";
	blueName = blueName + std::string(12 - blueName.length(), '-') + "\"INKY\"";
	orangeName = orangeName + std::string(11 - orangeName.length(),'-') + "\"CLYDE\"";


	mOneUplabel = new Texture("1UP", "emulogic.ttf", 20, {255,255,255});
	HandleEntityInit(mOneUplabel, {100,25});
	mHighScoreLabel = new Texture("HIGH SCORE", "emulogic.ttf", 20, { 255,255,255 });
	HandleEntityInit(mHighScoreLabel, {Graphics::SCREEN_WIDTH/2,25});
	mTwoUpLabel = new Texture("2UP", "emulogic.ttf", 20, { 255,255,255 });
	HandleEntityInit(mTwoUpLabel,{Graphics::SCREEN_WIDTH-100,25});

	mPlayerOneScoreboard = new Scoreboard();
	HandleEntityInit(mPlayerOneScoreboard, mOneUplabel->Position() + Vector2(0,30));
	mHighScoreboard = new Scoreboard();
	HandleEntityInit(mHighScoreboard, mHighScoreLabel->Position() + Vector2(0, 30));
	mPlayerTwoScoreBoard = new Scoreboard();
	HandleEntityInit(mPlayerTwoScoreBoard, mTwoUpLabel->Position() + Vector2(0, 30));

	GhostTableLabel = new Texture("CHARACTER / NICKNAME", "emulogic.ttf", 20, {255,255,255});
	HandleEntityInit(GhostTableLabel, { (Graphics::SCREEN_WIDTH / 2)+50, 220 });

	mRedGhost = new Texture("PacmanAtlas.png", 457, 65, 14, 14);
	HandleEntityInit(mRedGhost, {100,300},Vect2_One*3);
	mRedGhostAnim = new AnimatedTexture("PacmanAtlas.png", 456, 65, 16, 14, 2, 0.5f, AnimatedTexture::Horizontal);
	HandleEntityInit(mRedGhostAnim, { 200,600 }, Vect2_One * 3);
	mRedGhostLabel = new Texture(redName, "emulogic.ttf", 20, { 255,0,0 });
	HandleEntityInit(mRedGhostLabel, { (Graphics::SCREEN_WIDTH / 2)+50,300 });

	mPinkGhost = new Texture("PacmanAtlas.png", 457, 81, 14, 14);
	HandleEntityInit(mPinkGhost, { 100,350 }, Vect2_One * 3);
	mPinkGhostAnim = new AnimatedTexture("PacmanAtlas.png", 456, 81, 16, 14, 2, 0.5f, AnimatedTexture::Horizontal);
	HandleEntityInit(mPinkGhostAnim, { 250,600 }, Vect2_One * 3);
	mPinkGhostLabel = new Texture(pinkName, "emulogic.ttf", 20, { 255,183,255 });
	HandleEntityInit(mPinkGhostLabel, { (Graphics::SCREEN_WIDTH / 2) + 50,350 });

	mBlueGhost = new Texture("PacmanAtlas.png", 457, 97, 14, 14);
	HandleEntityInit(mBlueGhost, { 100,400 }, Vect2_One * 3);
	mBlueGhostAnim = new AnimatedTexture("PacmanAtlas.png", 456, 97, 16, 14, 2, 0.5f, AnimatedTexture::Horizontal);
	HandleEntityInit(mBlueGhostAnim, { 300,600 }, Vect2_One * 3);
	mBlueGhostLabel = new Texture(blueName, "emulogic.ttf", 20, { 0,255,255 });
	HandleEntityInit(mBlueGhostLabel, { (Graphics::SCREEN_WIDTH / 2) + 50,400 });

	mOrangeGhost = new Texture("PacmanAtlas.png", 457, 113, 14, 14);
	HandleEntityInit(mOrangeGhost, { 100,450 }, Vect2_One * 3);
	mOrangeGhostAnim = new AnimatedTexture("PacmanAtlas.png", 456, 113, 16, 14, 2, 0.5f, AnimatedTexture::Horizontal);
	HandleEntityInit(mOrangeGhostAnim, { 350,600 }, Vect2_One * 3);
	mOrangeGhostLabel = new Texture(orangeName, "emulogic.ttf", 20, { 255,183,81 });
	HandleEntityInit(mOrangeGhostLabel, { (Graphics::SCREEN_WIDTH / 2) + 50,450 });

	mPacmanLeft = new AnimatedTexture("PacmanAtlas.png", 457, 1, 12, 13,2,0.5f, AnimatedTexture::Horizontal);
	HandleEntityInit(mPacmanLeft, { 100,600 }, Vect2_One * 3);
	mPacmanRight = new AnimatedTexture("PacmanAtlas.png", 474, 17, 12, 13, 2, 0.5f, AnimatedTexture::Horizontal);
	HandleEntityInit(mPacmanRight, { 150,600 }, Vect2_One * 3);

	mPowerPellet = new Texture("PacmanAtlas.png", 8, 24, 8, 8);
	HandleEntityInit(mPowerPellet, { (Graphics::SCREEN_WIDTH / 2)-50,750 }, Vect2_One * 3);
	mPellet = new Texture("PacmanAtlas.png", 11, 11, 2, 2);
	HandleEntityInit(mPellet, { (Graphics::SCREEN_WIDTH / 2)-50,700 }, Vect2_One * 3);

	mPowerPelletPTS = new Texture("50 PTS", "emulogic.ttf", 15, {255,255,255});
	HandleEntityInit(mPowerPelletPTS,mPowerPellet->Position()+Vector2(80,0));
	mPelletPTS = new Texture("10 PTS", "emulogic.ttf", 15, { 255,255,255 });
	HandleEntityInit(mPelletPTS, mPellet->Position() + Vector2(80, 0));

	mNamcoLabel = new Texture("NAMCO", "emulogic.ttf", 40, {255,0,0});
	HandleEntityInit(mNamcoLabel, {Graphics::SCREEN_WIDTH/2,900});
}

startScreen::~startScreen() {

	mTimer = nullptr;
	mInputManager = nullptr;

	delete mOneUplabel;
	mOneUplabel = nullptr;
	delete mHighScoreLabel;
	mHighScoreLabel = nullptr;
	delete mTwoUpLabel;
	mTwoUpLabel = nullptr;

	delete mPlayerOneScoreboard;
	mPlayerOneScoreboard = nullptr;
	delete mHighScoreboard;
	mHighScoreboard = nullptr;
	delete mPlayerTwoScoreBoard;
	mPlayerTwoScoreBoard = nullptr;

	delete GhostTableLabel;
	GhostTableLabel = nullptr;

	delete mRedGhost;
	mRedGhost = nullptr;
	delete mRedGhostAnim;
	mRedGhostAnim = nullptr;
	delete mRedGhostLabel;
	mRedGhostLabel = nullptr;

	delete mPinkGhost;
	mPinkGhost = nullptr;
	delete mPinkGhostAnim;
	mPinkGhostAnim = nullptr;
	delete mPinkGhostLabel;
	mPinkGhostLabel = nullptr;

	delete mBlueGhost;
	mBlueGhost = nullptr;
	delete mBlueGhostAnim;
	mBlueGhostAnim = nullptr;
	delete mBlueGhostLabel;
	mBlueGhostLabel = nullptr;

	delete mOrangeGhost;
	mOrangeGhost = nullptr;
	delete mOrangeGhostAnim;
	mOrangeGhostAnim = nullptr;
	delete mOrangeGhostLabel;
	mOrangeGhostLabel = nullptr;

	delete mPacmanLeft;
	mPacmanLeft = nullptr;
	delete mPacmanRight;
	mPacmanRight = nullptr;

	delete mPowerPellet;
	mPowerPellet = nullptr;
	delete mPellet;
	mPellet = nullptr;

	delete mPowerPelletPTS;
	mPowerPelletPTS = nullptr;
	delete mPelletPTS;
	mPelletPTS = nullptr;

	delete mNamcoLabel;
	mNamcoLabel = nullptr;

}


void startScreen::Update() {

	mRedGhostAnim->Update();
	mPinkGhostAnim->Update();
	mBlueGhostAnim->Update();
	mOrangeGhostAnim->Update();

	mPacmanLeft->Update();
	mPacmanRight->Update();

}

void startScreen::Render() {

	mOneUplabel->Render();
	mHighScoreLabel->Render();
	mTwoUpLabel->Render();

	mPlayerOneScoreboard->Render();
	mHighScoreboard->Render();
	mPlayerTwoScoreBoard->Render();

	GhostTableLabel->Render();

	mRedGhost->Render();
	mRedGhostAnim->Render();
	mRedGhostLabel->Render();

	mPinkGhost->Render();
	mPinkGhostAnim->Render();
	mPinkGhostLabel->Render();

	mBlueGhost->Render();
	mBlueGhostAnim->Render();
	mBlueGhostLabel->Render();

	mOrangeGhost->Render();
	mOrangeGhostAnim->Render();
	mOrangeGhostLabel->Render();

	mPacmanLeft->Render();
	mPacmanRight->Render();

	mPowerPellet->Render();
	mPellet->Render();

	mPowerPelletPTS->Render();
	mPelletPTS->Render();

	mNamcoLabel->Render();

}



void startScreen::HandleEntityInit(GameEntity* tex, Vector2 pos, Vector2 scale) {
	
	tex->Parent(this);
	tex->Position(pos);
	tex->Scale(scale);

}