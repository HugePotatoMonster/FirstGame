#include "FirstLevel.h"
#include "SimpleAudioEngine.h"
#include "SimpleAudioEngine.h"

#define PI (acos(-1))

USING_NS_CC;

Scene* FirstLevel::createScene()
{
	return FirstLevel::create();
}

//创建一个物品
void FirstLevel::createItem(int tag, Vec2 position)
{
	Item temp;
	temp.object = Sprite::createWithTexture(pictures[tag]);
	temp.object->setPosition(position);
	temp.itemTag = tag;
	items.push_back(temp);
	std::vector<Item>::iterator itr = items.end() - 1;
	this->addChild(itr->object, 10);
}

//创建一个子弹
void FirstLevel::createBullet(int tag, Vec2 position, double deg, int dam)
{
	Bullet temp;
	temp.object = Sprite::createWithTexture(bulletPictures[tag]);
	temp.object->setPosition(position);
	temp.degree = deg;
	temp.damage = dam;
	bullets.push_back(temp);
	std::vector<Bullet>::iterator itr = bullets.end() - 1;
	this->addChild(itr->object, 15);
}

//创建一个敌方子弹
void FirstLevel::createEnemyBullet(int tag, Vec2 position, double deg, int dam)
{
	Bullet temp;
	temp.object = Sprite::createWithTexture(enemyBulletPictures[tag]);
	temp.object->setPosition(position);
	temp.degree = deg;
	temp.damage = dam;
	enemyBullets.push_back(temp);
	std::vector<Bullet>::iterator itr = enemyBullets.end() - 1;
	this->addChild(itr->object, 15);
}

//创建一个敌人
void FirstLevel::createEnemy(int tag, Vec2 position, int health,int interval)
{
	Enemy temp;
	temp.object = Sprite::createWithTexture(enemyPictures[tag]);
	temp.object->setAnchorPoint(Vec2(0.5, 0.15));
	temp.textureNomal = enemyPictures[tag];
	temp.textureBack = enemyBackPictures[tag];
	temp.hp = health;
	temp.hpSup = health;
	temp.object->setPosition(position);
	temp.enemyTag = tag;
	temp.dirInterval = interval;
	temp.dirCount = interval;
	temp.degree = 0;
	enemies.push_back(temp);
	std::vector<Enemy>::iterator itr = enemies.end() - 1;
	this->addChild(itr->object, 19);
}

//攻速系统
void FirstLevel::weaponUpdate()
{
	for (int i = 0; i < 4; i++)
	{
		if (weaponCount[i] < weaponInterval[i])
			weaponCount[i]++;
	}
}

//伤害判定系统
void FirstLevel::hurtUpdate()
{
	if (hero.hurtCount < hero.hurtInterval)
		hero.hurtCount++;
}

//获取随机数
int FirstLevel::getRandom(int range)
{
	int ran = rand() % range;
	return ran;
}

//判断tag是否为武器
bool FirstLevel::isWeapon(int tag)
{
	return (tag >= 0 && tag <= 3);
}

//按下键盘时
void FirstLevel::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
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
				if (itr->isNear(hero.object->getPosition()))
				{
					//移除地面物品
					this->removeChild(itr->object);
					int curNum = hero.weaponNum;
					int curWea = hero.heroWeapons[hero.curWeapon];
					hero.getItem(itr->itemTag);
					bool flag = isWeapon(itr->itemTag);
					if (flag)
					{
						weapon->setTexture(pictures[hero.heroWeapons[hero.curWeapon]]);
						createItem(curWea, hero.object->getPosition());
					}
					else if (itr->itemTag == 4)
					{
						CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/Portal.mp3");
						UserDefault::sharedUserDefault()->setIntegerForKey("hp", hero.hp);
						UserDefault::sharedUserDefault()->setIntegerForKey("curWeapon", hero.curWeapon);
						UserDefault::sharedUserDefault()->setIntegerForKey("weapon0", hero.heroWeapons[0]);
						UserDefault::sharedUserDefault()->setIntegerForKey("weapon1", hero.heroWeapons[1]);
						UserDefault::sharedUserDefault()->setIntegerForKey("damageUp", hero.damageUp);
						UserDefault::sharedUserDefault()->setIntegerForKey("count", count);
						UserDefault::sharedUserDefault()->setFloatForKey("vol", CocosDenshion::SimpleAudioEngine::getInstance()->getBackgroundMusicVolume());
						CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
						Director::getInstance()->replaceScene(Sucess::createScene());
					}
					else if (itr->itemTag == 7)
					{
						hero.changeHp(2);
					}
					else if (itr->itemTag == 8)
					{
						hero.damageUp = hero.damageUp + 4;
					}
					//从地面物品vector中去除
					items.erase(itr);
					break;
				}
			}
		}
	}
	if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_Q && hero.weaponNum == 2)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/Q.mp3");
		hero.curWeapon = 1 - hero.curWeapon;
		weapon->setTexture(pictures[hero.heroWeapons[hero.curWeapon]]);
	}
}

