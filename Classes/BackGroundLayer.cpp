/***********************************************************************************************

@ Project: Flappy Brid
@ Author:  Lolo
@ Date:    2014-11-3 19:02:33
@ File:    BackGroundLayer.cpp
________________________________________________________________________________________________
@ Description:
the whole game's backgroud Layer
________________________________________________________________________________________________

************************************************************************************************/


#include "BackGroundLayer.h"

bool BackGroundLayer::init()
{
	if (!Layer::init()){
		return false;
	}

	this->initBackGround();
	this->initPhysicsAttributes();
	this->scrollingStart();
	__NotificationCenter::getInstance()->addObserver(this, CC_CALLFUNCO_SELECTOR(BackGroundLayer::scrollingEnd), MSG_GAME_STOP, nullptr);
	__NotificationCenter::getInstance()->addObserver(this, CC_CALLFUNCO_SELECTOR(BackGroundLayer::pipeScrollStart), MSG_PIPE_START, nullptr);
	return true;
}

void BackGroundLayer::onExit(){
	Layer::onExit();
	__NotificationCenter::getInstance()->removeObserver(this, MSG_GAME_STOP);
	__NotificationCenter::getInstance()->removeObserver(this, MSG_PIPE_START);
}

int BackGroundLayer::getLocalTime()
{

	struct tm* s_time;
	time_t t = time(&t);
	s_time   = localtime(&t);

	return s_time->tm_hour;
}



void BackGroundLayer::initBackGround()
{
	int hour = this->getLocalTime();

	Sprite* background = nullptr;
	if (hour >= 7 && hour <= 19)
	{
		//background is an autorelease object
		background = Sprite::createWithSpriteFrameName(PIC_BG_DAY);
	}
	else
	{
		background = Sprite::createWithSpriteFrameName(PIC_BG_NIGHT);
	}
	background->setAnchorPoint(Point::ZERO);
	background->setPosition(Point::ZERO);
	this->addChild(background);

	//------------------------------------------
	Size  visibleSize = Director::getInstance()->getVisibleSize();
	Point originPoint = Director::getInstance()->getVisibleOrigin();

	auto scrollLand_f = Sprite::createWithSpriteFrameName(PIC_BG_LAND);
	auto scrollLand_s = Sprite::createWithSpriteFrameName(PIC_BG_LAND);
	
	scrollLand_f->setAnchorPoint(Point::ZERO);
	scrollLand_s->setAnchorPoint(Point::ZERO);
	
	scrollLand_f->setPosition(Point::ZERO);
	scrollLand_s->setPosition( scrollLand_f->getContentSize().width - 2.0f,0 );

	scrollLand_f->setName("land_f");
	scrollLand_s->setName("land_s");

	pipeLayer = PipeLayer::create();
	this->addChild(pipeLayer);

	this->addChild(scrollLand_f);
	this->addChild(scrollLand_s);

}



void BackGroundLayer::landScrolling(float dt)
{
	auto land_f = this->getChildByName("land_f");
	auto land_s = this->getChildByName("land_s");
	land_f->setPositionX(land_f->getPositionX() - 2.0f);
	land_s->setPositionX(land_f->getPositionX() + land_f->getContentSize().width - 2.0f);

	if (land_s->getPositionX() == 0)
	{
		land_f->setPositionX(0);
	}
		
	
}



void BackGroundLayer::scrollingStart()
{
	this->schedule(CC_SCHEDULE_SELECTOR(BackGroundLayer::landScrolling),0.02f);

}

void BackGroundLayer::scrollingEnd(Ref* sender)
{

	if (this->isScheduled(CC_SCHEDULE_SELECTOR(BackGroundLayer::landScrolling))){

		this->unschedule(CC_SCHEDULE_SELECTOR(BackGroundLayer::landScrolling));
		CCLOG("!!!!!!!!!!!!!!unschedule!!!!!!!!!!!!!");
		pipeLayer->unscheduleUpdate();
	}
	
}



//void BackGroundLayer::onExit()
//{
//	Layer::onExit();
//	this->scrollingEnd(nullptr);
//}

void BackGroundLayer::initPhysicsAttributes(){

	Size  visibleSize = Director::getInstance()->getVisibleSize();
	Point originPoint = Director::getInstance()->getVisibleOrigin();

	auto  groundNode = Node::create();
	float landWidth  = this->getChildByName("land_f")->getContentSize().width;
	float landHeight = this->getChildByName("land_f")->getContentSize().height;
	//CCLOG("%f  %f", landWidth, landHeight);
	auto groundBody = PhysicsBody::create();
	groundBody->addShape(PhysicsShapeBox::create(Size(landWidth, landHeight)));
	groundBody->setDynamic(false);
	groundBody->setGravityEnable(false);
	groundBody->setLinearDamping(0.0f);
	groundBody->setCategoryBitmask(ColliderTypeLand);
	groundBody->setCollisionBitmask(ColliderTypeBird);
	groundBody->setContactTestBitmask(ColliderTypeBird);

	//
	groundNode->setPhysicsBody(groundBody);
	//CCLOG("%f  %f", originPoint.x + visibleSize.width / 2, landHeight / 2);
	groundNode->setPosition(originPoint.x + visibleSize.width/2, landHeight / 2);
	this->addChild(groundNode);

}


void BackGroundLayer::pipeScrollStart(Ref* sender){

	this->pipeLayer->scheduleUpdate();
}