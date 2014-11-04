/***********************************************************************************************

@ Project: flappy brid
@ Author:  Lolo
@ Date:    2014-11-3 17:02:33
@ File:    LoadingScene.cpp
________________________________________________________________________________________________
@ Description:
Game Loading
________________________________________________________________________________________________

************************************************************************************************/
#include"LoadingScene.h"

USING_NS_CC;


Scene* LoadingScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = LoadingScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}


bool LoadingScene::init()
{
	if (!Layer::init()){

		return false;
	}

	//do the initialization works

	//1.add background
	auto background = Sprite::create(PIC_LOADING);
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(background);

	return true;
	
	
}

void LoadingScene::onEnter()
{
	// start ansyc method load the atlas.png
	Director::getInstance()->getTextureCache()->addImageAsync(PIC_ATLAS, CC_CALLBACK_1(LoadingScene::loadOverCallback, this));
}


void LoadingScene::loadOverCallback(Texture2D *texture)
{
	AtlasLoader::getInstance()->loadAtlas(TXT_LOADING, texture);

	//load music
	this->loadMusic();
}


void LoadingScene::loadMusic()
{
	SimpleAudioEngine::getInstance()->preloadEffect(M_DIE);
	SimpleAudioEngine::getInstance()->preloadEffect(M_HIT);
	SimpleAudioEngine::getInstance()->preloadEffect(M_GETPOINT);
	SimpleAudioEngine::getInstance()->preloadEffect(M_WING);
	SimpleAudioEngine::getInstance()->preloadEffect(M_SWOOSH);
}