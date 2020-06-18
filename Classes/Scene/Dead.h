#ifndef __DEAD_H__
#define __DEAD_H__

#include "cocos2d.h"
#include "BeginLevel.h"

USING_NS_CC;

class Dead :public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(Dead);
	
	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
};

#endif 