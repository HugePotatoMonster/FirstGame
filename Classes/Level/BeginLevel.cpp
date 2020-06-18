#include "BeginLevel.h"
#include "SimpleAudioEngine.h"
#include "SimpleAudioEngine.h"

#define PI (acos(-1))

USING_NS_CC;

Scene* BeginLevel::createScene()
{
	return BeginLevel::create();
}

//创建一个物品
void BeginLevel::createItem(int tag, Vec2 position)
{
	Item temp;
	temp.object = Sprite::createWithTexture(pictures[tag]);
	temp.object->setPosition(position);
	temp.itemTag = tag;
	items.push_back(temp);
	std::vector<Item>::iterator itr = items.end() - 1;
	this->addChild( itr->object , 10 , tag );
}

//创建一个子弹
void BeginLevel::createBullet(int tag, Vec2 position, double deg, int dam)
{
	Bullet temp;
	temp.object = Sprite::createWithTexture(bulletPictures[tag]);
	temp.object->setPosition(position);
	temp.degree = deg;
	temp.damage = dam;
	bullets.push_back(temp);
	std::vector<Bullet>::iterator itr = bullets.end() - 1;
	this->addChild(itr->object, 15 , tag);
}

//
void BeginLevel::weaponUpdate()
{
	for (int i = 0; i < 4; i++)
	{
		if (weaponCount[i] < weaponInterval[i])
			weaponCount[i]++;
	}
}

//
bool BeginLevel::isWeapon(int tag)
{
	return (tag >= 0 && tag <= 3);
}

//按下键盘时
void BeginLevel::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	keys[keyCode] = true;
	if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_R)
	{
		Director::sharedDirector()->pushScene(Pause::createScene());
	}
	if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_E)
	{
		if (!items.empty())
		{
			std::vector<Item>::iterator itr = items.begin();
			for (; itr < items.end(); itr++)
			{
				if ( itr->isNear( hero.object->getPosition() ) )
				{
					//移除地面物品
					this->removeChildByTag(itr->itemTag);
					int curNum = hero.weaponNum;
					int curWea = hero.heroWeapons[hero.curWeapon];
					hero.getItem(itr->itemTag);
					bool flag = isWeapon(itr->itemTag);
					//若手中无武器，新建武器精灵
					if (flag && curNum==0 )
					{
						weapon = Sprite::createWithTexture(pictures[itr->itemTag]);
						weapon->setPosition( Vec2(hero.object->getPositionX(),hero.object->getPositionY()+5));
						this->addChild(weapon, 25);
					}
					//若手中有武器，改变武器精灵图片
					else if (flag && curNum==1)
					{
						weapon->setTexture(pictures[hero.heroWeapons[hero.curWeapon]]);
						CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/Portal.mp3");
						createItem( 4 , Vec2(750,450) );
					}
					else if (flag && curNum == 2)
					{
						weapon->setTexture(pictures[hero.heroWeapons[hero.curWeapon]]);
						createItem( curWea , hero.object->getPosition() );
					}
					else if (itr->itemTag == 4)
					{
						CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/Portal.mp3");
						UserDefault::sharedUserDefault()->setIntegerForKey("hp",hero.hp);
						UserDefault::sharedUserDefault()->setIntegerForKey("curWeapon", hero.curWeapon);
						UserDefault::sharedUserDefault()->setIntegerForKey("weapon0", hero.heroWeapons[0]);
						UserDefault::sharedUserDefault()->setIntegerForKey("weapon1", hero.heroWeapons[1]);
						UserDefault::sharedUserDefault()->setIntegerForKey("damageUp", hero.damageUp);
						UserDefault::sharedUserDefault()->setIntegerForKey("count", count);
						UserDefault::sharedUserDefault()->setFloatForKey("vol", CocosDenshion::SimpleAudioEngine::getInstance() ->getBackgroundMusicVolume());
						CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
						Director::getInstance()->replaceScene(FirstLevel::createScene());
					}
					//从地面物品vector中去除
					items.erase(itr);
					break;
				}
			}
		}
	}
	if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_Q && hero.weaponNum==2)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/Q.mp3");
		hero.curWeapon = 1 - hero.curWeapon;
		weapon ->setTexture(pictures[hero.heroWeapons[hero.curWeapon]]);
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
	int curX = hero.object->getPositionX();
	int curY = hero.object->getPositionY();
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
		curX += 20;
	else if (offsetX < 0)
		curX -= 20;
	int tarX = curX + 5*offsetX, tarY = curY + 5*offsetY;
	int tileX = tarX / 40, tileY =  (720-tarY) / 40;
	if ( layer1->getTileAt(Vec2(tileX, tileY))!= 0 || layer2->getTileAt(Vec2(tileX, tileY)) != 0 )
	{
		offsetX = 0;
		offsetY = 0;
	}
	auto moveBy1 = MoveBy::create(0.1, Vec2( offsetX, offsetY));
	auto moveBy2 = MoveBy::create(0.1, Vec2(offsetX, offsetY));
	auto moveBy3 = MoveBy::create(0.1, Vec2(offsetX, offsetY));
	auto moveBy4 = MoveBy::create(0.1, Vec2(offsetX, offsetY));
	auto moveBy5 = MoveBy::create(0.1, Vec2(-offsetX, -offsetY));
	hero.object->runAction(moveBy1);
	if (hero.weaponNum > 0)
		weapon->runAction(moveBy2);
	blood->runAction(moveBy3);
	bloodBack->runAction(moveBy4);
	this->runAction(moveBy5);
}

