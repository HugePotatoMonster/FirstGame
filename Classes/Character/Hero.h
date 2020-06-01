#ifndef __HERO_H__
#define __HERO_H__

#include "Character.h"
#include "Weapon.h"

#include "cocos2d.h"

USING_NS_CC;

class Hero :public Character
{
public:
	int weapons[2];
	int curWeapon;

	virtual bool init();
};

#endif 