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

	int hp;
	int hpSup;
	int checkState();
	void setState(int state);
	void changeHp(int delta);

};

#endif 