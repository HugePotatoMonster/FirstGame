#ifndef __BULLET_H__
#define __BULLET_H__
#include "cocos2d.h"

USING_NS_CC;

class Bullet
{
public:
	cocos2d::Sprite *object;
	double degree;
	int damage;
};

#endif 