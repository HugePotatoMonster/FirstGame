#ifndef __ITEM_H__
#define __ITEM_H__
#include "cocos2d.h"

USING_NS_CC;

class Item
{
public:
	cocos2d::Sprite *object;
	cocos2d::Label *label;
	Vec2 curPosition;
	bool isOnMap;

	virtual void setPosition(Vec2 target);
	virtual bool isNear(Vec2 target);

	virtual void pickUp(cocos2d::Scene* scene) = 0;
	virtual void nearBy(cocos2d::Scene* scene) = 0;
	virtual void clearTip(cocos2d::Scene* scene) = 0;
};

#endif 