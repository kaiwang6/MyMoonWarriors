

#include "StartPageScene.h"
#include "Resource.h"
#include "SimpleAudioEngine.h"
#include "GameScene.h"
#include "AboutScene.h"
#include "Effect.h"
StartScene* StartScene::createScene()
{
	return StartScene::create();
}

bool StartScene::init()
{
	addLoading();
	addLogo();
	addMenu();
	addShip();
	schedule([this](float dt) {shipUpdate(dt); },3,"shipupdate");
	return true;
}

void StartScene::addLoading()
{
	auto visibleSize = Director:: getInstance()->getVisibleSize();
	log("visiblesize->width %f,->height %f", visibleSize.width, visibleSize.height);
	auto loadingSprite = Sprite::create(s_loading);
	auto spriteSize = loadingSprite->getContentSize();
	loadingSprite->setAnchorPoint(Vec2::ZERO);
	loadingSprite->setScale(visibleSize.width/spriteSize.width,visibleSize.height/spriteSize.height);
	this->addChild(loadingSprite);
}

void StartScene::addLogo()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto logoSprite = Sprite::create(s_logo);
	logoSprite->setPosition(visibleSize.width / 2, visibleSize.height - 200);
	addChild(logoSprite);
}

void StartScene::addMenu()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto sprite = Sprite::create(s_menu);
	auto spriteSize = sprite->getContentSize();

	auto newgameNormal = Sprite::create(s_menu, Rect(0, 0, spriteSize.width / 4, spriteSize.height / 3));
	auto newgameSelected = Sprite::create(s_menu, Rect(0, spriteSize.height / 3, spriteSize.width / 4, spriteSize.height / 3));
	auto newgameDisabled = Sprite::create(s_menu, Rect(0, spriteSize.height * 2 / 3, spriteSize.width / 4, spriteSize.height / 3));

	auto optionNormal = Sprite::create(s_menu, Rect(spriteSize.width / 4, 0, spriteSize.width / 4, spriteSize.height / 3));
	auto optionSelected = Sprite::create(s_menu, Rect(spriteSize.width / 4, spriteSize.height / 3, spriteSize.width / 4, spriteSize.height / 3));
	auto optionDisabled = Sprite::create(s_menu, Rect(spriteSize.width / 4, spriteSize.height * 2 / 3, spriteSize.width / 4, spriteSize.height / 3));

	auto aboutNormal = Sprite::create(s_menu, Rect(spriteSize.width * 2 / 4, 0, spriteSize.width / 4, spriteSize.height / 3));
	auto aboutSelected = Sprite::create(s_menu, Rect(spriteSize.width*2 / 4, spriteSize.height / 3, spriteSize.width / 4, spriteSize.height / 3));
	auto aboutDisabled = Sprite::create(s_menu, Rect(spriteSize.width*2 / 4, spriteSize.height * 2 / 3, spriteSize.width / 4, spriteSize.height / 3));

	auto newgameMenu = MenuItemSprite::create(newgameNormal, newgameSelected, newgameDisabled,CC_CALLBACK_1(StartScene::newgameCallback,this));
	auto optionMenu = MenuItemSprite::create(optionNormal, optionSelected, optionDisabled, CC_CALLBACK_1(StartScene::optionCallback, this));
	auto aboutMenu = MenuItemSprite::create(aboutNormal, aboutSelected, aboutDisabled, CC_CALLBACK_1(StartScene::aboutCallback, this));

	auto menu = Menu::create(newgameMenu, optionMenu, aboutMenu, nullptr);
	menu->alignItemsVerticallyWithPadding(20);
	menu->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(menu);

}

void StartScene::addShip()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto ship_texture = TextureCache::getInstance()->addImage(s_ship01);
	_ship = Sprite::createWithTexture(ship_texture, Rect(0, 45, 60, 38));

	auto pos = Vec2(rand_0_1() * visibleSize.width, 0);
	_ship->setPosition(pos);

	pos = Vec2(rand_0_1() * visibleSize.width,visibleSize.height+100);
	_ship->runAction(MoveBy::create(3, pos));

	//CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.7);
	//CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(s_mainMainMusic,true);
	addChild(_ship);
}

void StartScene::newgameCallback(Ref* pSender)
{
	Effect* effect = Effect::create();
	auto callback = CallFunc::create(CC_CALLBACK_0(StartScene::newGameScene, this));
	effect->flare(this, callback);
}

void StartScene::newGameScene()
{
	auto scene = GameScene::createGameScene();
	Director::getInstance()->replaceScene(TransitionFade::create(1.2, scene));
}

void StartScene::optionCallback(Ref*)
{

}
void StartScene::aboutCallback(Ref*)
{
	auto scene = AboutScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(1.2, scene));
}

void StartScene::update(float dt)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	if (_ship->getPositionY() > visibleSize.height)
	{
		auto pos = Vec2(rand_0_1() * visibleSize.width, 0);
		_ship->setPosition(pos);

		pos = Vec2(rand_0_1() * visibleSize.width, visibleSize.height + 100);
		_ship->runAction(MoveBy::create(3, pos));
	}
}
void StartScene::shipUpdate(float dt)
{
	update(dt);
}