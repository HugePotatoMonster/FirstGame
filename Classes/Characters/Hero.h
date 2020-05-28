#ifndef __HERO_H__
#define __HERO_H__

#include "Character.h"
#include "cocos2d.h"

USING_NS_CC;

class Hero :public Character
{
public:
	cocos2d::CCTexture2D* textureRun;
	cocos2d::CCTexture2D* textureBackRun;

	virtual bool init();
	virtual void setPosition(Vec2 targrt);
};

#endif 