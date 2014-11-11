#ifndef __FB_INFO_LAYER_H__
#define __FB_INFO_LAYER_H__

/***********************************************************************************************

@ Project: Flappy Brid
@ Author:  Lolo
@ Date:    2014-11-3 19:02:33
@ File:    infoLayer.h
________________________________________________________________________________________________
@ Description:
Game Infomation Show
________________________________________________________________________________________________

************************************************************************************************/
#include "cocos2d.h"
#include "GameData.h"
#include "BirdSprite.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

class InfoLayer :public Layer{

public:

	virtual bool init() override;

	CREATE_FUNC(InfoLayer);

private:
	
	void loadInfo();

	//button callback function
	void gameStartCallback(Ref* sender);

	//game start
	void playGame();
};

#endif