#ifndef __HERO_H__
#define __HERO_H__

#include "Character.h"
#include "Weapon.h"

#include "cocos2d.h"

USING_NS_CC;

class Hero :public Character
{
public:
	Hero();
	int heroWeapons[2];
	int weaponNum;
	int curWeapon;
	int damageUp;

	int hurtInterval;
	int hurtCount;

	void getItem(int tag);
	void getWeapon(int tag);
};

#endif 