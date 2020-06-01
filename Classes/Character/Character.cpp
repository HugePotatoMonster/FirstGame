#include "Character.h"
#include "SimpleAudioEngine.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

int Character::checkState()
{
	if (object->getTexture() == textureNomal)
		return 0;
	if (object->getTexture() == textureBack)
		return 1;
	else
		return -1;
}

void Character::setState(int state)
{
	if (state == 0)
		object->setTexture(textureNomal);
	if (state == 1)
		object->setTexture(textureBack);
}

void Character::setPosition(Vec2 target)
{
	curPosition = target;
	object->setPosition(target);
}