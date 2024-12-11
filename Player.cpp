#include "Player.h"

Player* Player::sInstance = nullptr;


Player* Player::Instance() {

	if (sInstance == nullptr) {
		sInstance = new Player();
	}
	return sInstance;

}

void Player::Release() {
	delete sInstance;
	sInstance = nullptr;
}

Player::Player() {

	mTimer = Timer::Instance();
	mInputManager = InputManager::Instance();
	mAudioManager = AudioManager::Instance();


	mSpeed = 100;
	mWallHit = false;

	mTex = new Texture("PacmanAtlas.png", 473,1,12,12);
	mTex->Parent(this);
	mTex->Position(Vect2_Zero);
	mTex->Scale(Vect2_One*3);

	CurrentNode = NodeManager::Instance()->getNode(0);//TODO this is temp
	Position(CurrentNode->Position());
	targetNode = CurrentNode->ClosestConnection(Vect2_Up*Graphics::SCREEN_HEIGHT);

	Vector2 dir = (targetNode->Position() - Position()).Normalized();
	mNextTurn = dir;

}

Player::~Player() {

	delete mTex;
	mTex = nullptr;

}

void Player::Update() {

	if (mInputManager->KeyPressed(SDL_SCANCODE_W)) {
		mNextTurn = -Vect2_Up;
	}
	else if (mInputManager->KeyPressed(SDL_SCANCODE_A)) {
		mNextTurn = -Vect2_Right;
	}
	else if (mInputManager->KeyPressed(SDL_SCANCODE_S)) {
		mNextTurn = Vect2_Up;
	}
	else if (mInputManager->KeyPressed(SDL_SCANCODE_D)) {
		mNextTurn = Vect2_Right;
	}


	Vector2 dir;
	if (targetNode != CurrentNode) {
		dir = (targetNode->Position() - Position()).Normalized();
	}
	else {
		dir = Vect2_Zero;
	}

	Vector2 pos = Position() + dir * mSpeed * mTimer->DeltaTime();
	Vector2 dist = targetNode->Position() - pos;


	
	if (dist.MagnitudeSqr() < EPSILON * mSpeed / 25.0f) { //hitting walls is busted. pac man gets his pos set to nan for some reason.


		pos = targetNode->Position();
		
		CurrentNode = targetNode;
		targetNode = CurrentNode->GetConnectionbyDir(mNextTurn);

		if (targetNode == nullptr) {
			targetNode = CurrentNode;
		}

		
	}
	
	Position(pos);

}

void Player::Render() {
	mTex->Render();
}