#ifndef ALIEN_H
#define ALIEN_H

#include "Constants.h"
#include "Bullet.h"

class Alien{
	public:
		IMeshSceneNode *alienNode;
		Bullet *bullet;

		Alien(IMeshSceneNode *alienNode, AlienType type);

		void moveLeft(float distance);
		void moveRight(float distance);
		void moveDown(float distance);
		void destroy();

};



#endif