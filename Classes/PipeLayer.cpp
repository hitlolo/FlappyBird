
#include "PipeLayer.h"



bool PipeLayer::init(){
	
	if (!Layer::init()){
		return false;
	}

	curPoint = 0;

	this->createPipe();


	return true;

}


void PipeLayer::createPipe()
{

	Size visibleSize = Director::getInstance()->getVisibleSize();
	std::string pipeName_up;
	std::string pipeName_down;

	int hour = this->getLocalTime();
	if (hour>=7 && hour <=19){
		pipeName_up = PIC_PIPE_DAY_UP;
		pipeName_down = PIC_PIPE_DAY_DOWN;
	}
	else{
		pipeName_up = PIC_PIPE_NIGHT_UP;
		pipeName_down = PIC_PIPE_NIGHT_DOWN;
	}

	for (int i = 0; i < 3; i++){

		//up 
		auto pipeSprite_up   = Sprite::createWithSpriteFrameName(pipeName_up);
		
		auto pipeBody_up     = PhysicsBody::create();
		auto pipeShape_up    = PhysicsShapeBox::create(pipeSprite_up->getContentSize());
		pipeBody_up->addShape(pipeShape_up);
		pipeBody_up->setDynamic(false);
		pipeBody_up->setCategoryBitmask(ColliderTypePip);
		pipeBody_up->setContactTestBitmask(ColliderTypeBird);
		pipeBody_up->setCollisionBitmask(ColliderTypeBird);
		pipeSprite_up->setPhysicsBody(pipeBody_up);
		//down
		auto pipeSprite_down = Sprite::createWithSpriteFrameName(pipeName_down);

		auto pipeBody_down = PhysicsBody::create();
		auto pipeShape_down = PhysicsShapeBox::create(pipeSprite_down->getContentSize());
		pipeBody_down->addShape(pipeShape_down);
		pipeBody_down->setDynamic(false);
		pipeBody_down->setCategoryBitmask(ColliderTypePip);
		pipeBody_down->setContactTestBitmask(ColliderTypeBird);
		pipeBody_down->setCollisionBitmask(ColliderTypeBird);
		pipeSprite_down->setPhysicsBody(pipeBody_down);

		//
		pipeSprite_up->setPosition(Point::ZERO);
		pipeSprite_down->setPosition(0, THROUGH_HEIGHT + pipeSprite_down->getContentSize().height);

		auto pipeNode = Node::create();
		pipeNode->addChild(pipeSprite_up);
		pipeNode->addChild(pipeSprite_down);

		pipeNode->setPosition((visibleSize.width + i*PIPE_RANGE) + READY_DISTANCE, getRandomHeight());

		this->pipeVector.pushBack(pipeNode);
		
		this->addChild(pipeNode,0,0);
	}

}


int  PipeLayer::getRandomHeight(){

	Size visibleSize = Director::getInstance()->getVisibleSize();
	return rand() % (int)(2 * PIPE_HEIGHT + THROUGH_HEIGHT - visibleSize.height);

}

void PipeLayer::pipeMoving(){
	
	Size visibleSize = Director::getInstance()->getVisibleSize();
	for (auto pipeNode : this->pipeVector) {
		pipeNode->setPositionX(pipeNode->getPositionX() - 2);
		

		if (isGetPoint(pipeNode) && pipeNode->getTag()==0){
			
			curPoint++;
			//__NotificationCenter::getInstance()->postNotification(MSG_GET_POINT);
			//CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(M_GETPOINT);
			this->getDelegator()->updateScore(curPoint);
			pipeNode->setTag(1);
		}


		if (pipeNode->getPositionX() < -(pipeNode->getContentSize().width + 26)) {
			
			pipeNode->setTag(0);
			int i = pipeVector.getIndex(pipeNode);
			switch (i){
			case 0:
				pipeNode->setPosition((pipeVector.at(2))->getPositionX() + PIPE_RANGE, this->getRandomHeight());
				break;
			case 1:
				pipeNode->setPosition((pipeVector.at(0))->getPositionX() + PIPE_RANGE, this->getRandomHeight());
				break;
			case 2:
				pipeNode->setPosition((pipeVector.at(1))->getPositionX() + PIPE_RANGE, this->getRandomHeight());
				break;
			}
			
			
		}

		
	}
}


void PipeLayer::startGame(){

	this->scheduleUpdate();
}

void PipeLayer::overGame(){

	this->unscheduleUpdate();
}


bool PipeLayer::isGetPoint(Node* pipe){
	
	return pipe->getPositionX() < CHECK_POINT;
}

void PipeLayer::update(float dt){

	this->pipeMoving();
}



int  PipeLayer::getLocalTime()
{

	struct tm* s_time;
	time_t t = time(&t);
	s_time = localtime(&t);

	return s_time->tm_hour;
}
