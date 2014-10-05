#ifndef BULLET_H
#define BULLET_H

#include "Headers.h"

class Bullet{

	public:
		IMeshSceneNode *bulletNode;
		Bullet(IMeshSceneNode *node);
		void moveUp();
		void moveDown();
		void destroy();
};

#endif