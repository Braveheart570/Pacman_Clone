#include "Player.h"

Player::Player() {

	mTimer = Timer::Instance();
	mInputManager = InputManager::Instance();
	mAudioManager = AudioManager::Instance();


	mSpeed = 100;

	mTex = new Texture("PacmanAtlas.png", 473,1,12,12);
	mTex->Parent(this);
	mTex->Position(Vect2_Zero);
	mTex->Scale(Vect2_One*3);

}

Player::~Player() {

	delete mTex;
	mTex = nullptr;

}

void Player::Update() {


	//need to lock the movment to the nodes, target node and current node system?


	if (mInputManager->KeyPressed(SDL_SCANCODE_W)) {
		Translate(-Vect2_Up*mSpeed*mTimer->DeltaTime());
	}
	else if (mInputManager->KeyPressed(SDL_SCANCODE_A)) {
		Translate(-Vect2_Right * mSpeed * mTimer->DeltaTime());
	}
	else if (mInputManager->KeyPressed(SDL_SCANCODE_S)) {
		Translate(Vect2_Up * mSpeed * mTimer->DeltaTime());
	}
	else if (mInputManager->KeyPressed(SDL_SCANCODE_D)) {
		Translate(Vect2_Right * mSpeed * mTimer->DeltaTime());
	}

}

void Player::Render() {
	mTex->Render();
}