#ifndef __BEGIN_LEVEL_H__
#define __BEGIN_LEVEL_H__
#include "cocos2d.h"

class BeginLevel :public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(BeginLevel);

	cocos2d::Sprite *hero;
	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event *event);
	virtual void update(float delta);
	bool isKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode);
	void keyPressedDuration(cocos2d::EventKeyboard::KeyCode code);

private:
	std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;

};

#endif 