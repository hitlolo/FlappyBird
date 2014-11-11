/***********************************************************************************************

@ Project: Flappy Brid
@ Author:  Lolo
@ Date:    2014-11-3 19:02:33
@ File:    infoScene.cpp
________________________________________________________________________________________________
@ Description:
Game Infomation Show
________________________________________________________________________________________________

************************************************************************************************/

#include "InfoScene.h"

/* @brif
** this scene have two children
*  1. the background layer
*  2. the infomation layer
*/
bool InfoScene::init()
{
	if ( !Scene::init() ){
		return false;
	}

	//do initialization;
	auto backLayer = BackGroundLayer::create(); 
	auto infoLayer = InfoLayer::create();

	this->addChild(backLayer);
	this->addChild(infoLayer);

	return true;
}