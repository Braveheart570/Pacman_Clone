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
	mDefaultSpeed = mSpeed;

	mFlashSpeed = 0.5f;
	mFlashTime = 0.0f;

	mStartNode = start;
	

	mHouseNodes.push_back(new PathNode(mStartNode->Position() - Vector2{ 0,25 }, 0));
	mHouseNodes.push_back(new PathNode(mStartNode->Position() + Vector2{ 0,25 }, 1));
	mHouseNodes[0]->AddConnection(mHouseNodes[1]);
	mHouseNodes[1]->AddConnection(mHouseNodes[0]);

	Reset();

}

void Ghost::Render() {
	HandleTexture();
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
	mCurrentNode = nullptr;
	mTargetNode = nullptr;

}

void Ghost::Update() {

	Vector2 dir = (mTargetNode->Position()-Position()).Normalized();
	Vector2 pos;


	//speed modifiers
	if (mState == Frightened) {
		pos = Position() + dir * (mDefaultSpeed / 2) * mTimer->DeltaTime();
	}
	else if (mState == Dead) {
		pos = Position() + dir * (mDefaultSpeed *1.5f) * mTimer->DeltaTime();
	}
	else {
		pos = Position() + dir * mSpeed * mTimer->DeltaTime();
	}
	
	if (mState != Dead) {
		if (mState == Frightened && !Player::Instance()->Energized()) {
			State(Scatter);
		}
		else if (mState != Frightened && Player::Instance()->Energized() && mCanFrighten) {
			State(Frightened);
		}
	}

	if (!Player::Instance()->Energized() && !mCanFrighten) {
		mCanFrighten = true;
	}

	//debug keys
	if (InputManager::Instance()->KeyPressed(SDL_SCANCODE_T)) {
		if (mState == Scatter) {
			State(Hunt);
		}
		else if (mState == Hunt) {
			State(Scatter);
		}
	}
	if (InputManager::Instance()->KeyPressed(SDL_SCANCODE_F)) {
		if (mState != Frightened) {
			Player::Instance()->Energize();
		}
	}

	Vector2 dist = mTargetNode->Position() - pos;
	if (dist.MagnitudeSqr() < EPSILON * mSpeed / 25.0f) {
		Position(mTargetNode->Position());
		mCurrentNode = mTargetNode;
			
		int randomIndex;
		if (mHousedState == Unhoused) {
			switch (mState)
			{
			case Ghost::Scatter:
				handleScatter();
				break;
			case Ghost::Hunt:
				setNewTargetNode();
				break;
			case Ghost::Frightened:
				randomIndex = Random::Instance()->RandomRange(0, mCurrentNode->ConnectionsSize() - 1);
				mTargetNode = mCurrentNode->GetConnectionByIndex(randomIndex);
				break;
			case Ghost::Dead:
				HandleDead();
				break;
			default:
				break;
			}
		}
		else{
			HandleHoused();
		}
		
			

	}
	else {
		Position(pos);
	}

	mGhostTex->Update();

}

void Ghost::handleScatter() {
	mTargetNode = mCurrentNode->ClosestConnection(mScatterTarget);
}

void Ghost::HandleHoused() {

	if (mHousedState == Housed) {
		mTargetNode = mCurrentNode->GetConnectionByIndex(0);
	}
	else if(mHousedState == Exiting) {
		mTargetNode = mStartNode;
		mHousedState = Unhoused;
	}
	
}

void Ghost::HandleDead() {
	if (mCurrentNode == mNodeManager->getNode(66)) {
		mTargetNode = mNodeManager->getNode(67);
	}
	else if (mCurrentNode == mNodeManager->getNode(67)) {
		mTargetNode = mCurrentNode->GetConnectionByIndex(0);
		State(Scatter, false);
		mCanFrighten = false;
	}
	else {
		mTargetNode = mCurrentNode->ClosestConnection(mNodeManager->getNode(66)->Position());
	}
	

}

void Ghost::Hit(PhysEntity* entity) {

	if (mState == Dead) {
		return;
	}

	if ((!Player::Instance()->IsDying() && !Player::Instance()->isDead()) && dynamic_cast<Player*>(entity)) {
		if (mState != Frightened) {
			Player::Instance()->Die();
		}
		else {
			State(Dead, false);
			Player::Instance()->GhostEaten();
			AudioManager::Instance()->PlaySFX("ghostEaten.wav",0);
		}
		
	}
}

void Ghost::HandleTexture() {

	if (mState == Frightened) {

		
		if (Player::Instance()->EnergizedTimeLeftPercent() >= 0.3f) {
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



	Vector2 dir = (mCurrentNode->Position() - mTargetNode->Position()).Normalized();


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

void Ghost::State( GhostState state, bool flip) {

	if (state == mState) {
		return;
	}

	if (flip) {
		PathNode* temp = mCurrentNode;
		mCurrentNode = mTargetNode;
		mTargetNode = temp;
	}

	mState = state;

}

Ghost::GhostState Ghost::State() {
	return mState;
}

void Ghost::Reset() {

	mCurrentNode = mStartNode;
	mTargetNode = mHouseNodes[0];
	Position(mStartNode->Position());
	mHousedState = Housed;
	mState = Scatter;
	mCanFrighten = true;
}

void Ghost::Unhouse() {
	if (mHousedState == Housed) {
		mHousedState = Exiting;
	}
}

Ghost::HousedState Ghost::HouseState() {
	return mHousedState;
}