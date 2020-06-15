#ifndef __ITEM_H__
#define __ITEM_H__
#include "cocos2d.h"

USING_NS_CC;

class Item
{
public:
	Item();
	cocos2d::Sprite *object;
	int itemTag;

	virtual bool isNear(Vec2 target);
};

#endif 