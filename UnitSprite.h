#pragma once
#include "cocos2d.h"

USING_NS_CC;

class UnitSprite :public Sprite
{
public:
	UnitSprite();
	virtual ~UnitSprite();

	virtual void destroy() = 0;//游戏对象销毁
	virtual void hurt() = 0;//游戏对象受伤
	virtual Rect collideRect() = 0;//获取碰撞范围
	virtual bool isActive() = 0;//判断游戏对象是否活着
};