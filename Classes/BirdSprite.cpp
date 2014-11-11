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

void BirdSprite::initAnimation(std::string name, int img_count, float ft)
{

	Animation* animation = Animation::create();
	for (int i = 0; i < img_count; i++){
		String* file_name = String::createWithFormat(name.c_str(), i);
		//CCLOG("%s", file_name->getCString());
		SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(file_name->getCString());
		animation->addSpriteFrame(frame);
	}
	animation->setDelayPerUnit(ft);
	Animate* animate = Animate::create(animation);
	//bind
	this->actionIdle = RepeatForever::create(animate);

	// create the swing action
	ActionInterval* up = CCMoveBy::create(0.4f, Point(0, 8));
	ActionInterval* upBack = up->reverse();
	//bind
	this->actionSwing = RepeatForever::create(Sequence::create(up, upBack, nullptr));


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

	this->initWithSpriteFrame( SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
	
	this->initAnimation(name_format,3,0.2f);

	this->initPhysicsAttributes();
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
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(M_DIE);
	this->unscheduleUpdate();
	this->getPhysicsBody()->setGravityEnable(true);
	this->stopAllActions();
	//90 degree .head down!
	this->setRotation(90);
	this->runAction(FadeOut::create(0.9f));


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
	//give bird a velocity to fly up
	this->getPhysicsBody()->setVelocity(VELOCITY);
}

//scheduled
void BirdSprite::update(float){

	auto origin = Director::getInstance()->getVisibleOrigin();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	//avoid to corss the bound
	if (this->getPositionY()>(origin.y + visibleSize.height))
	{
		this->setPositionY(origin.y + visibleSize.height);
	}
	//set the angle of the bird depends on the velocity.
	this->setRotation(this->getPhysicsBody()->getVelocity().y*-0.1);
}