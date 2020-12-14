#pragma once

#include "cocos2d.h"

USING_NS_CC;

class GameScene :public Scene
{
public:
	static GameScene* createGameScene();
	virtual bool init();
	CREATE_FUNC(GameScene);
private:
	void addBackground();
	void movingBackground(float dt);
private:
	Sprite* _background;//±³¾°
	Sprite* _backgroundReload;
	float _backgroundHeight;//±³¾°¸ß¶È
	bool _isReloadedBackground = false;

	TMXTiledMap* _backTiledMap;//ÍßÆ¬
	TMXTiledMap* _backTiledMapReload;
	float _backTiledMapHeight;
	bool _isReloadedTiledMap = false;

	
};