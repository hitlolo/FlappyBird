/***********************************************************************************************

@ Project: Flappy Brid
@ Author:  Lolo
@ Date:    2014-11-4 23:42:32
@ File:    GameScene.cpp
________________________________________________________________________________________________
@ Description:
Main Game Scene
________________________________________________________________________________________________

************************************************************************************************/

#include "GameScene.h"

bool GameScene::init(){

	if (!Scene::initWithPhysics()){
		return false;
	}

	auto backLayer = BackGroundLayer::create();
	this->addChild(backLayer);
	

	auto bulletinLayer = BulletinBoard::create();
	this->addChild(bulletinLayer);

	auto gameLayer = GameLayer::create();
	gameLayer->setbulletinDelegator(bulletinLayer);
	this->addChild(gameLayer);

	auto touchLayer = TouchLayer::create();
	touchLayer->setDelegator(gameLayer);
	this->addChild(touchLayer);

	initPhysicsAttributes();

	return true;
}

void GameScene::initPhysicsAttributes(){

	this->getPhysicsWorld()->setGravity(GRAVITY);

}
