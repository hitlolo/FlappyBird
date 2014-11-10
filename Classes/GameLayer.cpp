
#include "GameLayer.h"

bool GameLayer::init(){

	if (!Layer::init()){
		return false;
	}

	this->loadRes();

	this->initPhysicsAttributes();

	this->setGameState(READY);

	return true;
}


void GameLayer::loadRes(){

	curScore = 0;

	Size visiableSize = Director::getInstance()->getVisibleSize();
	Point originPoint = Director::getInstance()->getVisibleOrigin();

	birdSprite = BirdSprite::create();
	birdSprite->setPosition(originPoint.x + visiableSize.width/4,originPoint.y + visiableSize.height/2);
	this->addChild(birdSprite);

	//pipeLayer = PipeLayer::create();
	//this->addChild(pipeLayer); 

	__NotificationCenter::getInstance()->addObserver(this, CC_CALLFUNCO_SELECTOR(GameLayer::startGame), MSG_GAME_START, nullptr);
	__NotificationCenter::getInstance()->addObserver(this, CC_CALLFUNCO_SELECTOR(GameLayer::getPoint), MSG_GET_POINT, nullptr);

}

void GameLayer::initPhysicsAttributes(){

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameLayer::onContact, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

}


void GameLayer::onTouch(){

	switch(curState){

	case READY:
		this->readyGame(CC_CALLBACK_0(GameLayer::steadyGame, this));
		break;
	case STEADY:
		return;
		break;
	case GAMING:
		this->onGaming();
		break;
	case OVER:
		return;
		break;
	default:
		return;
	}
}


//void TextureCache::addImageAsync(const std::string &path, const std::function<void(Texture2D*)>& callback)

void  GameLayer::readyGame(const std::function<void()> &callback){

	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(M_SWOOSH);
	this->getbulletinDelegator()->showBulletin(getGameState());
	callback();

}

void GameLayer::steadyGame(){

	this->setGameState(STEADY);
	this->getbulletinDelegator()->showBulletin(getGameState());
	
}

void  GameLayer::startGame(Ref* sender){

	this->setGameState(GAMING);
	this->getbulletinDelegator()->showBulletin(getGameState());
	birdSprite->birdRun(BIRD_STATE::STATE_FLY);
	__NotificationCenter::getInstance()->postNotification(MSG_PIPE_START);
	//pipeLayer->scheduleUpdate();

}



void  GameLayer::overGame(){

	this->birdSprite->birdRun(BIRD_STATE::STATE_DIE);
	this->setGameState(GAME_STATE::OVER);
	__NotificationCenter::getInstance()->postNotification(MSG_GAME_STOP);
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(M_HIT);

}

bool  GameLayer::onContact(PhysicsContact& contact){
	
	if (this->getGameState() == GAME_STATE::GAMING){
		this->overGame();
	}

	return true;
}

//touch
void GameLayer::onGaming(){

	this->birdSprite->gravityUp();
}


void  GameLayer::getPoint(Ref* sender){
	this->curScore++;
	this->bulletinDelegated->updateScore(curScore);

}