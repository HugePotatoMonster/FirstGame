#ifndef __SECOND_LEVEL_H__
#define __SECOND_LEVEL_H__

#include "Hero.h"
#include "Item.h"
#include "Bullet.h"
#include "Pause.h"
#include "Enemy.h"
#include "cocos2d.h"
#include "BeginLevel.h"
#include "Dead.h"
#include "Sucess.h"

USING_NS_CC;

class SecondLevel :public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(SecondLevel);

	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event *event);
	bool isKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode);
	void keyPressedDuration(cocos2d::EventKeyboard::KeyCode code);

	virtual void onMouseMove(Event *event);
	virtual void onMouseDown(Event *event);

	virtual void update(float delta);

private:
	Hero hero;
	cocos2d::Sprite *weapon;
	std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;

	TMXTiledMap* floor;
	TMXTiledMap* wall1;
	TMXTiledMap* wall2;
	TMXTiledMap* barrier;
	TMXTiledMap* door;
	TMXTiledMap* closedDoor;

	TMXLayer* floorLayer;
	TMXLayer* wall1Layer;
	TMXLayer* wall2Layer;
	TMXLayer* barrierLayer;
	TMXLayer* doorLayer;
	TMXLayer* closedDoorLayer;

	std::vector<Item> items;
	std::vector<Bullet> bullets;
	std::vector<Bullet> enemyBullets;
	std::vector<Enemy> enemies;

	cocos2d::ui::LoadingBar* blood;
	cocos2d::Sprite* bloodBack;

	cocos2d::Sprite* openedBox;

	int count;
	int ran;

	cocos2d::CCTexture2D* pictures[10];
	cocos2d::CCTexture2D* backPictures[10];
	cocos2d::CCTexture2D* bulletPictures[10];
	cocos2d::CCTexture2D* enemyBulletPictures[10];
	cocos2d::CCTexture2D* enemyPictures[10];
	cocos2d::CCTexture2D* enemyBackPictures[10];

	int weaponInterval[4];
	int weaponCount[4];

	void weaponUpdate();
	void hurtUpdate();

	bool isWeapon(int tag);

	int room;
	int roomState[5];

	int bonus;

	int enemyTarget;
	int enemyCount;

	bool isBattle;

	int getRandom(int range);

	void createItem(int tag, Vec2 position);
	void createBullet(int tag, Vec2 position, double deg, int dam);
	void createEnemy(int tag, Vec2 position, int health, int interval);
	void createEnemyBullet(int tag, Vec2 position, double deg, int dam);
};

#endif 