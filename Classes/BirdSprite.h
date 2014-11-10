/***********************************************************************************************

@ Project: Flappy Brid
@ Author:  Lolo
@ Date:    2014-11-3 21:32:32
@ File:    BirdSprite.h
________________________________________________________________________________________________
@ Description:
Bird
________________________________________________________________________________________________

************************************************************************************************/

#ifndef __FB_BIRD_H__
#define __FB_BIRD_H__

#include "cocos2d.h"
#include "GameData.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

typedef enum class state_enum{
	STATE_IDEL = 0,
	STATE_FLY,
	STATE_DIE
}BIRD_STATE;

typedef enum{
	YELLOW = 0,
	GREEN,
	RED,
}BIRD_COLOR;

class BirdSprite :public Sprite{

private:
	
	void createBird();

	int  selectRandomColor();

	Action* actionIdle;

	Action* actionSwing;

	void initAnimation(std::string name, int img_count, float ft);

public:

	BirdSprite();

	virtual ~BirdSprite();

	void idle();

	void fly();

	void die();

	void gravityDown();

	void gravityUp();

	void birdRun(BIRD_STATE);

	virtual bool init() override;

	CREATE_FUNC(BirdSprite);

	CC_SYNTHESIZE(BIRD_STATE, curState, State);

	void initPhysicsAttributes();

	void update(float dt) override;

};




#endif