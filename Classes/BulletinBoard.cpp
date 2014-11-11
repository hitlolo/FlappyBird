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
	//initialize the counting down number
	count = 3;
	this->loadRes();

	return true;
	
}

void BulletinBoard::loadRes(){

	this->originPoint    = Director::getInstance()->getVisibleOrigin();
	this->visiableSize   = Director::getInstance()->getVisibleSize();
	this->fireworkSprite = nullptr;
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

//steady state
//1.
void BulletinBoard::showSteady(const std::function<void(void)> &callback){

	tutorialSprite->stopAllActions();
	auto scale   = CCScaleBy::create(0.2f,1.8f);
	auto fade    = CCFadeOut::create(0.3f);
	auto fadeout = Spawn::createWithTwoActions(scale,fade);
	this->readySprite->runAction(fadeout);
	this->tutorialSprite->runAction(CCFadeOut::create(0.3f));

	callback();

}

//steady state
//2.
void BulletinBoard::countDown(){

	auto str   = String::createWithFormat("%d",count);
	scoreLabel = Label::createWithBMFont(FONT_BIG,str->getCString());
	scoreLabel->setPosition(originPoint.x + visiableSize.width / 2, originPoint.y + visiableSize.height / 10 * 8);
	this->addChild(scoreLabel);
	if (count > 0)
	{
		this->schedule(CC_SCHEDULE_SELECTOR(BulletinBoard::countDownAnimation), 1.0f);
	}
	
}

//steady state
//3.
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


//gaming state
//1.

// moved to the scoreLabel
void BulletinBoard::showGaming(){

	//this->scoreSprite = Sprite::createWithSpriteFrameName("font_048.png");
	//scoreSprite->setPosition(originPoint.x + visiableSize.width / 2, originPoint.y + visiableSize.height / 10 * 8);
	//scoreSprite->setName(NAME_SCORE);
	//this->addChild(scoreSprite);

}


//gaming state
//2.
void BulletinBoard::updateScore(int score){
	auto str = String::createWithFormat("%d", score);
	scoreLabel->setString(str->getCString());
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(M_GETPOINT);
}


//game over state
//1.
void BulletinBoard::showGameOver(){

	blinkScreen();

}

void  BulletinBoard::blinkScreen(){

	auto white = CCSprite::createWithSpriteFrameName("white.png");
	float scale = (visiableSize.height / white->getContentSize().height);
	white->setScale(scale);
	white->setPosition(originPoint.x + visiableSize.width / 2, originPoint.y + visiableSize.height / 2);
	this->addChild(white);
	auto fadeOut = FadeOut::create(0.1f);
	auto fadeIn = FadeIn::create(0.1f);
	CallFunc *actionDone = CallFunc::create(std::bind(&BulletinBoard::fadeinPanel, this));
	auto blinkAction = Sequence::create(fadeIn, fadeOut, actionDone, nullptr);

	white->stopAllActions();
	white->runAction(blinkAction);
}


//game over state
//2.
void BulletinBoard::removeScoreLabel(){

	this->removeChild(this->scoreLabel);

}


//game over state
//3.
void  BulletinBoard::fadeinPanel(){

	//get point
	sscanf(scoreLabel->getString().c_str(), "%d", &curScore);
	CCLOG("%d,current score!",curScore);
	this->removeChild(scoreLabel);

	//add game over panel
	auto overSprite = Sprite::createWithSpriteFrameName("text_game_over.png");
	overSprite->setPosition(originPoint.x + visiableSize.width / 2, originPoint.y + visiableSize.height / 10 * 8);
	this->addChild(overSprite);
	//add score panel

	auto scorePanel = Sprite::createWithSpriteFrameName("score_panel.png");
	scorePanel->setPosition(originPoint.x + visiableSize.width / 2, originPoint.y - scorePanel->getContentSize().height);
	ActionInterval* panel_up = MoveTo::create(0.2f, Point(originPoint.x + visiableSize.width / 2, originPoint.y + visiableSize.height / 10 * 6));
	this->addChild(scorePanel);
	scorePanel->runAction(panel_up);
	//add score

	scoreLabel = Label::createWithBMFont(FONT_SMALL, "0", TextHAlignment::CENTER);
	scoreLabel->setAnchorPoint(Point(1, 1));
	scoreLabel->setPosition(scorePanel->getContentSize().width - 28, scorePanel->getContentSize().height -32);
	scorePanel->addChild(scoreLabel);
	//score animation
	if (curScore > 0)
	{
		this->count = 0;
		this->schedule(CC_SCHEDULE_SELECTOR(BulletinBoard::addScoreAnimation), 0.3f);
	}

	//best score
	int bestScore = UserDefault::getInstance()->getIntegerForKey("best_score");

	String *str = String::createWithFormat("%d", ((curScore > bestScore)? curScore:bestScore));
	auto bestLabel = Label::createWithBMFont(FONT_SMALL, str->getCString(), TextHAlignment::CENTER);
	bestLabel->setAnchorPoint(Point(1, 1));
	bestLabel->setPosition(scorePanel->getContentSize().width - 28, 50);
	scorePanel->addChild(bestLabel);

	if (curScore > bestScore){

		bestScore = curScore;
		UserDefault::getInstance()->setIntegerForKey("best_score", bestScore);

		auto newTag = Sprite::createWithSpriteFrameName("new.png");
		newTag->setAnchorPoint(Point(1, 1));
		newTag->setPosition(scorePanel->getContentSize().width - 28 - bestLabel->getContentSize().width -5, 48);
		scorePanel->addChild(newTag);

	}

	//medal

	if (curScore >= 5){
		
		std::string medalName;
		if (curScore < 10){
			medalName = "medals_0.png";
		}
		else if (curScore >= 10 && curScore <= 15){
			medalName = "medals_1.png";
		}
		else if (curScore > 15 && curScore <= 20){
			medalName = "medals_2.png";
		}
		else if (curScore > 20 ){
			medalName = "medals_3.png";
		}
		this->getFirework();
		auto medalsSprite = Sprite::createWithSpriteFrameName(medalName.c_str());
		medalsSprite->addChild(this->fireworkSprite);
		medalsSprite->setPosition(54, 58);
		scorePanel->addChild(medalsSprite);

	}

	//button
	auto buttonStart_n = Sprite::createWithSpriteFrameName(PIC_B_PLAY);
	auto buttonStart_p = Sprite::createWithSpriteFrameName(PIC_B_PLAY);
	buttonStart_n->setPositionY(5);

	auto buttonBoard_n = Sprite::createWithSpriteFrameName(PIC_B_BOARD);
	auto buttonBoard_p = Sprite::createWithSpriteFrameName(PIC_B_BOARD);
	buttonBoard_n->setPositionY(5);

	auto item_restart = MenuItemSprite::create(buttonStart_n, buttonStart_p, CC_CALLBACK_1(BulletinBoard::restartGame, this));
	item_restart->setPosition(Point(originPoint.x + visiableSize.width / 2 - item_restart->getContentSize().width / 2, originPoint.y + visiableSize.height / 10 * 3.7));

	auto item_board = MenuItemSprite::create(buttonBoard_n, buttonBoard_p, CC_CALLBACK_1(BulletinBoard::scoreBoard, this));
	item_board->setPosition(Point(originPoint.x + visiableSize.width / 2 + item_board->getContentSize().width / 2, originPoint.y + visiableSize.height / 10 * 3.7));

	auto menu = Menu::create(item_restart, item_board, nullptr);
	menu->setPosition(Point::ZERO);
	this->addChild(menu);

}

void BulletinBoard::restartGame(Ref* sender){

	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(M_SWOOSH);

	auto nextScene = GameScene::createScene();
	TransitionScene *transition = TransitionFade::create(0.2f, nextScene);
	Director::getInstance()->replaceScene(transition);
}

void BulletinBoard::scoreBoard(Ref* sender){

	CCLOG("hi,there!");
}

void BulletinBoard::addScoreAnimation(float dt){

	++count;

	auto str = String::createWithFormat("%d", count);
	scoreLabel->setString(str->getCString());

	// start game
	if (count == curScore)
	{
		this->unschedule(CC_SCHEDULE_SELECTOR(BulletinBoard::addScoreAnimation));
	}
	
}

void BulletinBoard::getFirework(){

	std::string filename;
	this->fireworkSprite = Sprite::createWithSpriteFrameName("blink_00.png");
	Animation* animation = Animation::create();
	for (int i = 0; i < 3; i++){
		filename = String::createWithFormat("blink_0%d.png", i)->getCString();
		SpriteFrame *frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(filename.c_str());
		animation->addSpriteFrame(frame);
	}
	for (int i = 2; i >= 0; i--){
		filename = String::createWithFormat("blink_0%d.png", i)->getCString();
		SpriteFrame *frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(filename.c_str());
		animation->addSpriteFrame(frame);
	}
	animation->setDelayPerUnit(0.1f);
	auto animate = Animate::create(animation);
	auto actionDone = CallFunc::create(std::bind(&BulletinBoard::showFirework, this));
	auto sequence = Sequence::createWithTwoActions(animate, actionDone);
	fireworkSprite->runAction(RepeatForever::create(sequence));
}

void  BulletinBoard::showFirework(){
	if (fireworkSprite != nullptr){

		Size activeSize = this->fireworkSprite->getParent()->getContentSize();
		this->fireworkSprite->setPosition(rand() % ((int)(activeSize.width)), rand() % ((int)(activeSize.height)));
	}
}