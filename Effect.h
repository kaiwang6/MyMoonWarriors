#pragma once
#include "cocos2d.h"
USING_NS_CC;

class Effect :public Node
{
public:
	static void loadExplosion();
	void flare(Node* parent,CallFunc *cb);
	void killSprite(Node*);
	void enemyExplode(Node* parent, const Vec2& pos);
	void enemySpark(Node* parent, const Vec2& pos, float scale, float duration);
	CREATE_FUNC(Effect);
private:
	//Sprite* _sprite;
};