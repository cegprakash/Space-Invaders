#include "Bullet.h"

Bullet::Bullet(IMeshSceneNode *node){
	bulletNode = node;
	if(bulletNode){
		bulletNode->setScale(vector3df(0.5));
	}
}

void Bullet::moveUp(){
	bulletNode->setPosition(bulletNode->getPosition()+vector3df(0,2,0));
}

void Bullet::moveDown(){
	bulletNode->setPosition(bulletNode->getPosition()+vector3df(0,-2,0));
}

void Bullet::destroy(){
	if(bulletNode){
		bulletNode->remove();
		bulletNode = NULL;
	}
}