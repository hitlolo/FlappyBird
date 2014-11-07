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
	this->birdRun();

	return true;
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

	CCLOG("%s    from init bird",name.c_str());
	this->initWithSpriteFrame( SpriteFrameCache::getInstance()->getSpriteFrameByName(name));
	
	this->initAnimation(name_format,3,0.2f);


}


void BirdSprite::initAnimation(std::string name, int img_count, float ft)
{

	//Animation *animation = animation::create();
	//Animation->setdelayperunit(1 / fps);
	//for (int i = 0; i < count; i++){
	//	const char *filename = string::createwithformat(fmt, i)->getcstring();
	//	spriteframe *frame = atlasloader::getinstance()->getspriteframebyname(filename);
	//	animation->addspriteframe(frame);
	//}
	CCLOG("%s",name.c_str());
	Animation* animation = Animation::create();
	for (int i = 0; i < img_count; i++){
		String* file_name  = String::createWithFormat(name.c_str(), i);
		CCLOG("%s", file_name->getCString());
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
	this->setState(BIRD_STATE::STATE_IDEL);
	this->runAction(actionIdle);
	this->runAction(actionSwing);
}


void BirdSprite::fly()
{
	this->setState(BIRD_STATE::STATE_FLY);
	this->stopAction(actionSwing);
	
}


void BirdSprite::die()
{
	this->setState(BIRD_STATE::STATE_DIE);
}


void BirdSprite::birdRun()
{
	switch (this->getState()){

		case BIRD_STATE::STATE_IDEL:
			this->idle();
			break;
		case BIRD_STATE::STATE_FLY:
			this->fly();
			break;
		case BIRD_STATE::STATE_DIE:
			this->die();
			break;
		default:
			CCLOG("BUG HERE IN BIRD RUN!");
			return;
	}

}