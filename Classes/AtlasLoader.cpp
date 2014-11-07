

/*@@@@@  WARNING @@@@@@@
	this class deprecated!
  @@@@@  WARNING @@@@@@@
*/

/***********************************************************************************************

@ Project: Flappy Brid
@ Author:  Lolo
@ Date:    2014-11-2 17:01:33
@ File:    AtlasLoader.cpp
________________________________________________________________________________________________
@ Description:
AtlasLoader is a class to Load the atlas sprite sheet.
________________________________________________________________________________________________

************************************************************************************************/

#include "AtlasLoader.h"


AtlasLoader* AtlasLoader::sharedAtlasLoader = nullptr;


/** @ Description @ **
*  A static class function to	Get the instance of AtlasLoader
*  parameters: void
*  return:     the singleton instance
**/
AtlasLoader* AtlasLoader::getInstance()
{
	if (sharedAtlasLoader == nullptr){
		sharedAtlasLoader = new AtlasLoader();
		if (!sharedAtlasLoader){
			delete sharedAtlasLoader;
			sharedAtlasLoader = nullptr;
			CCLOG("ERROR: Could not init sharedAtlasLoader");
		}
	}
	else
		return sharedAtlasLoader;
	
}

/** @ Description @ **
*  A static class function to Delete the instance of AtlasLoader Safely!
*  parameters: void
*  return:     void
**/
void AtlasLoader::deleteInstance()
{

	CC_SAFE_DELETE(sharedAtlasLoader);

}


/** @ Description @ **
*  init function
*  parameters: filename
*  return:     succesful or not
**/
bool AtlasLoader::initWithTexture(std::string filename)
{
	return false;
}

/** @ Description @ **
*  Get the sprite by name.
*  parameters: sprite name
*  return:     sprite frame instance
**/
SpriteFrame* AtlasLoader::getSpriteByName(std::string spriteName)
{
	return this->spriteFrames.at(spriteName);
}

/** @ Description @ **
*  Load the atlas of file
*  parameters: filename, texture
*  return:     succesful or not
**/
bool AtlasLoader::loadAtlas(std::string filename, Texture2D* texture)
{

	Atlas s_atlas;
	std::string data;
	char  bufName[100];
	std::string format = "%s %d %d %f %f %f %f";
	data = FileUtils::getInstance()->getStringFromFile(filename);
	
	if (!data.empty())
	{
		std::string::size_type located = 0;
		std::string line;

		located = data.find_first_of('\n');
		line    = data.substr(0,located);
		data	= data.substr(located + 1);

		while (!line.empty())
		{
			sscanf(line.c_str(), format.c_str(), bufName, &s_atlas.width, &s_atlas.height, &s_atlas.start.x, &s_atlas.start.y, &s_atlas.end.x, &s_atlas.end.y);
			s_atlas.name = bufName;

			if (!s_atlas.name.empty())
			{
				s_atlas.start.x *= 1024;
				s_atlas.start.y *= 1024;
				s_atlas.end.x *= 1024;
				s_atlas.end.y *= 1024;
			}
			CCLOG("%s ", line.c_str());
			located = data.find_first_of("\n");
			line = data.substr(0, located);
			data = data.substr(located + 1);

		    if(s_atlas.name == std::string("land")) {
				CCLOG("i am coming");
		    	s_atlas.start.x += 1;
		    }

			Rect rect  = Rect(s_atlas.start.x,s_atlas.start.y,s_atlas.width,s_atlas.height);
			auto frame = SpriteFrame::createWithTexture(texture,rect);
			this->spriteFrames.insert(s_atlas.name, frame);


		}
	}
	
	return false;
}

//----------------------------------------------------------------------------------------------------------------------------------
/** @ Description @ **
*  decode the txt file that record the sprite infomation.
*  parameters: .txt filename
*  return:     succesful or not
**/
bool AtlasLoader::decodeTxt(std::string txtLine)
{
	Atlas s_atlas;
	char  bufName[100];
	std::string format = "%s %d %d %f %f %f %f";
	sscanf(txtLine.c_str(), format.c_str(), bufName, &s_atlas.width, &s_atlas.height, &s_atlas.start.x, &s_atlas.start.y, &s_atlas.end.x, &s_atlas.end.y);
	s_atlas.name = bufName;
	if (!s_atlas.name.empty()){
		s_atlas.start.x *= 1024;
		s_atlas.start.y *= 1024;
		s_atlas.end.x   *= 1024;
		s_atlas.end.y   *= 1024;

		return true;
	}
	return false;
}



//----------------------------------------------------------------------------------------------------------------------------------
AtlasLoader::AtlasLoader()
{
	CCLOG("allocing AtlasLoader");
}

AtlasLoader::~AtlasLoader()
{
	CCLOG("deallocing AtlasLoader");
}
//----------------------------------------------------------------------------------------------------------------------------------
