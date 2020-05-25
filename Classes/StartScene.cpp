#include "StartScene.h"
#include "SimpleAudioEngine.h"
#include "SimpleAudioEngine.h"
#include "BeginLevel.h"

USING_NS_CC;

static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

Scene* StartScene::createScene()
{
	return StartScene::create();
}

bool StartScene::init()
{

	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto background = Sprite::create("windows/StartScene.png");
	background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(background, 0);

	auto startButtum = MenuItemImage::create("buttum/Start.png","buttum/Start.png", CC_CALLBACK_1(StartScene::startGame, this));
	auto menu = Menu::create(startButtum, NULL);
	menu->setPosition(Vec2(visibleSize.width / 2 + origin.x - 250 , visibleSize.height / 2 + origin.y - 10 ));
	this->addChild(menu,1);

	return true;
}

void StartScene::startGame(cocos2d::Ref* Sender)
{

	auto buttumSound = CocosDenshion::SimpleAudioEngine::getInstance();
	buttumSound->playEffect("music/ButtumSound.mp3" , false , 1.0f , 1.0f , 1.0f );

	Director::getInstance()->replaceScene(BeginLevel::createScene());
}