#pragma once
#include "cocos2d.h"
#include "UnitSprite.h"
#include <string>
USING_NS_CC;

class Bullet :public UnitSprite
{
public:
	Bullet();

	static Bullet* create(const std::string &name);

	virtual bool init(const std::string& name);

	void update(float dt);

	void hurt();
	void destroy();
	bool isActive() { return _active; }
	Rect collideRect();
	int getZOrder()const { return _zOrder; }
private:
	void exploded();
private:
	std::string _name;
	int _hp;
	int _power;
	int _attackMode;
	//int _parentType;
	float _velocityX;
	float _velocityY;
	bool _active;
	int _zOrder;
};