//鼠标移动时
void BeginLevel::onMouseMove(Event *event)
{
	EventMouse* mouse = (EventMouse*)event;
	int mouseX = mouse->getCursorX() , mouseY = mouse->getCursorY();
	if (mouseX < 500)
	{
		hero.setState(1);
		if (hero.weaponNum != 0)
			weapon->setTexture(backPictures[hero.heroWeapons[hero.curWeapon]]);
	}
	else if (mouseX > 500)
	{
		hero.setState(0);
		if (hero.weaponNum != 0)
			weapon->setTexture(pictures[hero.heroWeapons[hero.curWeapon]]);
	}
}

//鼠标单击时
void BeginLevel::onMouseDown(Event *event)
{
	EventMouse* mouse = (EventMouse*)event;
	double mouseX = mouse->getCursorX() , mouseY = mouse->getCursorY();
	double curX = hero.object->getPositionX(), curY = hero.object->getPositionY()+5;
	double dx = mouseX - 500, dy = mouseY - 365;
	double degree = atan2(dy,dx);
	Vec2 target;
	int tag = hero.heroWeapons[hero.curWeapon];
	if (tag == 0)
	{
		createBullet(0, Vec2(curX, curY), degree, 5);
	}
	if (tag == 1 && weaponCount[1]==weaponInterval[1])
	{
		createBullet(1, Vec2(curX, curY), degree - PI/18, 3);
		createBullet(1, Vec2(curX, curY), degree, 3);
		createBullet(1, Vec2(curX, curY), degree + PI/18, 3);
		weaponCount[1] = 0;
	}
	if (tag == 2 && weaponCount[2] == weaponInterval[2])
	{
		int flag;
		if (mouseX > 500)
			flag = 1;
		else
			flag = -1;
		auto rotateBy1 = RotateBy::create(0.1f, 120*flag);
		auto rotateBy2 = RotateBy::create(0.1f, -120*flag);
		auto seq = Sequence::create(rotateBy1, rotateBy2, nullptr);
		weapon->runAction(seq);
		weaponCount[2] = 0;
	}
	if (tag == 3 && weaponCount[3] == weaponInterval[3])
	{
		int ang;
		if (mouseX > 500)
			ang = 180;
		else
			ang = -180;
		auto rotateBy1 = RotateBy::create(0.1f, ang);
		auto rotateBy2 = RotateBy::create(0.1f, ang);
		auto seq = Sequence::create(rotateBy1,rotateBy2,nullptr);
		weapon->runAction(seq);
		weaponCount[3] = 0;
	}
}

