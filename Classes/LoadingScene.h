#ifndef __FB_LOAD_H__
#define __FB_LOAD_H__

/***********************************************************************************************

@ Project: Flappy Brid
@ Author:  Lolo
@ Date:    2014-11-3 17:02:33
@ File:    LoadingScene.h
________________________________________________________________________________________________
@ Description:
Game Loading
________________________________________________________________________________________________

************************************************************************************************/

#include "cocos2d.h"
#include "InfoScene.h"
#include "GameData.h"

USING_NS_CC;
using namespace CocosDenshion;


class LoadingScene :public Layer{



	public:

		// there's no 'id' in cpp, so we recommend returning the class instance pointer
		static Scene* createScene();
		// implement the "static create()" method manually
		CREATE_FUNC(LoadingScene);
		// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
		virtual bool init();

		
	private:
		/*@brif
		**Load music resourses;
		*/
		void loadMusic();

		/*@brif
		**call back function;
		*/
		void loadOverCallback(Texture2D *texture);

};





#endif