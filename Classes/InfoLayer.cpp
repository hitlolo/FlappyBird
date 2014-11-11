/***********************************************************************************************

@ Project: Flappy Brid
@ Author:  Lolo
@ Date:    2014-11-3 19:02:33
@ File:    infoLayer.cpp
________________________________________________________________________________________________
@ Description:
Game Infomation Show
________________________________________________________________________________________________

************************************************************************************************/

#include "InfoLayer.h"


bool InfoLayer::init()
{
	if (!Layer::init()){
		return false;
	}

	this->loadInfo();
	
	return true;
}



void InfoLayer::loadInfo()
{
	Size visiableSize = Director::getInstance()->getVisibleSize();
	Point originPoint = Director::getInstance()->getVisibleOrigin();

	//title
	auto gameTitle = Sprite::createWithSpriteFrameName(PIC_BG_TITLE);
	gameTitle->setPosition( originPoint.x + visiableSize.width/2, originPoint.y + (visiableSize.height/10) *8 );
	this->addChild(gameTitle);

	//bird
	auto bird = BirdSprite::create();
	bird->setPosition( Point(originPoint.x + visiableSize.width/2, originPoint.y + visiableSize.height/10 *6));
	this->addChild(bird);


	//button
	auto buttonStart_n = Sprite::createWithSpriteFrameName( PIC_B_PLAY );
	auto buttonStart_p = Sprite::createWithSpriteFrameName( PIC_B_PLAY );
	buttonStart_n->setPositionY(5);

	//MenuItemSprite * MenuItemSprite::create(Node* normalSprite, Node* selectedSprite, Ref* target, SEL_MenuHandler selector)
	//typedef std::function<void(Ref*)> ccMenuCallback;
	//#define CC_CALLBACK_1(__selector__,__target__, ...) std::bind(&__selector__,__target__, std::placeholders::_1, ##__VA_ARGS__)
	

	//menu
	auto menuItem = MenuItemSprite::create(buttonStart_n, buttonStart_p, CC_CALLBACK_1(InfoLayer::gameStartCallback, this));
	menuItem->setPosition( Point( originPoint.x + visiableSize.width/2 , originPoint.y + visiableSize.height/10 * 4) );
	auto menu     = Menu::create(menuItem,nullptr);
	menu->setPosition(Point::ZERO);
	this->addChild(menu);

	//LOGO
	auto copyright = Sprite::createWithSpriteFrameName(PIC_BG_COPYRIGHT);
	copyright->setPosition( originPoint.x + visiableSize.width / 2, originPoint.y + visiableSize.height / 10 * 1 );
	this->addChild(copyright);

}


void InfoLayer::gameStartCallback(Ref* sender)
{
	this->playGame();
}

/* @brif
** 
*  Go to the next scene. 
*  GameScene is the main scene of the game!
*/
void InfoLayer::playGame()
{

	CCLOG("hi,there!");
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(M_SWOOSH);
	auto nextScene = GameScene::createScene();
	TransitionScene *transition = TransitionFade::create(0.2f, nextScene);
	Director::getInstance()->replaceScene(transition);
}