//定时器
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

	//遍历子弹数组
	if (!bullets.empty())
	{
		std::vector<Bullet>::iterator itr = bullets.begin();
		for (; itr < bullets.end(); itr++)
		{
			double tarX = itr->object->getPositionX();
			double tarY = itr->object->getPositionY();
			int tileX = tarX / 40, tileY = (720 - tarY) / 40;
			if (tarX>=1000 || tarX<=0 || tarY<=0 || tarY>=720 || layer1->getTileAt(Vec2(tileX, tileY)) != 0 || layer2->getTileAt(Vec2(tileX, tileY)) != 0)
			{
				removeChild(itr->object);
				bullets.erase(itr);
				break;
			}
			double finX = 25 * cos(itr->degree);
			double finY = 25 * sin(itr->degree);
			auto moveBy = MoveBy::create(0.1, Vec2(finX,finY));
			itr->object->runAction(moveBy);
		}
	}

	//武器跟随移动
	if (hero.weaponNum != 0)
	{
		if (abs(weapon->getPositionX() - hero.object->getPositionX())>3 || abs(weapon->getPositionY() - hero.object->getPositionY())>6)
			weapon->setPosition(Vec2(hero.object->getPositionX(), hero.object->getPositionY() + 5));
	}

	weaponUpdate();

	//更新计数
	count = 1 - count;
}

bool BeginLevel::init()
{

	if (!Scene::init())
	{
		return false;
	}
	//常用位置
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Vec2 mid = Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);

	//声音
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("music/Q.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("music/Portal.mp3");

	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("music/BGM.mp3");

	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("music/BGM.mp3",true);
	CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.5f);

	//地图
	floor = TMXTiledMap::create("levels/BeginLevel/Floor.tmx");
	this->addChild( floor , 0 );

	wall1 = TMXTiledMap::create("levels/BeginLevel/Wall1.tmx");
	this->addChild( wall1 , 1 );
	wall2 = TMXTiledMap::create("levels/BeginLevel/Wall2.tmx");
	this->addChild( wall2 , 50 );

	layer1 = wall1->getLayer("layer1");
	layer2 = wall2->getLayer("layer1");

	//主角
	hero.object->setPosition(Vec2(580,420));
	this->addChild( hero.object , 20 );

	//血条
	blood = ui::LoadingBar::create("bar/blood.png");
	blood->setDirection(ui::LoadingBar::Direction::LEFT);
	blood->setPosition(Vec2(hero.object->getPositionX(), hero.object->getPositionY()+70));
	blood->setPercent(100);
	this->addChild(blood, 100);

	bloodBack = Sprite::create("bar/back.png");
	bloodBack->setPosition(Vec2(hero.object->getPositionX(), hero.object->getPositionY() + 70));
	this->addChild(bloodBack, 100);

	//计数
	count = 0;

	//图片
	pictures[0] = CCTextureCache::sharedTextureCache()->addImage("weapon/Rifle.png");
	pictures[1] = CCTextureCache::sharedTextureCache()->addImage("weapon/Shotgun.png");
	pictures[2] = CCTextureCache::sharedTextureCache()->addImage("weapon/Fish.png");
	pictures[3] = CCTextureCache::sharedTextureCache()->addImage("weapon/Sword.png");

	pictures[4] = CCTextureCache::sharedTextureCache()->addImage("maps/Portal.png");

	backPictures[0] = CCTextureCache::sharedTextureCache()->addImage("weapon/RifleBack.png");
	backPictures[1] = CCTextureCache::sharedTextureCache()->addImage("weapon/ShotgunBack.png");
	backPictures[2] = CCTextureCache::sharedTextureCache()->addImage("weapon/FishBack.png");
	backPictures[3] = CCTextureCache::sharedTextureCache()->addImage("weapon/SwordBack.png");

	bulletPictures[0] = CCTextureCache::sharedTextureCache()->addImage("bullet/RifleBullet.png");
	bulletPictures[1] = CCTextureCache::sharedTextureCache()->addImage("bullet/ShotgunBullet.png");

	//放置武器
	createItem( 0 , Vec2(390,530) );
	createItem( 1 , Vec2(580,530) );
	createItem( 2 , Vec2(390,310) );
	createItem( 3 , Vec2(580,310) );

	//攻速系统初始化
	weaponInterval[0] = 0;
	weaponInterval[1] = 20;
	weaponInterval[2] = 20;
	weaponInterval[3] = 25;

	weaponCount[0] = 0;
	weaponCount[1] = 0;
	weaponCount[2] = 0;
	weaponCount[3] = 0;

	//键盘响应
	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(BeginLevel::onKeyPressed, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(BeginLevel::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

	//鼠标响应
	auto mouseListener = EventListenerMouse::create();
	mouseListener->onMouseMove = CC_CALLBACK_1(BeginLevel::onMouseMove, this);
	mouseListener->onMouseDown = CC_CALLBACK_1(BeginLevel::onMouseDown, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

	//定时器
	this->scheduleUpdate();

	this->setPosition(-80, -60);

	return true;
}