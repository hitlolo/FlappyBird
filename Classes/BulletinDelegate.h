
//virtual calss

#pragma once
class BulletinDelegate{

	virtual void showReady() = 0;

	virtual void showSteady(const std::function<void(void)> &callback) = 0;

	virtual void showGaming() = 0;

	virtual void showGameOver() = 0;

public:



	virtual void showBulletin(int) = 0;

	virtual void updateScore(int) = 0;


};