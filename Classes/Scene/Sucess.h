#ifndef __SUCESS_H__
#define __SUCESS_H__

#include "cocos2d.h"
#include "BeginLevel.h"

USING_NS_CC;

class Sucess :public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(Sucess);

	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
};

#endif 