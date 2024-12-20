#pragma once
#include "PathNode.h"

class WrapNode : public PathNode {

public:

	WrapNode(Vector2 pos, int index);
	~WrapNode();

	void addWrapTo(WrapNode* wrapTo);
	WrapNode* WrapTo();

private:

	WrapNode* mWrapTo;

};