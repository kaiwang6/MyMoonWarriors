#pragma once
#include "cocos2d.h"

USING_NS_CC;

class UnitSprite :public Sprite
{
public:
	UnitSprite();
	virtual ~UnitSprite();

	virtual void destroy() = 0;//��Ϸ��������
	virtual void hurt() = 0;//��Ϸ��������
	virtual Rect collideRect() = 0;//��ȡ��ײ��Χ
	virtual bool isActive() = 0;//�ж���Ϸ�����Ƿ����
};