/***********************************************************************************************

@ Project: Flappy Brid
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


	Director::getInstance()->getTextureCache()->addImageAsync(RES_PNG, CC_CALLBACK_1(LoadingScene::loadOverCallback, this));
	//auto image = new Image();
	//image->initWithImageFile(PIC_ATLAS);
	//Director::getInstance()->getTextureCache()->addImage(image, PIC_ATLAS);
	//AtlasLoader::getInstance()->loadAtlas(TXT_LOADING, Director::getInstance()->getTextureCache()->getTextureForKey(PIC_ATLAS));

	return true;
	
	
}


/* @brif
** after the resoures loaded ,go to the next Scene;InfoScene to show the infomations about the game!
*/
void LoadingScene::loadOverCallback(Texture2D *texture)
{

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(RES_PLIST , texture);
	//load music
	this->loadMusic();

	auto nextScene = InfoScene::create();
	TransitionScene *transition = TransitionFade::create(2, nextScene);
	Director::getInstance()->replaceScene(transition);
}


void LoadingScene::loadMusic()
{
	SimpleAudioEngine::getInstance()->preloadEffect(M_DIE);
	SimpleAudioEngine::getInstance()->preloadEffect(M_HIT);
	SimpleAudioEngine::getInstance()->preloadEffect(M_GETPOINT);
	SimpleAudioEngine::getInstance()->preloadEffect(M_WING);
	SimpleAudioEngine::getInstance()->preloadEffect(M_SWOOSH);
}
