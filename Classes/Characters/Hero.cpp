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

	return true;
}

void Hero::setPosition(Vec2 target)
{
	curPosition = target;
	object->setPosition(target);
}