//松开键盘时
void FirstLevel::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
	keys[keyCode] = false;
}

//检测某个键是否被按住
bool FirstLevel::isKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode) {
	if (keys[keyCode]) {
		return true;
	}
	else {
		return false;
	}
}

//如果某个键正被按住
void FirstLevel::keyPressedDuration(cocos2d::EventKeyboard::KeyCode code) {
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
	int tarX = curX + 5 * offsetX, tarY = curY + 5 * offsetY;
	int tileX = tarX / 40, tileY = (4800 - tarY) / 40;
	if (!isBattle)
	{
		if (wall1Layer->getTileAt(Vec2(tileX, tileY)) != 0 || wall2Layer->getTileAt(Vec2(tileX, tileY)) != 0 || barrierLayer->getTileAt(Vec2(tileX, tileY)) != 0)
		{
			offsetX = 0;
			offsetY = 0;
		}
	}
	else
	{
		if (wall1Layer->getTileAt(Vec2(tileX, tileY)) != 0 || wall2Layer->getTileAt(Vec2(tileX, tileY)) != 0 || barrierLayer->getTileAt(Vec2(tileX, tileY)) != 0 || closedDoorLayer->getTileAt(Vec2(tileX, tileY)) != 0)
		{
			offsetX = 0;
			offsetY = 0;
		}
	}
	auto moveBy1 = MoveBy::create(0.1, Vec2(offsetX, offsetY));
	auto moveBy2 = MoveBy::create(0.1, Vec2(offsetX, offsetY));
	auto moveBy3 = MoveBy::create(0.1, Vec2(offsetX, offsetY));
	auto moveBy4 = MoveBy::create(0.1, Vec2(offsetX, offsetY));
	auto moveBy5 = MoveBy::create(0.1, Vec2(-offsetX, -offsetY));
	hero.object->runAction(moveBy1);
	weapon->runAction(moveBy2);
	blood->runAction(moveBy3);
	bloodBack->runAction(moveBy4);
	this->runAction(moveBy5);
}

