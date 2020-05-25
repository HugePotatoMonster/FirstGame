#include "BeginLevel.h"
#include "SimpleAudioEngine.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* BeginLevel::createScene()
{
	return BeginLevel::create();
}

void BeginLevel::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	keys[keyCode] = true;
}
void BeginLevel::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
	keys[keyCode] = false;
}

void BeginLevel::keyPressedDuration(cocos2d::EventKeyboard::KeyCode code) {
	int offsetX = 0, offsetY = 0;
	switch (code) {
	case cocos2d::EventKeyboard::KeyCode::KEY_A:
		offsetX = -5;
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_D:
		offsetX = 5;
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_W:
		offsetY = 5;
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_S:
		offsetY = -5;
		break;
	default:
		offsetY = offsetX = 0;
		break;
	}
	auto moveTo = MoveTo::create(0.3, Vec2(hero->getPositionX() + offsetX, hero->getPositionY() + offsetY));
	hero->runAction(moveTo);
}

void BeginLevel::update(float delta) {
	Node::update(delta);
	auto left = EventKeyboard::KeyCode::KEY_A;
	auto right = EventKeyboard::KeyCode::KEY_D;
	auto up = EventKeyboard::KeyCode::KEY_W;
	auto down = EventKeyboard::KeyCode::KEY_S;
	if (isKeyPressed(left)) {
		keyPressedDuration(left);
	}
	else if (isKeyPressed(right)) {
		keyPressedDuration(right);
	}
	else if (isKeyPressed(up)) {
		keyPressedDuration(up);
	}
	else if (isKeyPressed(down)) {
		keyPressedDuration(down);
	}
}

bool BeginLevel::isKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode) {
	if (keys[keyCode]) {
		return true;
	}
	else {
		return false;
	}
}

bool BeginLevel::init()
{

	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto floor = TMXTiledMap::create("levels/BeginLevel/Floor.tmx");
	this->addChild( floor, 0 );

	auto wall = TMXTiledMap::create("levels/BeginLevel/Wall.tmx");
	this->addChild( wall , 1 );

	hero = Sprite::create("character/Hero.png");
	hero->setPosition(Vec2(visibleSize.width / 2 + origin.x , visibleSize.height / 2 + origin.y ));
	this->addChild( hero , 10 );

	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(BeginLevel::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(BeginLevel::onKeyReleased, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	this->scheduleUpdate();

	return true;
}