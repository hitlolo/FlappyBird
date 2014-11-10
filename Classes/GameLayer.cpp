
#include "GameLayer.h"

bool GameLayer::init(){

	if (!Layer::init()){
		return false;
	}


	this->setTouchEnabled(false);

	this->loadRes();

	this->initPhysicsAttributes();

	this->setGameState(READY);

	//start game

	/*this->readyGame(CC_CALLBACK_0(GameLayer::steadyGame, this));*/
	this->readyGame();

	return true;
}


void GameLayer::loadRes(){

	//curScore = 0;

	Size visiableSize = Director::getInstance()->getVisibleSize();
	Point originPoint = Director::getInstance()->getVisibleOrigin();


	backLayer = BackGroundLayer::create();
	this->addChild(backLayer);


	auto boardLayer = BulletinBoard::create();
	this->addChild(boardLayer);



	birdSprite = BirdSprite::create();
	birdSprite->setPosition(originPoint.x + visiableSize.width/4,originPoint.y + visiableSize.height/2);
	this->addChild(birdSprite);

	this->setbulletinDelegator(boardLayer);
	this->backLayer->setPipeDelegator(boardLayer);

}

void GameLayer::initPhysicsAttributes(){

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameLayer::onContact, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

}


void GameLayer::onTouch(){

	switch(curState){

	case READY:
		this->steadyGame();
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

//void  GameLayer::readyGame(const std::function<void()> &callback){
void  GameLayer::readyGame(){

	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(M_SWOOSH);
	this->getbulletinDelegator()->showBulletin(getGameState());
	

}

void GameLayer::steadyGame(){

	this->setGameState(STEADY);
	this->getbulletinDelegator()->showBulletin(getGameState());
	
}

void  GameLayer::startGame(){

	this->setGameState(GAMING);
	this->getbulletinDelegator()->showBulletin(getGameState());
	this->birdSprite->birdRun(BIRD_STATE::STATE_FLY);
	this->backLayer->startGame();
}



void  GameLayer::overGame(){

	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(M_HIT);
	this->birdSprite->birdRun(BIRD_STATE::STATE_DIE);
	this->setGameState(GAME_STATE::OVER);
	this->backLayer->overGame();
	this->getbulletinDelegator()->showBulletin(getGameState());

	//score

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


//void  GameLayer::getPoint(Ref* sender){
//	this->curScore++;
//	this->bulletinDelegated->updateScore(curScore);
//
//}