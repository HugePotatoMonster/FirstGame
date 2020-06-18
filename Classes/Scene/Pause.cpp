#include "Pause.h"
#include "SimpleAudioEngine.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* Pause::createScene()
{
	return Pause::create();
}

bool Pause::init()
{

	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto exitButtum = MenuItemImage::create("buttum/Exit.png", "buttum/Exit.png", CC_CALLBACK_1(Pause::exitGame, this));
	auto menu1 = Menu::create(exitButtum, NULL);
	menu1->setPosition(Vec2(visibleSize.width / 2 + origin.x - 150, visibleSize.height / 2 + origin.y+100 ));
	this->addChild(menu1, 1);

	auto continueButtum = MenuItemImage::create("buttum/Start.png", "buttum/Start.png", CC_CALLBACK_1(Pause::continueGame, this));
	auto menu2 = Menu::create(continueButtum, NULL);
	menu2->setPosition(Vec2(visibleSize.width / 2 + origin.x +100, visibleSize.height / 2 + origin.y +100));
	this->addChild(menu2, 1);

	auto slider = ui::Slider::create();
	slider->loadBarTexture("slider/Slider.png");
	slider->loadSlidBallTextures("slider/Nomal.png", "slider/Pressed.png", "slider/SliderNode_Disable.png");
	slider->loadProgressBarTexture("slider/PressedSlider.png");
	slider->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 50));
	double vol = CocosDenshion::SimpleAudioEngine::getInstance()->getBackgroundMusicVolume();
	slider->setPercent(vol*200);
	slider->addEventListener([&](Ref* ref, ui::Slider::EventType type)
	{
		if (type == ui::Slider::EventType::ON_PERCENTAGE_CHANGED)
		{
			float percent = dynamic_cast<ui::Slider*> (ref)->getPercent();
			CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(percent/200);
		}
	});
	this->addChild(slider);

	return true;
}

void Pause::exitGame(cocos2d::Ref* Sender)
{
	Director::sharedDirector()->end();
	exit(0);
}

void Pause::continueGame(cocos2d::Ref* Sender)
{
	Director::sharedDirector()->popScene();
}