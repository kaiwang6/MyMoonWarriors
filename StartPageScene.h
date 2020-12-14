#pragma once

#include "cocos2d.h"
USING_NS_CC;

class StartScene :public Scene
{
public:
	static StartScene* createScene();
	virtual bool init();
	CREATE_FUNC(StartScene);
private:
	void addLoading();
	void addLogo();
	void addMenu();
	void addShip();

	void newgameCallback(Ref *);
	void newGameScene();
	void optionCallback(Ref*);
	void aboutCallback(Ref*);
	virtual void update(float dt);
	void shipUpdate(float dt);
	Sprite* _ship;
};