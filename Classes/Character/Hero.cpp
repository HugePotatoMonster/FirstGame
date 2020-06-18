#include "Hero.h"
#include "SimpleAudioEngine.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Hero::Hero()
{
	object = Sprite::create("character/Hero.png");
	object->setAnchorPoint(Vec2(0.5 , 0.15));

	textureNomal = CCTextureCache::sharedTextureCache()->addImage("character/Hero.png");
	textureBack = CCTextureCache::sharedTextureCache()->addImage("character/HeroBack.png");

	curWeapon = -1;
	weaponNum = 0;

	hp = 10;
	hpSup = 10;

	damageUp = 0;

	hurtInterval = 60;
	hurtCount = 60;
}

void Hero::getItem(int tag)
{
	if (tag >= 0 && tag <= 3)
	{
		this->getWeapon(tag);
	}
	else
	{

	}
}

void Hero::getWeapon(int tag)
{
	if (weaponNum == 0)
	{
		heroWeapons[0] = tag;
		curWeapon = 0;
		weaponNum++;
	}
	else if (weaponNum == 1)
	{
		heroWeapons[1] = tag;
		curWeapon = 1;
		weaponNum++;
	}
	else if (weaponNum == 2)
	{
		heroWeapons[curWeapon] = tag;
	}
}
