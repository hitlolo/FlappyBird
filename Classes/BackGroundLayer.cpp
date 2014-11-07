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
	this->scrollingStart();

	return true;
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
	Size  visibleSize = Director::sharedDirector()->getVisibleSize();
	Point originPoint = Director::sharedDirector()->getVisibleOrigin();

	auto scrollLand_f = Sprite::createWithSpriteFrameName(PIC_BG_LAND);
	auto scrollLand_s = Sprite::createWithSpriteFrameName(PIC_BG_LAND);
	
	scrollLand_f->setAnchorPoint(Point::ZERO);
	scrollLand_s->setAnchorPoint(Point::ZERO);
	
	scrollLand_f->setPosition(Point::ZERO);
	scrollLand_s->setPosition( scrollLand_f->getContentSize().width - 2.0f,0 );

	scrollLand_f->setName("land_f");
	scrollLand_s->setName("land_s");

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

void BackGroundLayer::scrollingEnd()
{
	if (this->isScheduled(CC_SCHEDULE_SELECTOR(BackGroundLayer::landScrolling))){

		this->unschedule(CC_SCHEDULE_SELECTOR(BackGroundLayer::landScrolling));

	}
	
}



void BackGroundLayer::onExit()
{
	Layer::onExit();
	this->scrollingEnd();
}