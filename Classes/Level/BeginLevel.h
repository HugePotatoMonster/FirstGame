#ifndef __BEGIN_LEVEL_H__
#define __BEGIN_LEVEL_H__

#include "Hero.h"
#include "Item.h"
#include "Bullet.h"
#include "Pause.h"
#include "cocos2d.h"
#include "FirstLevel.h"

USING_NS_CC;

class BeginLevel :public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(BeginLevel);

	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event *event);
	bool isKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode);
	void keyPressedDuration(cocos2d::EventKeyboard::KeyCode code);

	virtual void onMouseMove(Event *event);
	virtual void onMouseDown(Event *event);

	virtual void update(float delta);

private:
	Hero hero;
	cocos2d::Sprite* weapon;
	std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;

	TMXTiledMap* floor;
	TMXTiledMap* wall1;
	TMXTiledMap* wall2;

	TMXLayer* layer1;
	TMXLayer* layer2;

	std::vector<Item> items;
	std::vector<Bullet> bullets;

	cocos2d::ui::LoadingBar* blood;
	cocos2d::Sprite* bloodBack;

	cocos2d::CCTexture2D* pictures[10];
	cocos2d::CCTexture2D* backPictures[10];
	cocos2d::CCTexture2D* bulletPictures[10];

	int count;

	int weaponInterval[4];
	int weaponCount[4];

	void weaponUpdate();

	bool isWeapon(int tag);

	void createItem(int tag, Vec2 position);
	void createBullet(int tag, Vec2 position, double deg, int dam);
};

#endif 