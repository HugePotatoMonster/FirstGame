#include "Sucess.h"
#include "SimpleAudioEngine.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* Sucess::createScene()
{
	return Sucess::create();
}

void Sucess::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_SPACE)
	{
		Director::sharedDirector()->replaceScene(BeginLevel::createScene());
	}

}

bool Sucess::init()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto background = Sprite::create("windows/Success.png");
	background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(background);

	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(Sucess::onKeyPressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

	return true;
}
