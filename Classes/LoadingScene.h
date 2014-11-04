#ifndef __FB_LOAD_H__
#define __FB_LOAD_H__

/***********************************************************************************************

@ Project: flappy brid
@ Author:  Lolo
@ Date:    2014-11-3 17:02:33
@ File:    LoadingScene.h
________________________________________________________________________________________________
@ Description:
Game Loading
________________________________________________________________________________________________

************************************************************************************************/

#include "cocos2d.h"
#include "AtlasLoader.h"
#include "SimpleAudioEngine.h"
#include "Data.h"

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
		
		/**@brif
		* When this scene appear ,will call this method,
		* not this scene is create, so if you have some thing
		* want do when scen appear not init, please add to here
		*/
		void onEnter() override;

		
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