#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "Character.h"

#include "cocos2d.h"

USING_NS_CC;

class Enemy :public Character
{
public:
	int enemyTag;

	int dirInterval;
	int dirCount;

	int degree;
};

#endif 