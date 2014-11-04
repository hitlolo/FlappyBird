/***********************************************************************************************

@ Project: flappy brid
@ Author:  Lolo
@ Date:    2014-11-3 19:02:33
@ File:    infoScene.cpp
________________________________________________________________________________________________
@ Description:
Game Infomation Show
________________________________________________________________________________________________

************************************************************************************************/

#include "InfoScene.h"

bool InfoScene::init()
{
	if ( !Scene::init() ){
		return false;
	}

	//do initialization;
	auto infoLayer = InfoLayer::create();
	auto backLayer = BackGroundLayer::create(); 
	this->addChild(backLayer);
	this->addChild(infoLayer);
}