#include "Bullet.h"
#include "Resource.h"
Bullet* Bullet::create(const std::string& name)
{
	Bullet* pret = new(std::nothrow) Bullet();
	if (pret && pret->init(name))
	{
		pret->autorelease();
		return pret;
	}
	else
	{
		CC_SAFE_DELETE(pret);
		return nullptr;
	}
}

Bullet::Bullet()
:_hp(1)
,_power(1)
,_attackMode(1)
,_velocityX(0)
,_velocityY(200)
,_active(true)
,_zOrder(3000)
{}

bool Bullet::init(const std::string& name)
{
	if (!Sprite::init())
	{
		return false;
	}
	_name = name;
	if (_name == "W2.png")
	{
		_velocityX = 0;
		_velocityY = 300;
	}
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(s_bullet_plist);
	this->initWithSpriteFrameName(name);
	this->setScale(0.5);

	BlendFunc cb1 = { GL_SRC_ALPHA, GL_ONE };
	this->setBlendFunc(cb1);

	scheduleUpdate();

	return true;
}

void Bullet::update(float dt)
{
	auto pos = getPosition();
	if (_name == "W2.png")
	{
		pos.x += _velocityX * dt;
		pos.y -= _velocityY * dt;
	}
	else
	{
		pos.x -= _velocityX * dt;
		pos.y += _velocityY * dt;
	}
	setPosition(pos);
	if (_hp < =0)
	{
		_active = false;
	}
}

void Bullet::hurt()
{
	--_hp;
	if (_hp <= 0)
	{
		_active = false;
		exploded();
		destroy();
	}
}

void Bullet::destroy()
{
	this->removeFromParent();
}

void Bullet::exploded()
{
	if (getParent()) {
		Sprite* explode = Sprite::create(s_hit);
		explode->setPosition(this->getPosition());
		explode->setRotation(rand_0_1() * 360);
		explode->setScale(0.8);
		this->getParent()->addChild(explode, 9999);
		this->removeFromParent();

		explode->runAction(ScaleBy::create(0.3, 2));
		CallFunc* removeExplode = CallFunc::create([explode]() {
			explode->removeFromParent();
			});
		explode->runAction(Sequence::create(FadeOut::create(0.3), removeExplode, nullptr));
	}
}

Rect Bullet::collideRect()
{
	//log("Bullet::collideRect()");
	auto pos = getPosition();
	return Rect(pos.x - 3, pos.y - 3, 6, 6);
}