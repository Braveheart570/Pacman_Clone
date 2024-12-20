#include "WrapNode.h"

WrapNode::WrapNode(Vector2 pos, int index) : PathNode(pos,index){}

WrapNode::~WrapNode() {

	mWrapTo = nullptr;

}

void WrapNode::addWrapTo(WrapNode* wrapTo) {
	mWrapTo = wrapTo;
}

WrapNode* WrapNode::WrapTo() {
	return mWrapTo;
}