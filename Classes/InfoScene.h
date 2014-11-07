#ifndef __FB_INFO_H__
#define __FB_INFO_H__

/***********************************************************************************************

@ Project: Flappy Brid
@ Author:  Lolo
@ Date:    2014-11-3 19:02:33
@ File:    infoScene.h
________________________________________________________________________________________________
@ Description:
Game Infomation Show
________________________________________________________________________________________________

************************************************************************************************/

#include "cocos2d.h"
#include "InfoLayer.h"
#include "BackGroundLayer.h"


USING_NS_CC;

class InfoScene :public Scene{

private:

public:

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init() override;


	// implement the "static create()" method manually
	CREATE_FUNC(InfoScene);

};


#endif