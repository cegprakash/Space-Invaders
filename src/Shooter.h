#ifndef SHOOTER_H
#define SHOOTER_H

#include "Bullet.h"

class Shooter{

public:

	IMeshSceneNode *shooterNode;
	vector<Bullet> bullets;
	void initShooter(IMeshSceneNode *node);
	void moveLeft();
	void moveRight();
	void fireBullet(IMeshSceneNode *node);
	void updateBullets();
};

#endif