#pragma once
#include "cocos2d.h"
USING_NS_CC;

class AboutScene :public Scene
{
public:
	static Scene* createScene();
	//static Scene* create();
	bool init();
	CREATE_FUNC(AboutScene);
};