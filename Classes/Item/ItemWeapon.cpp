#include "ItemWeapon.h"
#include "SimpleAudioEngine.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

void ItemWeapon::init(int tag)
{
	isOnMap = true;
	weaponTag = tag;
}

void ItemWeapon::nearBy(cocos2d::Scene* scene)
{
	if (isOnMap)
	{
		if (weaponTag == 1)
			label = Label::createWithSystemFont("R i f l e", "Arial", 16);
		label->setPosition(Vec2(curPosition.x, curPosition.y + 20));
		scene->addChild(label, 5, weaponTag + 100);
	}
}

void ItemWeapon::pickUp(cocos2d::Scene* scene)
{
	scene->removeChildByTag(weaponTag + 100);
	scene->removeChildByTag(weaponTag);
	isOnMap = false;
}

void ItemWeapon::throwDown(cocos2d::Scene* scene)
{

}

void ItemWeapon::clearTip(cocos2d::Scene* scene)
{
	scene->removeChildByTag(weaponTag+100);
}