#include "BeginLevel.h"
#include "SimpleAudioEngine.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* BeginLevel::createScene()
{
	return BeginLevel::create();
}

//按下键盘时
void BeginLevel::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	keys[keyCode] = true;
	if (keyCode == EventKeyboard::KeyCode::KEY_E)
	{
		std::vector<ItemWeapon>::iterator itr = itemWeapons.begin();
		for (; itr < itemWeapons.end(); itr++)
		{
			if (itr->isNear(hero.curPosition))
				itr->pickUp(this);
		}
	}
}

//松开键盘时
void BeginLevel::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
	keys[keyCode] = false;
}

//检测某个键是否被按住
bool BeginLevel::isKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode) {
	if (keys[keyCode]) {
		return true;
	}
	else {
		return false;
	}
}

//如果某个键正被按住
void BeginLevel::keyPressedDuration(cocos2d::EventKeyboard::KeyCode code) {
	int offsetX = 0, offsetY = 0;
	hero.curPosition = hero.object->getPosition() ;
	auto layer1 = wall1->getLayer("layer1");
	auto layer2 = wall2->getLayer("layer1");
	switch (code) {
	case cocos2d::EventKeyboard::KeyCode::KEY_A:
		offsetX = -4;
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_D:
		offsetX = 4;
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_W:
		offsetY = 4;
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_S:
		offsetY = -4;
		break;
	default:
		offsetY = offsetX = 0;
		break;
	}
	if (offsetX > 0)
		hero.curPosition.x += 20;
	else if (offsetX < 0)
		hero.curPosition.x -= 20;
	int tarX = hero.curPosition.x + 5*offsetX, tarY = hero.curPosition.y + 5*offsetY;
	int tileX = tarX / 40, tileY =  tarY / 40;
	if ( layer1->getTileAt(Vec2(tileX, tileY))!= 0 || layer2->getTileAt(Vec2(tileX, tileY)) != 0 )
	{
		offsetX = 0;
		offsetY = 0;
	}
	auto moveBy = MoveBy::create(0.1, Vec2( offsetX, offsetY));
	hero.object->runAction(moveBy);
}

//鼠标移动时
void BeginLevel::onMouseMove(Event *event)
{
	EventMouse* mouse = (EventMouse*)event;
	int mouseX = mouse->getCursorX() , mouseY = mouse->getCursorY();
	if (mouseX < hero.curPosition.x )
		hero.setState(1);
	else if ( mouseX > hero.curPosition.y)
		hero.setState(0);
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
	if (isKeyPressed(right)) {
		keyPressedDuration(right);
	}
	if (isKeyPressed(up)) {
		keyPressedDuration(up);
	}
	if (isKeyPressed(down)) {
		keyPressedDuration(down);
	}

	std::vector<ItemWeapon>::iterator itr = itemWeapons.begin();
	for (; itr < itemWeapons.end(); itr++)
	{
		if (itr->isNear(hero.curPosition))
			itr->nearBy(this);
		else
			itr->clearTip(this);
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
	Vec2 mid = Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);

	floor = TMXTiledMap::create("levels/BeginLevel/Floor.tmx");
	this->addChild( floor , 0 );

	wall1 = TMXTiledMap::create("levels/BeginLevel/Wall1.tmx");
	this->addChild( wall1 , 1 );
	wall2 = TMXTiledMap::create("levels/BeginLevel/Wall2.tmx");
	this->addChild( wall2 , 50 );

	hero.init();
	hero.setPosition(mid);
	this->addChild( hero.object , 10 );

	rifle.init(1);
	rifle.object = Sprite::create("weapon/Rifle.png");
	rifle.object->setAnchorPoint(Vec2(0.75,0.6));
	rifle.setPosition(Vec2(200,500));
	itemWeapons.push_back(rifle);
	this->addChild( rifle.object , 5 , rifle.weaponTag );

	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(BeginLevel::onKeyPressed, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(BeginLevel::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

	auto mouseListener = EventListenerMouse::create();
	mouseListener->onMouseMove = CC_CALLBACK_1(BeginLevel::onMouseMove, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

	this->scheduleUpdate();

	return true;
}