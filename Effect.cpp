#include "Effect.h"
#include "Resource.h"

void Effect::loadExplosion()
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(s_explosion_plist);

	char name[64] = { 0 };
	Vector<SpriteFrame*> frames;
	for (ssize_t i = 1; i <= 35; ++i)
	{
		sprintf(name, "explosion_%02d.png", i);
		frames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
	}

	Animation* animation = Animation::createWithSpriteFrames(frames, 0, 03);
	//����ը�������map
	AnimationCache::getInstance()->addAnimation(animation, "explosion");
}

void Effect::flare(Node* parent, CallFunc* cb)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto flare = Sprite::create(s_flare);
	BlendFunc cb1 = { GL_SRC_ALPHA, GL_ONE };
	flare->setBlendFunc(cb1);
	parent->addChild(flare, 10);

	flare->setOpacity(0);

	flare->setPosition(Vec2(-30, visibleSize.height - 300));

	// ���ó�ʼ�Ƕ�
	flare->setRotation(-120);

	// ���ó�ʼ�Ŵ�ϵ��
	flare->setScale(0.1);

	//����͸���Ƚ���
	auto opacityAction = FadeTo::create(0.5, 255);
	auto opacityAction2 = FadeTo::create(1, 0);

	//��С����
	auto bigAction = ScaleBy::create(0.7, 1.2, 1.2);
	auto biggerEaseAction = EaseSineOut::create(bigAction);

	//�ƶ�λ�ý���
	auto moveAction = MoveBy::create(0.5, Vec2(400, 0));
	auto moveEaseAction = EaseSineOut::create(moveAction);

	//��ת�ǶȽ���
	auto rotateAction = RotateBy::create(2.5, 90);
	auto rotateEaseAction = EaseExponentialOut::create(rotateAction);

	//�ָ�ԭ��С
	auto originBigAction = ScaleTo::create(0.5, 1);

	auto smallAction = ScaleTo::create(0.5, 0.2);

	//����������ɺ󣬻ص�����Ҫɾ������flare
	//auto removeFunc = CallFuncN::create(flare, CC_CALLFUNCN_SELECTOR(Effect::killSprite));
	auto removeFunc = CallFunc::create([this, flare]() {
		this->killSprite(flare);
		});

	auto seq1 = Sequence::create(opacityAction, biggerEaseAction, opacityAction2, removeFunc, cb, nullptr);
	flare->runAction(Spawn::create(seq1, moveAction, rotateAction, originBigAction, nullptr));

	//flare->runAction(Sequence::create(opacityAction, biggerEaseAction, opacityAction2, removeFunc, cb, nullptr));
	//flare->runAction(moveAction);
	//flare->runAction(rotateAction);
	//flare->runAction(originBigAction);
	//flare->runAction(smallAction);
}

void Effect::killSprite(Node* psender)
{
	if (psender)
	{
		psender->removeFromParent();
	}
}

void Effect::enemyExplode(Node* parent, const Vec2& pos)
{
	SpriteFrame* firstFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName("explosion_01.png");
	Sprite* explosion = Sprite::createWithSpriteFrame(firstFrame);
	explosion->setPosition(pos);
	parent->addChild(explosion);

	//��map�л�ȡ��ը����
	Animation* explosionAction = AnimationCache::getInstance()->getAnimation("explosion");
	auto removeExplosion = CallFunc::create([explosion]() {
		explosion->removeFromParent();
		});

	explosion->runAction(Sequence::create(Animate::create(explosionAction), removeExplosion, nullptr));
}

void Effect::enemySpark(Node* parent, const Vec2& pos, float scale, float duration)
{
	Sprite* one = Sprite::create(s_explode1);
	Sprite* two = Sprite::create(s_explode2);
	Sprite* three = Sprite::create(s_explode3);

	one->setPosition(pos);
	two->setPosition(pos);
	three->setPosition(pos);

	one->setScale(scale);
	two->setScale(scale);
	three->setScale(scale);

	three->setRotation(rand_0_1() * 360);

	parent->addChild(one);
	parent->addChild(two);
	parent->addChild(three);

	auto left = RotateBy::create(duration, -45);
	auto right = RotateBy::create(duration, 45);
	auto scaleby = ScaleBy::create(duration, scale);
	auto fadeout = FadeOut::create(duration);

	auto removeOne = CallFunc::create([one]() {
		one->removeFromParent();
		});
	auto removeTwo = CallFunc::create([two]() {
		two->removeFromParent();
		});
	auto removeThree = CallFunc::create([three]() {
		three->removeFromParent();
		});

	auto seqOne = Sequence::create(fadeout,removeOne,nullptr);

	one->runAction(left);
	one->runAction(scaleby);
	one->runAction(Spawn::create(left, scaleby, seqOne, nullptr));

	two->runAction(right);
	two->runAction(scaleby->clone());
	two->runAction(Sequence::create(fadeout->clone(), removeTwo, nullptr));

	three->runAction(scaleby->clone());
	three->runAction(Sequence::create(fadeout->clone(), removeThree, nullptr));

}