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

	mTex = new Texture("PacmanAtlas.png", 473,1,12,12);
	mTex->Parent(this);
	mTex->Position(Vect2_Zero);
	mTex->Scale(Vect2_One*3);

	CurrentNode = NodeManager::Instance()->getNode(0);//TODO this is temp
	Position(CurrentNode->Position());
	targetNode = CurrentNode->ClosestConnection(Vect2_Up*Graphics::SCREEN_HEIGHT);

}

Player::~Player() {

	delete mTex;
	mTex = nullptr;

}

void Player::Update() {

	Vector2 dir = (targetNode->Position() - Position()).Normalized();

	Vector2 pos = Position() + dir * mSpeed * mTimer->DeltaTime();

	Vector2 dist = targetNode->Position() - pos;

	
	if (dist.MagnitudeSqr() < EPSILON * mSpeed / 25.0f) {
		if (mInputManager->KeyPressed(SDL_SCANCODE_W)) {

			Position(targetNode->Position());
			CurrentNode = targetNode;
			targetNode = CurrentNode->GetConnectionbyDir(Vect2_Up*-1.0f);

		}
		else if (mInputManager->KeyPressed(SDL_SCANCODE_A)) {
			Position(targetNode->Position());
			CurrentNode = targetNode;
			targetNode = CurrentNode->GetConnectionbyDir(-Vect2_Right);
		}
		else if (mInputManager->KeyPressed(SDL_SCANCODE_S)) {
			Position(targetNode->Position());
			CurrentNode = targetNode;
			targetNode = CurrentNode->GetConnectionbyDir(Vect2_Up);
		}
		else if (mInputManager->KeyPressed(SDL_SCANCODE_D)) {
			Position(targetNode->Position());
			CurrentNode = targetNode;
			targetNode = CurrentNode->GetConnectionbyDir(Vect2_Right);
		}
	}
	
	Position(pos);
	

	

}

void Player::Render() {
	mTex->Render();
}