//鼠标移动时
void FirstLevel::onMouseMove(Event *event)
{
	if (hero.hp > 0)
	{
		EventMouse* mouse = (EventMouse*)event;
		int mouseX = mouse->getCursorX(), mouseY = mouse->getCursorY();
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
}

//鼠标单击时
void FirstLevel::onMouseDown(Event *event)
{
	EventMouse* mouse = (EventMouse*)event;
	double mouseX = mouse->getCursorX(), mouseY = mouse->getCursorY();
	double curX = hero.object->getPositionX(), curY = hero.object->getPositionY() + 5;
	double dx = mouseX - 500, dy = mouseY - 365;
	double degree = atan2(dy, dx);
	Vec2 target;
	int tag = hero.heroWeapons[hero.curWeapon];
	if (tag == 0)
	{
		createBullet(0, Vec2(curX, curY), degree, 6+hero.damageUp);
	}
	if (tag == 1 && weaponCount[1] == weaponInterval[1])
	{
		createBullet(1, Vec2(curX, curY), degree - PI / 18, 5);
		createBullet(1, Vec2(curX, curY), degree, 3);
		createBullet(1, Vec2(curX, curY), degree + PI / 18, 5);
		if (hero.damageUp > 0)
		{
			createBullet(1, Vec2(curX, curY), degree - PI / 36, 5);
			createBullet(1, Vec2(curX, curY), degree + PI / 36, 5);
		}
		weaponCount[1] = 0;
	}
	if (tag == 2 && weaponCount[2] == weaponInterval[2])//7
	{
		int flag;
		if (mouseX > 500)
			flag = 1;
		else
			flag = -1;
		auto rotateBy1 = RotateBy::create(0.1f, 120 * flag);
		auto rotateBy2 = RotateBy::create(0.1f, -120 * flag);
		auto seq = Sequence::create(rotateBy1, rotateBy2, nullptr);
		weapon->runAction(seq);
		weaponCount[2] = 0;
		//判断是否有怪被击中
		if (!enemies.empty())
		{
			std::vector<Enemy>::iterator itr = enemies.begin();
			for (; itr < enemies.end(); itr++)
			{
				double enemyX = itr->object->getPositionX();
				double enemyY = itr->object->getPositionY();
				if (flag == 1 )
				{
					if (enemyX - curX<100 && enemyX - curX>-10 && abs(enemyY - curY) < 50)
					{
						itr->changeHp(-7- hero.damageUp);
						itr->object->setColor(Color3B::RED);
					}
				}
				else
				{
					if (curX - enemyX<100 && curX - enemyX>-10 && abs(enemyY - curY) < 50)
					{
						itr->changeHp(-7- hero.damageUp);
						itr->object->setColor(Color3B::RED);
					}
				}
				if (itr->hp == 0)
				{
					enemyCount++;
					this->removeChild(itr->object);
					enemies.erase(itr);
					break;
				}
			}
		}
	}
	if (tag == 3 && weaponCount[3] == weaponInterval[3])//4
	{
		int ang;
		if (mouseX > 500)
			ang = 180;
		else
			ang = -180;
		auto rotateBy1 = RotateBy::create(0.1f, ang);
		auto rotateBy2 = RotateBy::create(0.1f, ang);
		auto seq = Sequence::create(rotateBy1, rotateBy2, nullptr);
		weapon->runAction(seq);
		weaponCount[3] = 0;
		//判断是否有怪被击中
		if (!enemies.empty())
		{
			std::vector<Enemy>::iterator itr = enemies.begin();
			for (; itr < enemies.end(); itr++)
			{
				double enemyX = itr->object->getPositionX();
				double enemyY = itr->object->getPositionY();
				dx = enemyX - curX;
				dy = enemyY - curY;
				if(sqrt(dx*dx+dy*dy)<100)
				itr->changeHp(-7- hero.damageUp);
				itr->object->setColor(Color3B::RED);
				if (itr->hp == 0)
				{
					enemyCount++;
					this->removeChild(itr->object);
					enemies.erase(itr);
					break;
				}
			}
		}
	}
}

//定时器
void FirstLevel::update(float delta) {
	Node::update(delta);

	//主角颜色复原
	hero.object->setColor(Color3B(255, 255, 255));

	if (hero.hp == 0 && hero.hurtCount==hero.hurtInterval)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
		Director::getInstance()->replaceScene(Dead::createScene());
	}
	else if (hero.hp == 0 && hero.hurtCount < hero.hurtInterval)
	{
		hero.hurtCount++;
	}
	else
	{
		//键盘控制
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

		//子弹移动
		if (!bullets.empty())
		{
			std::vector<Bullet>::iterator itr = bullets.begin();
			for (; itr < bullets.end(); itr++)
			{
				double tarX = itr->object->getPositionX();
				double tarY = itr->object->getPositionY();
				int tileX = tarX / 40, tileY = (4800 - tarY) / 40;
				if (!isBattle)
				{
					if (tarX >= 4800 || tarX <= 0 || tarY <= 0 || tarY >= 4800 || wall1Layer->getTileAt(Vec2(tileX, tileY)) != 0 || wall2Layer->getTileAt(Vec2(tileX, tileY)) != 0 || barrierLayer->getTileAt(Vec2(tileX, tileY)) != 0)
					{
						removeChild(itr->object);
						bullets.erase(itr);
						break;
					}
				}
				else
				{
					if (tarX >= 4800 || tarX <= 0 || tarY <= 0 || tarY >= 4800 || wall1Layer->getTileAt(Vec2(tileX, tileY)) != 0 || wall2Layer->getTileAt(Vec2(tileX, tileY)) != 0 || barrierLayer->getTileAt(Vec2(tileX, tileY)) != 0 || closedDoorLayer->getTileAt(Vec2(tileX, tileY)) != 0)
					{
						removeChild(itr->object);
						bullets.erase(itr);
						break;
					}
				}
				double finX = 25 * cos(itr->degree);
				double finY = 25 * sin(itr->degree);
				auto moveBy = MoveBy::create(0.1, Vec2(finX, finY));
				itr->object->runAction(moveBy);
			}
		}

		//敌人行动
		if (!enemies.empty())
		{
			std::vector<Enemy>::iterator itr = enemies.begin();
			for (; itr < enemies.end(); itr++)
			{
				double curX = itr->object->getPositionX();
				double curY = itr->object->getPositionY();
				double heroX = hero.object->getPositionX();
				double heroY = hero.object->getPositionY();
				if (curX < heroX)
					itr->setState(0);
				if (curX > heroX)
					itr->setState(1);
				//0号怪物逻辑
				if (itr->enemyTag == 0)
				{
					double finX = 4 * cos(itr->degree);
					double finY = 4 * sin(itr->degree);
					if (itr->dirCount < itr->dirInterval && itr->dirCount >= 0.75*itr->dirInterval)
					{
						finX = 0;
						finY = 0;
						itr->dirCount++;
					}
					else if (itr->dirCount >= itr->dirInterval)
					{
						double dx = heroX - curX;
						double dy = heroY - curY;
						double deg = atan2(dy, dx);
						createEnemyBullet(0, Vec2(curX, curY), deg, 2);
						double range = 500 - getRandom(1001);
						if (range >= 0)
							range += 1000;
						else if (range < 0)
							range -= 1000;
						double rangeDegree = PI*(range / 3000);
						itr->degree = deg + rangeDegree;
						finX = 4 * cos(itr->degree);
						finY = 4 * sin(itr->degree);
						itr->dirCount = 0;
					}
					else
					{
						itr->dirCount++;
					}

					int tarX = curX + 10 * finX, tarY = curY + 10 * finY;
					int tileX = tarX / 40, tileY = (4800 - tarY) / 40;
					if (wall1Layer->getTileAt(Vec2(tileX, tileY)) != 0 || wall2Layer->getTileAt(Vec2(tileX, tileY)) != 0 || barrierLayer->getTileAt(Vec2(tileX, tileY)) != 0 || closedDoorLayer->getTileAt(Vec2(tileX, tileY)) != 0)
					{
						finX = 0;
						finY = 0;
					}

					auto moveBy = MoveBy::create(0.1, Vec2(finX, finY));
					itr->object->runAction(moveBy);
				}
				//2号怪物逻辑
				else if (itr->enemyTag == 2)
				{
					double finX = 6 * cos(itr->degree);
					double finY = 6 * sin(itr->degree);
					if (itr->dirCount < itr->dirInterval && itr->dirCount >= 0.8*itr->dirInterval)
					{
						finX = 0;
						finY = 0;
						itr->dirCount++;
					}
					else if (itr->dirCount >= itr->dirInterval)
					{
						double dx = heroX - curX;
						double dy = heroY - curY;
						double deg = atan2(dy, dx);
						itr->degree = deg;
						finX = 6 * cos(itr->degree);
						finY = 6 * sin(itr->degree);
						itr->dirCount = 0;
					}
					else
					{
						itr->dirCount++;
					}

					int tarX = curX + 10 * finX, tarY = curY + 10 * finY;
					int tileX = tarX / 40, tileY = (4800 - tarY) / 40;
					if (wall1Layer->getTileAt(Vec2(tileX, tileY)) != 0 || wall2Layer->getTileAt(Vec2(tileX, tileY)) != 0 || barrierLayer->getTileAt(Vec2(tileX, tileY)) != 0 || closedDoorLayer->getTileAt(Vec2(tileX, tileY)) != 0)
					{
						finX = 0;
						finY = 0;
					}

					auto moveBy = MoveBy::create(0.1, Vec2(finX, finY));
					itr->object->runAction(moveBy);
				}
			}
		}

		//伤害结算部分*****************************************************************************************************

		//遍历敌人数组
		if (!enemies.empty())
		{
			std::vector<Enemy>::iterator itr = enemies.begin();
			for (; itr < enemies.end(); itr++)
			{
				itr->object->setColor(Color3B(255, 255, 255));
				double curX = itr->object->getPositionX();
				double curY = itr->object->getPositionY();
				double heroX = hero.object->getPositionX();
				double heroY = hero.object->getPositionY();
				//判断是否受到伤害
				if (!bullets.empty())
				{
					std::vector<Bullet>::iterator bitr = bullets.begin();
					for (; bitr < bullets.end(); bitr++)
					{
						double bulletX = bitr->object->getPositionX();
						double bulletY = bitr->object->getPositionY();
						if (abs(bulletX - curX) <= 30 && (((bulletY - curY) < 60 && bulletY >= curY) || ((curY - bulletY) < 8 && bulletY < curY)))
						{
							itr->changeHp(-bitr->damage);
							itr->object->setColor(Color3B::RED);
							this->removeChild(bitr->object);
							bullets.erase(bitr);
							break;
						}
					}
				}
				if (abs(heroX - curX) < 55 && abs(heroY - curY) < 60 && hero.hurtCount == hero.hurtInterval)
				{
					hero.changeHp(-2);
					hero.object->setColor(Color3B::RED);
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/Hurt.mp3");
					hero.hurtCount = 0;
				}
				if (itr->hp == 0)
				{
					enemyCount++;
					this->removeChild(itr->object);
					enemies.erase(itr);
					break;
				}
			}
		}

		//遍历敌人子弹数组
		if (!enemyBullets.empty())
		{
			std::vector<Bullet>::iterator itr = enemyBullets.begin();
			for (; itr < enemyBullets.end(); itr++)
			{
				double tarX = itr->object->getPositionX();
				double tarY = itr->object->getPositionY();
				double heroX = hero.object->getPositionX();
				double heroY = hero.object->getPositionY();
				int tileX = tarX / 40, tileY = (4800 - tarY) / 40;
				if (tarX >= 4800 || tarX <= 0 || tarY <= 0 || tarY >= 4800 || wall1Layer->getTileAt(Vec2(tileX, tileY)) != 0 || wall2Layer->getTileAt(Vec2(tileX, tileY)) != 0 || barrierLayer->getTileAt(Vec2(tileX, tileY)) != 0 || closedDoorLayer->getTileAt(Vec2(tileX, tileY)) != 0)
				{
					removeChild(itr->object);
					enemyBullets.erase(itr);
					break;
				}
				if (abs(heroX - tarX) < 45 && ((heroY > tarY && abs(heroY - tarY) < 10) || (heroY <= tarY && abs(tarY - heroY) < 65)) && hero.hurtCount == hero.hurtInterval)
				{
					hero.changeHp(-itr->damage);
					hero.object->setColor(Color3B::RED);
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/Hurt.mp3");
					hero.hurtCount = 0;
					removeChild(itr->object);
					enemyBullets.erase(itr);
					break;
				}
				double finX = 6 * cos(itr->degree);
				double finY = 6 * sin(itr->degree);
				auto moveBy = MoveBy::create(0.1, Vec2(finX, finY));
				itr->object->runAction(moveBy);
			}
		}

		//*****************************************************************************************************************

		//武器跟随移动
		if (abs(weapon->getPositionX() - hero.object->getPositionX()) > 3 || abs(weapon->getPositionY() - hero.object->getPositionY()) > 6)
			weapon->setPosition(Vec2(hero.object->getPositionX(), hero.object->getPositionY() + 5));

		//武器攻速系统
		weaponUpdate();

		//伤害判定系统
		hurtUpdate();

		//更新血条
		blood->setPercent(hero.hp * 10);

		//更新计数
		count = 1 - count;

		//判断是否达到击杀目标
		if (enemyTarget > 0 && enemyCount == enemyTarget)
		{
			enemyCount = 0;
			enemyTarget = 0;
			roomState[room] = 0;
			closedDoor->setLocalZOrder(-1);
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/Door.mp3");
			isBattle = false;
		}

		//更新所在房间
		if (!isBattle)
		{
			double curX, curY;
			curX = hero.object->getPositionX();
			curY = hero.object->getPositionY();
			if (curX <= 925)
			{
				room = 0;
			}
			else if (curX >= 1835 && curX <= 2605 && curY >= 2135 && curY <= 2950)
			{
				room = 1;
			}
			else if (curX >= 2035 && curX <= 2405 && curY >= 3695 && curY <= 3950)
			{
				room = 2;
			}
			else if (curX >= 1915 && curX <= 2525 && curY >= 855 && curY <= 1510)
			{
				room = 3;
			}
			else if (curX >= 3395)
			{
				room = 4;
			}
			if (roomState[room] > 0)
			{
				enemyTarget = roomState[room];
				isBattle = true;
				closedDoor->setLocalZOrder(1);
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/Door.mp3");
				if (room == 1)
				{
					createEnemy(0, Vec2(2000, 2320), 60, 180);
					createEnemy(0, Vec2(2440, 2320), 60, 180);
					createEnemy(0, Vec2(2220, 2320), 60, 120);
					createEnemy(0, Vec2(2000, 2760), 60, 100);
					createEnemy(0, Vec2(2440, 2760), 60, 140);
				}
				if (room == 3)
				{
					createEnemy(2, Vec2(2080, 1000), 80, 90);
					createEnemy(2, Vec2(2360, 1040), 80, 90);
				}
			}
		}
	}
}

