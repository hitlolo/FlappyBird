#ifndef __FB_INFO_LAYER_H__
#define __FB_INFO_LAYER_H__

/***********************************************************************************************

@ Project: flappy brid
@ Author:  Lolo
@ Date:    2014-11-3 19:02:33
@ File:    infoLayer.h
________________________________________________________________________________________________
@ Description:
Game Infomation Show
________________________________________________________________________________________________

************************************************************************************************/
#include "cocos2d.h"

USING_NS_CC;

class InfoLayer :public Layer{

public:

	virtual bool init();

	CREATE_FUNC(InfoLayer);
};

#endif