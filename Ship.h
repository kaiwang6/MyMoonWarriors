#pragma once
#include "cocos2d.h"
#include "UnitSprite.h"

USING_NS_CC;

class Ship :public UnitSprite
{
public:
	Ship();
	bool init();
	CREATE_FUNC(Ship);

	void shoot(float dt);
	void hurt()override;
	void destroy()override;
	Rect collideRect() override;
	void isActive() override;
private:
	bool _active;
};