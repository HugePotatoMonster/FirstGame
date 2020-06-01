#include "Item.h"
#include "SimpleAudioEngine.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

void Item::setPosition(Vec2 target)
{
	curPosition = target;
	object->setPosition(target);
}

bool Item::isNear(Vec2 target)
{
	int dx = abs(target.x - curPosition.x);
	int dy = abs(target.y - curPosition.y);
	if (dx < 50 && dy < 30)
		return true;
	else
		return false;
}