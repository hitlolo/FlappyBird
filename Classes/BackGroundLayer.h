/***********************************************************************************************

@ Project: flappy brid
@ Author:  Lolo
@ Date:    2014-11-3 19:02:33
@ File:    BackGroundLayer.h
________________________________________________________________________________________________
@ Description:
the whole game's backgroud Layer
________________________________________________________________________________________________

************************************************************************************************/


#ifndef __FB_BACK_LAYER_H__
#define __FB_BACK_LAYER_H__

#include "cocos2d.h"

USING_NS_CC;

class BackGroundLayer :public Layer{

public:

	virtual bool init();

	CREATE_FUNC(BackGroundLayer);
};



#endif