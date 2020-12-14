#pragma once
#include "cocos2d.h"
USING_NS_CC;

class GameOverSceme :public Scene 
{
public:
	static GameOverSceme* createScene();
	bool init();
	CREATE_FUNC(GameOverSceme);
private:
	void playAgainCallback(Ref* pSender);
	void initBackground();
	void initMenu();
	void playBackgroundMusic();
};