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

	mPacmanUp = new AnimatedTexture("PacmanAtlas.png", 454,32,16,15,2,0.5f,AnimatedTexture::Horizontal);
	mPacmanUp->Parent(this);
	mPacmanUp->Position(Vect2_Zero);
	mPacmanUp->Scale(Vect2_One*3);

	mPacmanRight = new AnimatedTexture("PacmanAtlas.png", 454, 16, 16, 15, 2, 0.5f, AnimatedTexture::Horizontal);
	mPacmanRight->Parent(this);
	mPacmanRight->Position(Vect2_Zero);
	mPacmanRight->Scale(Vect2_One * 3);

	mPacmanDown = new AnimatedTexture("PacmanAtlas.png", 454, 48, 16, 15, 2, 0.5f, AnimatedTexture::Horizontal);
	mPacmanDown->Parent(this);
	mPacmanDown->Position(Vect2_Zero);
	mPacmanDown->Scale(Vect2_One * 3);

	mPacmanLeft = new AnimatedTexture("PacmanAtlas.png", 454, 0, 16, 15, 2, 0.5f, AnimatedTexture::Horizontal);
	mPacmanLeft->Parent(this);
	mPacmanLeft->Position(Vect2_Zero);
	mPacmanLeft->Scale(Vect2_One * 3);

	mPacmanStopped = new Texture("PacmanAtlas.png", 486, 0, 16, 15);
	mPacmanStopped->Parent(this);
	mPacmanStopped->Position(Vect2_Zero);
	mPacmanStopped->Scale(Vect2_One * 3);

	AddCollider(new CircleCollider(20,true));
	AddCollider(new CircleCollider(20));
	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Friendly);

	CurrentNode = NodeManager::Instance()->getNode(61);//TODO this is temp
	Position(CurrentNode->Position());
	targetNode = CurrentNode->ClosestConnection(Vect2_Up*Graphics::SCREEN_HEIGHT);

	mNextTurn = Dir();

}

Player::~Player() {

	mPacmanTex = nullptr;

	delete mPacmanUp;
	mPacmanUp = nullptr;
	delete mPacmanRight;
	mPacmanRight = nullptr;
	delete mPacmanDown;
	mPacmanDown = nullptr;
	delete mPacmanLeft;
	mPacmanLeft = nullptr;

	delete mPacmanDeath;
	mPacmanDeath = nullptr;

	delete mPacmanStopped;
	mPacmanStopped = nullptr;

}

void Player::Update() {
	HandleTexture();
	if (mPacmanTex != nullptr) {
		mPacmanTex->Update();
	}
	

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
	if (mPacmanTex != nullptr) {
		mPacmanTex->Render();
	}
	else {
		mPacmanStopped->Render();
	}
	
	//PhysEntity::Render();
}

void Player::Hit(PhysEntity* other) {

	if (false) {//todo
		std::cout << "Ghost touched player" << std::endl;
	}

}

void Player::HandleTexture() {


	Vector2 dir = (CurrentNode->Position() - targetNode->Position()).Normalized();

	if (dir == Vect2_Up) {
		mPacmanTex = mPacmanUp;
	}
	else if (dir == Vect2_Right) {
		mPacmanTex = mPacmanRight;
	}
	else if (dir == -Vect2_Up) {
		mPacmanTex = mPacmanDown;
	}
	else if (dir == -Vect2_Right) {
		mPacmanTex = mPacmanLeft;
	}
	else {
		mPacmanTex = nullptr;
	}

}