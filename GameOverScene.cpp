#include "GameOverScene.h"
#include "Resource.h"
#include "StartPageScene.h"
#include "SimpleAudioEngine.h"

GameOverSceme* GameOverSceme::createScene()
{
	return GameOverSceme::create();
}

bool GameOverSceme::init()
{
	if (!Scene::init())
	{
		return false;
	}
	initBackground();
	return true;
}

void GameOverSceme::initBackground()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto loading = Sprite::create(s_loading);
	loading->setAnchorPoint(Vec2::ZERO);
	loading->setScale(2.2);
	addChild(loading);

	auto gameover = Sprite::create(s_gameOver);
	gameover->setPosition(visibleSize.width / 2, visibleSize.height - 300);
	gameover->setScale(1.5);
	addChild(gameover);

	auto cocos2dxlogo = Sprite::create(s_cocos2dx);
	cocos2dxlogo->setPosition(visibleSize.width / 2, 100);
	addChild(cocos2dxlogo);
}

void GameOverSceme::initMenu()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto playAgainNormal = Sprite::create(s_menu, Rect(358, 0, 116, 33));
	auto playAgainSelected = Sprite::create(s_menu, Rect(358, 33, 116, 33));
	auto playAgainDisabled = Sprite::create(s_menu, Rect(358, 66, 116, 33));

	auto menuItemPlayAgain = MenuItemSprite::create(playAgainNormal, playAgainSelected, playAgainDisabled, [this](Ref* pSender) {
		this->playAgainCallback(pSender);
		});
}

void GameOverSceme::playAgainCallback(Ref* pSender)
{
	auto scene = StartScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(2, scene));
}

void GameOverSceme::playBackgroundMusic()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(s_mainMainMusic);
}