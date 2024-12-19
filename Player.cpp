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

Vector2 Player::Dir() {

	Vector2 retVal = (targetNode->Position() - Position()).Normalized();

	if (retVal.x == retVal.x && retVal.y == retVal.y) { //nan check. comparing a nan to itself will return false.
		return retVal;
	}
	else {
		return Vect2_Zero;
	}

	

}

Vector2 Player::nextTurn() {
	return mNextTurn;
}

int Player::Score() {
	return mScore;
}

void Player::AddScore(int change) {
	mScore += change;
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

	AddCollider(new CircleCollider(20,true));
	AddCollider(new CircleCollider(20));
	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Friendly);

	CurrentNode = NodeManager::Instance()->getNode(61);//TODO this is temp
	Position(CurrentNode->Position());
	targetNode = CurrentNode->ClosestConnection(Vect2_Up*Graphics::SCREEN_HEIGHT);

	mNextTurn = Dir();

}

Player::~Player() {

	delete mTex;
	mTex = nullptr;

}

void Player::Update() {

	//movement keys
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


	Vector2 dir = Dir();

	if (-mNextTurn == dir) {
		PathNode* temp = targetNode;
		targetNode = CurrentNode;
		CurrentNode = temp;
		dir = -dir;
	}


	Vector2 pos = Position() + dir * mSpeed * mTimer->DeltaTime(); // new position
	Vector2 dist = targetNode->Position() - pos;
	
	if (dist.MagnitudeSqr() < EPSILON * mSpeed / 25.0f) { //check if reached target


		pos = targetNode->Position(); // set position to target
		
		CurrentNode = targetNode;

		targetNode = CurrentNode->GetConnectionbyDir(mNextTurn); //attempt to find new target

		
		if (targetNode == nullptr && (dir == mNextTurn || dir == Vect2_Zero)) { //if there is no node in this direction and we are going straight then the player should stop
			targetNode = CurrentNode;
		}
		else if (targetNode == nullptr) { // if we cannot go the chosen direction and we are not going straight then continue straight.
			targetNode = CurrentNode->GetConnectionbyDir(dir);

			if (targetNode == nullptr) {// if we cannot go straight then stop
				targetNode = CurrentNode;
			}
		}

		
	}
	
	Position(pos);

}

void Player::Render() {
	mTex->Render();
	PhysEntity::Render();
}

void Player::Hit(PhysEntity* other) {

	if (false) {//todo
		std::cout << "Ghost touched player" << std::endl;
	}

}