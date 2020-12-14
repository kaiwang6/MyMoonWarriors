
#include "AboutScene.h"
#include "Resource.h"
#include "StartPageScene.h"
Scene* AboutScene::createScene()
{
	return AboutScene::create();
}

bool AboutScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();

	Sprite* loadingSprite = Sprite::create(s_loading);
	loadingSprite->setAnchorPoint(Vec2::ZERO);
	loadingSprite->setScale(2.2);
	addChild(loadingSprite);

	Texture2D* imageTexture = TextureCache::getInstance()->addImage(s_menuTitle);
	auto titleSprite = Sprite::createWithTexture(imageTexture,Rect(0,36,100,34));

	std::string msg = "I recode this game according to the logic of MoonWarriors-html5,\n"
		"almost all of the code  keep unanimous with the original."
		"This showcase utilizes many features from Cocos2d-x engine,"
		"including: Parallax background, tilemap, actions, ease, frame animation, schedule, "
		"Labels, keyboard Dispatcher, Scene Transition";
	log("%s", msg);
	Label * aboutLabel = Label::createWithTTF(msg, s_arial_ttf, 18, Size(visibleSize.width * 0.85, 320));
	aboutLabel->setPosition(visibleSize.width / 2, visibleSize.height / 2 - 20);
	addChild(aboutLabel);

	Label* backLabel = Label::createWithBMFont(s_font, "back");
	auto backItem = MenuItemLabel::create(backLabel, [](Ref*) {
		auto Scene = StartScene::createScene();
		Director::getInstance()->replaceScene(TransitionFade::create(1.2, Scene));
		});

	ActionInterval* fadeIn = FadeTo::create(1,50);
	ActionInterval* fadeOut = FadeTo::create(1,255);
	EaseSineInOut* ease1 = EaseSineInOut::create(fadeIn);
	EaseSineInOut* ease2 = EaseSineInOut::create(fadeOut);

	auto seq = Sequence::create(ease1,ease2,  nullptr);
	backItem->runAction(RepeatForever::create(seq));

	auto menu = Menu::create(backItem, nullptr);
	menu->setPosition(Vec2(visibleSize.width / 2, 80));
	addChild(menu);

	return true;
}