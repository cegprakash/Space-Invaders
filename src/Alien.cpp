#include "Alien.h"

 //distance per second

Alien::Alien(IMeshSceneNode *alienNode, AlienType type){
	this->alienNode = alienNode;
	bullet = new Bullet(NULL);
}

void Alien::moveLeft(float distance){	
	alienNode->setPosition(alienNode->getPosition()+vector3df(-distance,0,0));
}

void Alien::moveRight(float distance){
	alienNode->setPosition(alienNode->getPosition()+vector3df(distance,0,0));
}

void Alien::moveDown(float distance){
	alienNode->setPosition(alienNode->getPosition()+vector3df(0,-distance,0));
}

void Alien::destroy(){

	bullet->destroy();
	if(alienNode){
		alienNode->remove();
		alienNode = NULL;
	}
}