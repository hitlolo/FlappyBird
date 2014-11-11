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
#include "GameScene.h"

USING_NS_CC;

class BulletinBoard :public Layer, public BulletinDelegate{


public:



	CREATE_FUNC(BulletinBoard);

	virtual bool init();

	//deal with gamelayer's all states' infomation showing
	virtual void showBulletin(int) override;
	//deal with pipelayer's score-add showing
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
	
	//bool    newRecord;

	//the ready state's counting down animation.
	int     count;

	void    countDown();

	void    countDownAnimation(float);

	//score
	int     curScore;

	void    removeScoreLabel();

	//game over
	void    blinkScreen();

	void    fadeinPanel();

	void    restartGame(Ref* sender);

	void    scoreBoard(Ref* sender);

	//score panel 's score-adding animation
	void    addScoreAnimation(float dt);

	//medal's blink animation
	Sprite* fireworkSprite;

	void    getFirework();
	
	void    showFirework();
};



#endif