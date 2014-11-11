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

	void initAnimation(std::string name, int img_count, float ft);

	Action* actionIdle;

	Action* actionSwing;

	
public:

	BirdSprite();

	virtual ~BirdSprite();

	virtual bool init() override;

	void initPhysicsAttributes();

	void update(float dt) override;

	CREATE_FUNC(BirdSprite);

	CC_SYNTHESIZE(BIRD_STATE, curState, State);

	void idle();

	void fly();

	void die();

	void gravityDown();

	void gravityUp();

	//call the idle() fly() die() depends on the state
	void birdRun(BIRD_STATE);

};




#endif