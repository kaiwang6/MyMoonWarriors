
#include "GameScene.h"
#include "Resource.h"

GameScene* GameScene::createGameScene()
{
	return GameScene::create();
}

bool GameScene::init()
{
	addBackground();
	return true;
}

void GameScene::addBackground()
{
	//加载背景地图
	auto visibleSize = Director::getInstance()->getVisibleSize();
	_background = Sprite::create(s_bg01);
	_background->setAnchorPoint(Vec2::ZERO);
	_background->setScale(640 / 320.0 + 0.2, 960 / 576.0 + 0.2);
	_backgroundHeight = visibleSize.height;
	addChild(_background);

	//加载瓦砾地图
	_backTiledMap = TMXTiledMap::create(s_level01);
	addChild(_backTiledMap);
	auto h1 = _backTiledMap->getMapSize().height;
	auto h2 = _backTiledMap->getTileSize().height;
	_backTiledMapHeight = h1 * h2 + 200;

	//3秒向下移动地图
	_background->runAction(MoveBy::create(3, Vec2(0, -48)));
	_backTiledMap->runAction(MoveBy::create(3, Vec2(0, -200)));

	_backgroundHeight -= 48;
	_backTiledMapHeight -= 200;

	//调度器，每隔3秒执行一次回调函数
	schedule(CC_SCHEDULE_SELECTOR(GameScene::movingBackground), 3);
}

void GameScene::movingBackground(float dt)
{
	log("movingBackground...");
	auto sz = Director::getInstance()->getVisibleSize();


	//3秒向下移动地图
	_background->runAction(MoveBy::create(3, Vec2(0, -48)));
	_backTiledMap->runAction(MoveBy::create(3, Vec2(0, -200)));

	_backgroundHeight -= 48;
	_backTiledMapHeight -= 200;

	log("back Height: %f, sz.height: %f", _backgroundHeight, sz.height);

	if (_backgroundHeight < sz.height) {
		if (!_isReloadedBackground) {
			_backgroundReload = Sprite::create(s_bg01);
			_backgroundReload->setAnchorPoint(Vec2::ZERO);
			_backgroundReload->setScale(640 / 320.0 + 0.2, 960 / 576.0 + 0.2);
			_backgroundReload->setPosition(Vec2(0, sz.height));
			addChild(_backgroundReload, -10);

			_isReloadedBackground = true;
		}
		_backgroundReload->runAction(MoveBy::create(3, Vec2(0, -48)));
	}

	if (_backgroundHeight <= 0) {
		_backgroundHeight = _background->getContentSize().height * 2;
		this->removeChild(_background, true);
		_background = _backgroundReload;
		_backgroundReload = nullptr;
		_isReloadedBackground = false;
	}

	//TiledMap向下移
	if (_backTiledMapHeight <= sz.height) {
		if (!_isReloadedTiledMap) {
			_backTiledMapReload = TMXTiledMap::create(s_level01);
			_backTiledMapReload->setPosition(Vec2(0, sz.height));
			addChild(_backTiledMapReload, -9);
			_isReloadedTiledMap = true;
		}
		_backTiledMapReload->runAction(MoveBy::create(3, Vec2(0, -200)));
	}
	if (_backTiledMapHeight <= 0) {
		auto h1 = _backTiledMap->getMapSize().height;
		auto h2 = _backTiledMap->getTileSize().height;
		_backTiledMapHeight = h1 * h2 + 200;
		removeChild(_backTiledMap, true);
		_backTiledMap = _backTiledMapReload;
		_backTiledMapReload = nullptr;
		_isReloadedTiledMap = false;
	}
}