#include "Hero.h"
#include "SimpleAudioEngine.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

bool Hero::init()
{
	object = Sprite::create("character/Hero.png");
	object->setAnchorPoint(Vec2(0.5 , 0.15));

	textureNomal = CCTextureCache::sharedTextureCache()->addImage("character/Hero.png");
	textureBack = CCTextureCache::sharedTextureCache()->addImage("character/HeroBack.png");

	curWeapon = -1;

	return true;
}