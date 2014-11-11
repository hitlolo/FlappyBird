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


Scene * GameScene::createScene()
{
	//注意我们这边创造的是物理场景
	auto scene = Scene::createWithPhysics();
	//加入了重力，GRAVITY的值为（0，-980）
	//跟我们的世界重力加速度是一样的，比较真实
	scene->getPhysicsWorld()->setGravity(GRAVITY);
	scene->addChild(GameScene::create());
	return scene;
}

/* @brif
** two children
* 1.game layer which have the background and bulletinboard,and also deal about the game method.
* 2.touch layer, which is designed to deal with the touch action.
*/
bool GameScene::init(){

	if (!Layer::init()){
		return false;
	}

	auto gameLayer = GameLayer::create();
	this->addChild(gameLayer);

	auto touchLayer = TouchLayer::create();
	touchLayer->setDelegator(gameLayer);
	this->addChild(touchLayer);


	return true;
}
