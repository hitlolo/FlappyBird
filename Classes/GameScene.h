/***********************************************************************************************

@ Project: Flappy Brid
@ Author:  Lolo
@ Date:    2014-11-4 23:42:32
@ File:    GameScene.h
________________________________________________________________________________________________
@ Description:
 Main Game Scene
________________________________________________________________________________________________

************************************************************************************************/

#ifndef __FB_GAME_SCENE_H__
#define __FB_GAME_SCENE_H__


#include "cocos2d.h"
#include "GameData.h"

#include "GameLayer.h"
#include "TouchLayer.h" 

USING_NS_CC;

class GameScene :public Layer{

public:

	static Scene* createScene();

	virtual bool init(); 

	CREATE_FUNC(GameScene);
};




#endif
