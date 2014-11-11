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


	CREATE_FUNC(BackGroundLayer);

	//background layer's child, pipelayer, which deal about the pipes during  gaming.
	CC_SYNTHESIZE(PipeLayer*, pipeLayer,PipeLayer);

	
	void startGame();

	void overGame();

	int getCurPoint();

	void setPipeDelegator(BulletinDelegate*);


private:

	void initBackGround();

	void initPhysicsAttributes();

	void onExit() override;

	int  getLocalTime();
	
	void landScrolling(float dt);

	void scrollingStart();
	
	void scrollingEnd();



};



#endif