/***********************************************************************************************

@ Project: Flappy Brid
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
#include "GameData.h"
#include "time.h"
#include "PipeLayer.h"



USING_NS_CC;

class BackGroundLayer :public Layer{

public:

	virtual bool init() override;

	//void onExit() override;

	CREATE_FUNC(BackGroundLayer);

	CC_SYNTHESIZE(PipeLayer*, pipeLayer,PipeLayer);

	void startGame();

	void overGame();

	void setPipeDelegator(BulletinDelegate*);

	int getCurPoint();

private:

	void initPhysicsAttributes();

	void onExit() override;

	int getLocalTime();

	void initBackGround();
	
	void landScrolling(float dt);

	void scrollingStart();
	
	void scrollingEnd();



};



#endif