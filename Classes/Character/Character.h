#ifndef __CHARACTER_H__
#define __CHARACTER_H__
#include "cocos2d.h"

USING_NS_CC;

class Character
{
public:
	cocos2d::Sprite *object;
	cocos2d::CCTexture2D* textureNomal;
	cocos2d::CCTexture2D* textureBack;

	Vec2 curPosition;

	virtual bool init()=0;

	void setPosition(Vec2 targrt);
	int checkState();
	void setState(int state);
};

#endif 