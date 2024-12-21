#include "Ghost.h"

Ghost::Ghost(PathNode* start) {

	mTimer = Timer::Instance();
	mNodeManager = NodeManager::Instance();

	mFrightened1 = new AnimatedTexture("PacmanAtlas.png", 584, 65, 16, 14, 2, 0.5f, AnimatedTexture::Horizontal);
	mFrightened1->Parent(this);
	mFrightened1->Position(Vect2_Zero);
	mFrightened1->Scale(Vect2_One * 3);

	mFrightened2 = new AnimatedTexture("PacmanAtlas.png", 616, 65, 16, 14, 2, 0.5f, AnimatedTexture::Horizontal);
	mFrightened2->Parent(this);
	mFrightened2->Position(Vect2_Zero);
	mFrightened2->Scale(Vect2_One * 3);

	mGhostUpDead = new Texture("PacmanAtlas.png", 616, 79, 16, 14);
	mGhostUpDead->Parent(this);
	mGhostUpDead->Position(Vect2_Zero);
	mGhostUpDead->Scale(Vect2_One * 3);
	mGhostDownDead = new Texture("PacmanAtlas.png", 632, 79, 16, 14);
	mGhostDownDead->Parent(this);
	mGhostDownDead->Position(Vect2_Zero);
	mGhostDownDead->Scale(Vect2_One * 3);
	mGhostRightDead = new Texture("PacmanAtlas.png", 600, 79, 16, 14);
	mGhostRightDead->Parent(this);
	mGhostRightDead->Position(Vect2_Zero);
	mGhostRightDead->Scale(Vect2_One * 3);
	mGhostLeftDead = new Texture("PacmanAtlas.png", 584, 79, 16, 14);
	mGhostLeftDead->Parent(this);
	mGhostLeftDead->Position(Vect2_Zero);
	mGhostLeftDead->Scale(Vect2_One * 3);

	AddCollider(new CircleCollider(20,true));
	AddCollider(new CircleCollider(20));
	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Hostile);

	

	mSpeed = 100;

	mFlashSpeed = 0.5f;
	mFlashTime = 0.0f;
	mFrightenedDuration = 5.0f;
	mFrightenedTime = 0.0f;

	mStartNode = start;
	Reset();

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
	mTimer = nullptr;

	delete mGhostUp;
	mGhostUp = nullptr;
	delete mGhostRight;
	mGhostRight = nullptr;
	delete mGhostDown;
	mGhostDown = nullptr;
	delete mGhostLeft;
	mGhostLeft = nullptr;

	delete mFrightened1;
	mFrightened1 = nullptr;
	delete mFrightened2;
	mFrightened2 = nullptr;

	mStartNode = nullptr;
	CurrentNode = nullptr;
	targetNode = nullptr;


}

void Ghost::Update() {

	if (mState == Frightened) {
		mFrightenedTime += mTimer->DeltaTime();
		if (mFrightenedTime >= mFrightenedDuration) {
			State(Hunt);
			mFrightenedTime = 0;
			mFlashTime = 0;
		}
	}
	

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
			State(Hunt);
		}
		else if (mState == Hunt) {
			State(Scatter);
		}
	}

	if (InputManager::Instance()->KeyPressed(SDL_SCANCODE_F)) {
		if (mState != Frightened) {
			State(Frightened);
		}
	}

	if (InputManager::Instance()->KeyPressed(SDL_SCANCODE_Z)) {
		if (mState == Dead) {
			State(Hunt);
		}
		else {
			State(Dead);
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
				targetNode = CurrentNode->ClosestConnection(mStartNode->Position());
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

	if (mState == Dead) {
		return;
	}

	if ((!Player::Instance()->IsDying() && !Player::Instance()->isDead()) && dynamic_cast<Player*>(entity)) {//todo
		if (mState != Frightened) {
			Player::Instance()->Die();
		}
		else {
			mState = Dead;
		}
		
	}
}

void Ghost::HandleTexture() {

	if (mState == Frightened) {

		
		if (mFrightenedTime >= mFrightenedDuration/2) {
			mFlashTime += mTimer->DeltaTime();

			if (mFlashTime >= mFlashSpeed) {
				if (mGhostTex == mFrightened1) {
					mGhostTex = mFrightened2;
				}
				else {
					mGhostTex = mFrightened1;
				}
				mFlashTime = 0;
			}
		}
		else {
			mGhostTex = mFrightened1;
		}

		return;

	}



	Vector2 dir = (CurrentNode->Position() - targetNode->Position()).Normalized();


	if (dir == Vect2_Up) {

		mGhostTex = mState == Dead ? mGhostUpDead : mGhostUp;
	}
	else if (dir == Vect2_Right) {
		mGhostTex = mState == Dead ? mGhostRightDead : mGhostRight;
	}
	else if (dir == -Vect2_Up) {
		mGhostTex = mState == Dead ? mGhostDownDead : mGhostDown;
	}
	else if (dir == -Vect2_Right) {
		mGhostTex = mState == Dead ? mGhostLeftDead : mGhostLeft;
	}
	else {
		std::cout << "ghost has no texture" << std::endl;
	}

}

void Ghost::State( GhostState state) {

	if (state == mState) {
		return;
	}

	PathNode* temp = CurrentNode;
	CurrentNode = targetNode;
	targetNode = temp;

	mState = state;

}

void Ghost::Reset() {

	CurrentNode = mStartNode;
	targetNode = CurrentNode->ClosestConnection(mScatterTarget);
	Position(CurrentNode->Position());
	mState = Scatter;

}