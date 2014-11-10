/***********************************************************************************************

@ Project: Flappy Brid
@ Author:  Lolo
@ Date:    2014-11-4 23:42:32
@ File:    BulletinBoard.cpp
________________________________________________________________________________________________
@ Description:
show the infomations of the game.
such as score,and gamme over
________________________________________________________________________________________________

************************************************************************************************/


#include "BulletinBoard.h"

bool BulletinBoard::init(){
	
	if (!Layer::init()){
		return false;
	}
	count = 3;
	this->loadRes();
	//this->showReady();

	return true;
	
}

void BulletinBoard::loadRes(){

	this->originPoint  = Director::getInstance()->getVisibleOrigin();
	this->visiableSize = Director::getInstance()->getVisibleSize();
	this->newRecord	   = false;
}



void BulletinBoard::showBulletin(int GAME_STATE){

	CCLOG("%d%__GAME_STATE", GAME_STATE);
	switch (GAME_STATE){

	case READY:
		this->showReady();
		break;
	case STEADY:
		this->showSteady(CC_CALLBACK_0(BulletinBoard::countDown, this));
		break;
	case GAMING:
		this->showGaming();
		break;
	case OVER:
		this->showGameOver();
		break;
	default:
		CCLOG("WHAT THE FUCK!");
		break;
	}

}

void BulletinBoard::showReady(){

	this->readySprite = Sprite::createWithSpriteFrameName(PIC_READY);
	readySprite->setPosition(originPoint.x + visiableSize.width/2, originPoint.y + visiableSize.height/10 *8);
	this->addChild(readySprite);

	this->tutorialSprite = Sprite::createWithSpriteFrameName(PIC_TUTOR);
	tutorialSprite->setPosition(originPoint.x + visiableSize.width/2, originPoint.y + visiableSize.height/2);
	ActionInterval* fade     = CCFadeOut::create(1.0f);
	ActionInterval* fadeBack = fade->reverse();
	tutorialSprite->runAction( RepeatForever::create(Sequence::create(fade, fadeBack, nullptr)));
	this->addChild(tutorialSprite);


}

void BulletinBoard::showSteady(const std::function<void(void)> &callback){

	tutorialSprite->stopAllActions();
	auto scale = CCScaleBy::create(0.2f,1.8f);
	auto fade = CCFadeOut::create(0.3f);
	auto fadeout = Spawn::createWithTwoActions(scale,fade);
	this->readySprite->runAction(fadeout);
	this->tutorialSprite->runAction(CCFadeOut::create(0.3f));

	callback();

}

void BulletinBoard::showGaming(){

	//this->scoreSprite = Sprite::createWithSpriteFrameName("font_048.png");
	//scoreSprite->setPosition(originPoint.x + visiableSize.width / 2, originPoint.y + visiableSize.height / 10 * 8);
	//scoreSprite->setName(NAME_SCORE);
	//this->addChild(scoreSprite);


}

void BulletinBoard::showGameOver(){

}


void BulletinBoard::countDown(){

	//Vector<SpriteFrame*> vector;
	//vector.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("font_051.png"));
	//vector.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("font_050.png"));
	//vector.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("font_049.png"));
	//auto animation = Animation::createWithSpriteFrames(vector);
	//animation->setDelayPerUnit(1.0f);
	//auto animate = Animate::create(animation);
	//auto countdown = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("font_051.png"));
	//countdown->setPosition(originPoint.x + visiableSize.width/2, originPoint.y + visiableSize.height/10 *8);
	//this->addChild(countdown);
	////CallFunc * CallFunc::create(const std::function<void()> &func)
	//auto action = Sequence::create(animate, FadeOut::create(0.2f), CallFunc::create(CC_CALLBACK_0(BulletinBoard::sendGameStartMsg, this)), nullptr);
	//countdown->runAction(action);

	//Label

	////初始化分数
	//score = 0;
	////这是自定义字体的使用
	//auto str = __String::createWithFormat("%d", score);
	//numberLabel = Label::createWithBMFont("font1.fnt", str->getCString());
	//numberLabel->setPosition(Point(origin.x + visibleSize.width / 2, origin.y + visibleSize.height*0.85));
	//this->addChild(numberLabel);
	auto str   = String::createWithFormat("%d",count);
	scoreLabel = Label::createWithBMFont(FONT_BIG,str->getCString());
	scoreLabel->setPosition(originPoint.x + visiableSize.width / 2, originPoint.y + visiableSize.height / 10 * 8);
	this->addChild(scoreLabel);
	if (count > 0)
	{
		this->schedule(CC_SCHEDULE_SELECTOR(BulletinBoard::countDownAnimation), 1.0f);
	}



	
}

void BulletinBoard::countDownAnimation(float dt){

	--count;

	if (count != 0){

		auto action = ScaleBy::create(0.3f, 1.3f);
		auto action_ = action->reverse();
		scoreLabel->runAction(Sequence::create(action, action_, nullptr));
	}

	auto str = String::createWithFormat("%d", count);
	scoreLabel->setString(str->getCString());
	
	// start game
	if (count == 0)
	{
		this->unschedule(CC_SCHEDULE_SELECTOR(BulletinBoard::countDownAnimation));
		
		//game start
		auto game = dynamic_cast<GameLayer*>(this->getParent());
		if (!game)
			return;
		else
			game->startGame();
	}

}


void BulletinBoard::updateScore(int score){
	auto str = String::createWithFormat("%d", score);
	scoreLabel->setString(str->getCString());
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(M_GETPOINT);
}


void BulletinBoard::removeScoreLabel(){

	this->removeChild(this->scoreLabel);

}