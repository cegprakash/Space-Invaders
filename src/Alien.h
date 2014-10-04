#ifndef ALIEN_H
#define ALIEN_H

#include "Constants.h"
#include "Bullet.h"

class Alien{
	public:
		IMeshSceneNode *alienNode;
		vector<Bullet> bullets;

		Alien(IMeshSceneNode *node, AlienType type);

		void moveLeft(float speed);
		void moveRight(float speed);
		void moveDown();
		void destroy();

};



#endif