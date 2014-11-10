
#ifndef __FB_GAME_PIPE_H__
#define __FB_GAME_PIPE_H__


#include "cocos2d.h"
#include "GameData.h"
#include "Time.h"
#include "SimpleAudioEngine.h"
#include "BulletinDelegate.h"

USING_NS_CC;

class PipeLayer :public Layer{

public:

	CREATE_FUNC(PipeLayer);

	virtual bool init() override;

	void startGame();

	void overGame();

	CC_SYNTHESIZE(int,curPoint,CurPoint);

	CC_SYNTHESIZE(BulletinDelegate*,pointDelegate,Delegator);

private:
	
	Vector<Node*> pipeVector;

	void createPipe();

	void pipeMoving();

	void update(float) override;

	bool isGetPoint(Node*);

	int  getRandomHeight();



};

#endif