#ifndef __WEAPON_H__
#define __WEAPON_H__
#include "cocos2d.h"

USING_NS_CC;

class Weapon
{
public:
	cocos2d::Sprite* object;

	virtual void attack()=0;
};

#endif 
