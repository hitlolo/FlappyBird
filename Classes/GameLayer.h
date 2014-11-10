/***********************************************************************************************

@ Project: Flappy Brid
@ Author:  Lolo
@ Date:    2014-11-4 23:42:32
@ File:    GameLayer.h
________________________________________________________________________________________________
@ Description:
Main Game Layer
________________________________________________________________________________________________

************************************************************************************************/


#ifndef __FB_GAME_LAYER_H__
#define __FB_GAME_LAYER_H__


#include "cocos2d.h"
#include "GameData.h"
#include "BirdSprite.h"
#include "TouchDelegate.h"
#include "BulletinDelegate.h"
#include "SimpleAudioEngine.h"



USING_NS_CC;


typedef enum  state{
	READY = 0,
	STEADY,
	GAMING,
	OVER
}GAME_STATE;


class GameLayer :public Layer, public TouchDelegate{


public:

	virtual bool init();

	virtual void onTouch() override;

	void loadRes();

	CREATE_FUNC(GameLayer);

	CC_SYNTHESIZE(GAME_STATE,curState,GameState);

	CC_SYNTHESIZE(BulletinDelegate*,bulletinDelegated,bulletinDelegator);

private:

	void initPhysicsAttributes();

	BirdSprite* birdSprite;

	
	//void TextureCache::addImageAsync(const std::string &path, const std::function<void(Texture2D*)>& callback)
	void readyGame(const std::function<void(void)> &callback);

	void steadyGame();

	void startGame(Ref* sender);

	void onGaming();

	void overGame();

	int  curScore;

	void getPoint(Ref* sender);

	bool onContact(PhysicsContact& contact);

};


#endif
