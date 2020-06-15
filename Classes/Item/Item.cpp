#include "Item.h"
#include "SimpleAudioEngine.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Item::Item()
{
	itemTag = -1;
}

bool Item::isNear(Vec2 target)
{
	int curX = object->getPositionX();
	int curY = object->getPositionY();
	int dx = abs(target.x - curX);
	int dy = abs(target.y - curY);
	if (dx < 50 && dy < 30)
		return true;
	else
		return false;
}