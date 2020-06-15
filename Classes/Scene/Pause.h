#ifndef __PAUSE_H__
#define __PAUSE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

class Pause :public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(Pause);


	void exitGame(cocos2d::Ref* Sender);
	void continueGame(cocos2d::Ref* Sender);
};

#endif 