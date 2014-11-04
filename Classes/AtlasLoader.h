
#ifndef __FB_ATLAS_H__
#define __FB_ATLAS_H__





/***********************************************************************************************

@ Project: flappy brid
@ Author:  Lolo
@ Date:    2014-11-2 16:19:43
@ File:    AtlasLoader.h
________________________________________________________________________________________________
@ Description:
		   AtlasLoader is a class to Load the atlas sprite sheet.
________________________________________________________________________________________________

************************************************************************************************/



#include"cocos2d.h"

USING_NS_CC;

/*
 * A struct declaration to save the data of sprite Altas
 * name: png name
 * width: png width
 * height: png height
 * start: a point struct of png start point.x point.y
 * end: ....
*/

//bird0_1 48 48 0.0546875 0.9472656 0.046875 0.046875

typedef struct{
	std::string name;
	int         width;
	int			height;
	Point       start;
	Point       end;

}Atlas;

class AtlasLoader{

	private:
		
		/**
		*  A singleton AtalsLoader instance;
		**/
		static AtlasLoader* sharedAtlasLoader;

		/**
		*  A map container to contain sprite frame by name.
		**/
		Map<std::string, SpriteFrame*> spriteFrames;

	public:
	
		//___________________________________________________________________________________________
		/** @ Description @ **
		*  deconstructor
		*  parameters: void
		*  return:     void
		**/
		~AtlasLoader();
		
		AtlasLoader();

		//___________________________________________________________________________________________


		/** @ Description @ **
		  *  A static class function to	Get the instance of AtlasLoader
		  *  parameters: void
		  *  return:     the singleton instance
		 **/
		static AtlasLoader* getInstance();

		/** @ Description @ **
		*  A static class function to Delete the instance of AtlasLoader Safely!
		*  parameters: void
		*  return:     void
		**/
		static void deleteInstance();

		/** @ Description @ **
		*  init function
		*  parameters: filename
		*  return:     succesful or not
		**/
		bool initWithTexture(std::string filename);

		/** @ Description @ **
		*  Get the sprite by name.
		*  parameters: sprite name
		*  return:     sprite frame instance
		**/
		SpriteFrame* getSpriteByName(std::string spriteName);

		/** @ Description @ **
		*  Load the atlas of file
		*  parameters: filename, texture
		*  return:     succesful or not
		**/
		bool loadAtlas(std::string filename, Texture2D* texture);
	
	private:

		//----------------------------------------------------------------------------------------------------------------------------------

		/** @ Description @ **
		*  decode the txt file that record the sprite infomation.
		*  parameters: .txt filename
		*  return:     succesful or not
		**/
		bool decodeTxt(std::string txtFile);

		//----------------------------------------------------------------------------------------------------------------------------------
};



#endif //__FB_ATLAS_H__

