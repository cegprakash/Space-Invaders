#include "Alien.h"

Alien::Alien(IMeshSceneNode *alienNode, AlienType type){
	this->alienNode = alienNode;
	bullet = new Bullet(NULL);
}

void Alien::moveLeft(float speed){
	alienNode->setPosition(alienNode->getPosition()+speed*vector3df((f32)-0.4,0,0));
}

void Alien::moveRight(float speed){
	alienNode->setPosition(alienNode->getPosition()+speed*vector3df((f32)0.4,0,0));
}

void Alien::moveDown(float speed){
	alienNode->setPosition(alienNode->getPosition()+speed*(f32)10.0*vector3df(0,(f32)(-0.4),0));
}

void Alien::destroy(){

	bullet->destroy();
	if(alienNode){
		alienNode->remove();
		alienNode = NULL;
	}
}