
#ifndef __FB_GAME_PIPE_H__
#define __FB_GAME_PIPE_H__


#include "cocos2d.h"
#include "GameData.h"
#include "Time.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

class PipeLayer :public Layer{

public:

	CREATE_FUNC(PipeLayer);

	virtual bool init() override;

	void startGaming();

	void getPoint();

	void pipeStop();

	CC_SYNTHESIZE(int,curPoint,CurPoint);

private:
	
	Vector<Node*> pipeVector;

	void createPipe();

	void pipeMoving();

	void update(float) override;

	bool isGetPoint(Node*);


	int  getRandomHeight();



};

#endif