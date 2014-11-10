/***********************************************************************************************

@ Project: Flappy Brid
@ Author:  Lolo
@ Date:    2014-11-4 23:42:32
@ File:    BulletinBoard.h
________________________________________________________________________________________________
@ Description:
show the infomations of the game.
such as score,and gamme over
________________________________________________________________________________________________

************************************************************************************************/


#ifndef __FB_GAME_BULLETIN_H__
#define __FB_GAME_BULLETIN_H__

#include "cocos2d.h"
#include "GameData.h"
#include "BulletinDelegate.h"
#include "GameLayer.h"

USING_NS_CC;

class BulletinBoard :public Layer, public BulletinDelegate{


public:



	CREATE_FUNC(BulletinBoard);

	virtual bool init();

	virtual void showBulletin(int) override;

	virtual void updateScore(int) override;

private:
	
	void    loadRes();

	virtual void showReady() override;

	virtual void showSteady(const std::function<void(void)> &callback) override;

	virtual void showGaming() override;

	virtual void showGameOver() override;

	Point   originPoint;

	Size    visiableSize;

	Sprite* readySprite;

	Sprite* tutorialSprite;

	Label*  scoreLabel;
	
	bool    newRecord;

	int     count;

	void    countDown();

	void    countDownAnimation(float);

	void    removeScoreLabel();

};



#endif