#ifndef ALIEN_H
#define ALIEN_H

#include "Constants.h"
#include "Bullet.h"

class Alien{
	public:
		IMeshSceneNode *alienNode;
		Bullet *bullet;

		Alien(IMeshSceneNode *alienNode, AlienType type);

		void moveLeft(float speed);
		void moveRight(float speed);
		void moveDown(float speed);
		void destroy();

};



#endif