bool FirstLevel::init()
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
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("music/Door.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("music/Hurt.mp3");

	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("music/BGM.mp3");

	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("music/BGM.mp3", true);
	CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(UserDefault::sharedUserDefault()->getFloatForKey("vol"));

	//地图
	floor = TMXTiledMap::create("levels/FirstLevel/Floor.tmx");
	this->addChild(floor, 0);

	wall1 = TMXTiledMap::create("levels/FirstLevel/Wall1.tmx");
	this->addChild(wall1, 1);
	wall2 = TMXTiledMap::create("levels/FirstLevel/Wall2.tmx");
	this->addChild(wall2, 50);

	barrier = TMXTiledMap::create("levels/FirstLevel/Barrier.tmx");
	this->addChild(barrier, 0);

	door = TMXTiledMap::create("levels/FirstLevel/Door.tmx");
	this->addChild(door, 0);

	closedDoor = TMXTiledMap::create("levels/FirstLevel/ClosedDoor.tmx");
	this->addChild(closedDoor, -1);

	wall1Layer = wall1->getLayer("layer1");
	wall2Layer = wall2->getLayer("layer1");
	barrierLayer = barrier->getLayer("layer1");
	doorLayer = door->getLayer("layer1");
	closedDoorLayer = closedDoor->getLayer("layer1");

	//主角
	hero.object->setPosition(Vec2(660, 2700));
	hero.weaponNum = 2;
	hero.curWeapon = UserDefault::sharedUserDefault()->getIntegerForKey("curWeapon");
	hero.heroWeapons[0] = UserDefault::sharedUserDefault()->getIntegerForKey("weapon0");
	hero.heroWeapons[1] = UserDefault::sharedUserDefault()->getIntegerForKey("weapon1");
	hero.damageUp = UserDefault::sharedUserDefault()->getIntegerForKey("damageUp");
	this->addChild(hero.object, 20);

	//血条
	blood = ui::LoadingBar::create("bar/blood.png");
	blood->setDirection(ui::LoadingBar::Direction::LEFT);
	blood->setPosition(Vec2(hero.object->getPositionX(), hero.object->getPositionY() + 70));
	blood->setPercent(100);
	this->addChild(blood, 100);

	bloodBack = Sprite::create("bar/back.png");
	bloodBack->setPosition(Vec2(hero.object->getPositionX(), hero.object->getPositionY() + 70));
	this->addChild(bloodBack, 100);

	//计数
	count = 0;
	int ran= UserDefault::sharedUserDefault()->getIntegerForKey("count");

	//房间
	room = 0;
	roomState[0] = 0;
	roomState[1] = 5;
	roomState[2] = 0;
	roomState[3] = 2;
	roomState[4] = 0;

	//怪物计数
	enemyCount = 0;
	enemyTarget = 0;

	//交战状态
	isBattle = false;

	//图片
	pictures[0] = CCTextureCache::sharedTextureCache()->addImage("weapon/Rifle.png");
	pictures[1] = CCTextureCache::sharedTextureCache()->addImage("weapon/Shotgun.png");
	pictures[2] = CCTextureCache::sharedTextureCache()->addImage("weapon/Fish.png");
	pictures[3] = CCTextureCache::sharedTextureCache()->addImage("weapon/Sword.png");

	pictures[4] = CCTextureCache::sharedTextureCache()->addImage("maps/Portal.png");

	pictures[5] = CCTextureCache::sharedTextureCache()->addImage("maps/Box.png");
	pictures[6] = CCTextureCache::sharedTextureCache()->addImage("maps/BoxOpened.png");
	pictures[7] = CCTextureCache::sharedTextureCache()->addImage("things/Red.png");
	pictures[8] = CCTextureCache::sharedTextureCache()->addImage("things/Blue.png");

	backPictures[0] = CCTextureCache::sharedTextureCache()->addImage("weapon/RifleBack.png");
	backPictures[1] = CCTextureCache::sharedTextureCache()->addImage("weapon/ShotgunBack.png");
	backPictures[2] = CCTextureCache::sharedTextureCache()->addImage("weapon/FishBack.png");
	backPictures[3] = CCTextureCache::sharedTextureCache()->addImage("weapon/SwordBack.png");

	bulletPictures[0] = CCTextureCache::sharedTextureCache()->addImage("bullet/RifleBullet.png");
	bulletPictures[1] = CCTextureCache::sharedTextureCache()->addImage("bullet/ShotgunBullet.png");

	enemyBulletPictures[0] = CCTextureCache::sharedTextureCache()->addImage("bullet/ShotterBullet.png");
	enemyBulletPictures[1] = CCTextureCache::sharedTextureCache()->addImage("bullet/WitchBullet.png");

	enemyPictures[0] = CCTextureCache::sharedTextureCache()->addImage("enemy/Shotter.png");
	enemyPictures[1] = CCTextureCache::sharedTextureCache()->addImage("enemy/Witch.png");
	enemyPictures[2] = CCTextureCache::sharedTextureCache()->addImage("enemy/Pig.png");
	enemyPictures[3] = CCTextureCache::sharedTextureCache()->addImage("enemy/Monster.png");

	enemyBackPictures[0] = CCTextureCache::sharedTextureCache()->addImage("enemy/ShotterBack.png");
	enemyBackPictures[1] = CCTextureCache::sharedTextureCache()->addImage("enemy/WitchBack.png");
	enemyBackPictures[2] = CCTextureCache::sharedTextureCache()->addImage("enemy/PigBack.png");
	enemyBackPictures[3] = CCTextureCache::sharedTextureCache()->addImage("enemy/MonsterBack.png");

	//物品放置
	createItem(4, Vec2(3540,2540));
	createItem(7+ran, Vec2(2220,3820));

	//攻速系统初始化
	weaponInterval[0] = 0;
	weaponInterval[1] = 20;
	weaponInterval[2] = 20;
	weaponInterval[3] = 25;

	weaponCount[0] = 0;
	weaponCount[1] = 0;
	weaponCount[2] = 0;
	weaponCount[3] = 0;

	//加载武器
	weapon = Sprite::createWithTexture(pictures[hero.heroWeapons[hero.curWeapon]]);
	weapon->setPosition(Vec2(hero.object->getPositionX(), hero.object->getPositionY()+5));
	this->addChild(weapon, 25);

	//随机数种子设置
	srand((int)time(0));

	//键盘响应
	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(FirstLevel::onKeyPressed, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(FirstLevel::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

	//鼠标响应
	auto mouseListener = EventListenerMouse::create();
	mouseListener->onMouseMove = CC_CALLBACK_1(FirstLevel::onMouseMove, this);
	mouseListener->onMouseDown = CC_CALLBACK_1(FirstLevel::onMouseDown, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

	//定时器
	this->scheduleUpdate();

	this->setPosition(-160, -2340);

	return true;
}