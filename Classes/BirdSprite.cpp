/***********************************************************************************************

@ Project: Flappy Brid
@ Author:  Lolo
@ Date:    2014-11-3 21:32:32
@ File:    BirdSprite.cpp
________________________________________________________________________________________________
@ Description:
Bird
________________________________________________________________________________________________

************************************************************************************************/

#include "BirdSprite.h"


BirdSprite::BirdSprite()
{
	actionIdle  = nullptr;

	actionSwing = nullptr;

	curState    = BIRD_STATE::STATE_IDEL;
}


BirdSprite::~BirdSprite()
{
	actionIdle = nullptr;

	actionSwing = nullptr;
}


bool BirdSprite::init()
{
	if (!Sprite::init()){
		return false;
	}

	this->createBird();
	this->scheduleUpdate();
	this->birdRun(curState);

	return true;
}

void BirdSprite::initPhysicsAttributes(){

	PhysicsBody *body = PhysicsBody::create();
	body->addShape(PhysicsShapeCircle::create(BIRD_RADIUS));
	body->setCategoryBitmask(ColliderTypeBird);
	body->setCollisionBitmask(ColliderTypeLand | ColliderTypePip);
	body->setContactTestBitmask(ColliderTypeLand | ColliderTypePip);

	body->setDynamic(true);
	body->setLinearDamping(1.0f);
	body->setGravityEnable(false);
	this->setPhysicsBody(body);

}


int BirdSprite::selectRandomColor()
{
	srand((unsigned)time(NULL));
	return ((int)rand()) % 3;
}


void BirdSprite::createBird()
{
	std::string name;
	std::string name_format;
	int color = selectRandomColor();
	switch (color){

		case YELLOW:
			name = "bird0_0.png";
			name_format = "bird0_%d.png";
			break;
		case GREEN:
			name = "bird1_0.png";
			name_format = "bird1_%d.png";
			break;
		case RED:
			name = "bird2_0.png";
			name_format = "bird2_%d.png";
			break;
	}

	//CCLOG("%s    from init bird",name.c_str());
	this->initWithSpriteFrame( SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
	
	this->initAnimation(name_format,3,0.2f);

	this->initPhysicsAttributes();
}


void BirdSprite::initAnimation(std::string name, int img_count, float ft)
{

	Animation* animation = Animation::create();
	for (int i = 0; i < img_count; i++){
		String* file_name  = String::createWithFormat(name.c_str(), i);
		//CCLOG("%s", file_name->getCString());
		SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(file_name->getCString());
		animation->addSpriteFrame(frame);
	}
	animation->setDelayPerUnit(ft);
	Animate* animate = Animate::create(animation);
	//bind
	this->actionIdle = RepeatForever::create(animate);

	// create the swing action
	ActionInterval* up     = CCMoveBy::create(0.4f, Point(0, 8));
	ActionInterval* upBack = up->reverse();
	//bind
	this->actionSwing = RepeatForever::create(Sequence::create(up, upBack, nullptr));


}



void BirdSprite::idle()
{
	this->runAction(actionIdle);
	this->runAction(actionSwing);
	this->getPhysicsBody()->setGravityEnable(false);
}


void BirdSprite::fly()
{
	this->stopAction(actionSwing);
	this->getPhysicsBody()->setGravityEnable(true);
	
}


void BirdSprite::die()
{

	//播放音效
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(M_DIE);
	//关闭定时器
	this->unscheduleUpdate();

	this->getPhysicsBody()->setGravityEnable(true);
	//停止小鸟的所有动画
	this->stopAllActions();
	//设置角度，头向下...
	this->setRotation(90);


}


void BirdSprite::birdRun(BIRD_STATE curState)
{
	switch (curState){

		case BIRD_STATE::STATE_IDEL:
			this->setState(curState);
			this->idle();
			break;
		case BIRD_STATE::STATE_FLY:
			this->setState(curState);
			this->fly();
			break;
		case BIRD_STATE::STATE_DIE:
			this->setState(curState);
			this->die();
			break;
		default:
			CCLOG("BUG HERE IN BIRD RUN!");
			return;
	}

}


void BirdSprite::gravityDown(){

	

}

void BirdSprite::gravityUp(){

	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(M_WING);
	//给小鸟一个初速度
	this->getPhysicsBody()->setVelocity(VELOCITY);
}

void BirdSprite::update(float){

	auto origin = Director::getInstance()->getVisibleOrigin();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	//防止飞出边界
	if (this->getPositionY()>(origin.y + visibleSize.height))
	{
		this->setPositionY(origin.y + visibleSize.height);
	}
	//小鸟的飞行头部的角度，根据飞行的Y轴速度决定
	this->setRotation(this->getPhysicsBody()->getVelocity().y*-0.1);
}