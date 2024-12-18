#include "Ghost.h"

Ghost::Ghost(PathNode* start) {

	mTimer = Timer::Instance();
	mNodeManager = NodeManager::Instance();

	mFrightened = new AnimatedTexture("PacmanAtlas.png", 584, 65, 16, 14, 2, 0.5f, AnimatedTexture::Horizontal);
	mFrightened->Parent(this);
	mFrightened->Position(Vect2_Zero);
	mFrightened->Scale(Vect2_One * 3);

	CurrentNode = start;

	AddCollider(new CircleCollider(20,true));
	AddCollider(new CircleCollider(20));
	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Hostile);

	Position(start->Position());

	mSpeed = 100;

	targetNode = CurrentNode->ClosestConnection(mScatterTarget);

	mState = Scatter;

}

void Ghost::Render() {

	mGhostTex->Render();
	//PhysEntity::Render();
	//Graphics::Instance()->DrawLine(Position().x,Position().y, target.x,target.y);
	//Graphics::Instance()->DrawLine(Position().x,Position().y, mScatterTarget.x, mScatterTarget.y);

}

Ghost::~Ghost() {

	mNodeManager = nullptr;
	mGhostTex = nullptr;

	delete mGhostUp;
	mGhostUp = nullptr;
	delete mGhostRight;
	mGhostRight = nullptr;
	delete mGhostDown;
	mGhostDown = nullptr;
	delete mGhostLeft;
	mGhostLeft = nullptr;

	delete mFrightened;
	mFrightened = nullptr;


}

void Ghost::Update() {

	HandleTexture();
	mGhostTex->Update();

	Vector2 dir = (targetNode->Position()-Position()).Normalized();
	Vector2 pos;

	if (mState != Frightened) {
		pos = Position() + dir * mSpeed * mTimer->DeltaTime();
	}
	else {
		pos = Position() + dir * (mSpeed / 2) * mTimer->DeltaTime();
	}
	

	Vector2 dist = targetNode->Position() - pos;

	if (InputManager::Instance()->KeyPressed(SDL_SCANCODE_M)) {
		if (mState == Scatter) {
			mState = Hunt;
		}
		else if (mState == Hunt) {
			mState = Scatter;
		}
	}

	if (InputManager::Instance()->KeyPressed(SDL_SCANCODE_F)) {
		if (mState != Frightened) {
			mState = Frightened;
		}
		else {
			mState = Scatter;
		}
	}

	if (targetNode != nullptr) {

		
		if (dist.MagnitudeSqr() < EPSILON * mSpeed / 25.0f) {
			Position(targetNode->Position());
			CurrentNode = targetNode;
			
			int randomIndex;

			switch (mState)
			{
			case Ghost::Scatter:
				targetNode = CurrentNode->ClosestConnection(mScatterTarget);
				break;
			case Ghost::Hunt:
				setNewTargetNode();
				break;
			case Ghost::Frightened:
				randomIndex = Random::Instance()->RandomRange(0,CurrentNode->ConnectionsSize()-1);
				targetNode = CurrentNode->GetConnectionByIndex(randomIndex);
				break;
			case Ghost::Dead:
				//todo
				break;
			default:
				break;
			}
			

		}
		else {
			Position(pos);
		}
	}

}

void Ghost::Hit(PhysEntity* entity) {

}

void Ghost::HandleTexture() {

	if (mState == Frightened) {
		mGhostTex = mFrightened;
		return;
	}

	Vector2 dir = (CurrentNode->Position() - targetNode->Position()).Normalized();


	if (dir == Vect2_Up) {
		mGhostTex = mGhostUp;
	}
	else if (dir == Vect2_Right) {
		mGhostTex = mGhostRight;
	}
	else if (dir == -Vect2_Up) {
		mGhostTex = mGhostDown;
	}
	else if (dir == -Vect2_Right) {
		mGhostTex = mGhostLeft;
	}
	else {
		std::cout << "ghost has no texture" << std::endl;
	}

}