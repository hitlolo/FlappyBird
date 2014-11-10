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
	//ע��������ߴ������������
	auto scene = Scene::createWithPhysics();
	//������������GRAVITY��ֵΪ��0��-980��
	//�����ǵ������������ٶ���һ���ģ��Ƚ���ʵ
	scene->getPhysicsWorld()->setGravity(GRAVITY);
	scene->addChild(GameScene::create());
	return scene;
}


bool GameScene::init(){

	if (!Layer::init()){
		return false;
	}

	//auto backLayer = BackGroundLayer::create();
	//this->addChild(backLayer);
	//

	//auto bulletinLayer = BulletinBoard::create();
	//this->addChild(bulletinLayer);

	auto gameLayer = GameLayer::create();
	//gameLayer->setbulletinDelegator(bulletinLayer);
	this->addChild(gameLayer);

	auto touchLayer = TouchLayer::create();
	touchLayer->setDelegator(gameLayer);
	this->addChild(touchLayer);


	return true;
}
