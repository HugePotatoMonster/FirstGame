#ifndef __BEGIN_LEVEL_H__
#define __BEGIN_LEVEL_H__

#include "Hero.h"
#include "cocos2d.h"

USING_NS_CC;

class BeginLevel :public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(BeginLevel);

	Hero hero;

	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event *event);
	bool isKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode);
	void keyPressedDuration(cocos2d::EventKeyboard::KeyCode code);

	virtual void onMouseMove(Event *event);

	virtual void update(float delta);

private:
	std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;
	TMXTiledMap* floor;
	TMXTiledMap* wall1;
	TMXTiledMap* wall2;
};

#endif 