#ifndef __ITEMWEAPON_H__
#define __ITEMWEAPON_H__
#include "cocos2d.h"
#include "Item.h"

USING_NS_CC;

class ItemWeapon:public Item
{
public:
	int weaponTag;

	void init(int tag);
	
	virtual void pickUp(cocos2d::Scene* scene);
	virtual void nearBy(cocos2d::Scene* scene);
	virtual void clearTip(cocos2d::Scene* scene);

	virtual void throwDown(cocos2d::Scene* scene);
};

#endif 