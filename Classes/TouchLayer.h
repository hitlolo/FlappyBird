


#ifndef __FB_GAME_TOUCH_H__
#define __FB_GAME_TOUCH_H__


#include "cocos2d.h"
#include "TouchDelegate.h"

USING_NS_CC;

class TouchLayer :public Layer{

public:

	virtual void onTouchesBegan(const std::vector<Touch*>& touches, Event *event) override;

	virtual bool init();

	CREATE_FUNC(TouchLayer);

	CC_SYNTHESIZE(TouchDelegate*,touchDeleageted,Delegator);
};


#endif