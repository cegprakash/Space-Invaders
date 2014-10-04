#include "Alien.h"

Alien::Alien(IMeshSceneNode *node, AlienType type){
	alienNode = node;
}

void Alien::moveLeft(float speed){
	alienNode->setPosition(alienNode->getPosition()+speed*vector3df(-0.4,0,0));
}

void Alien::moveRight(float speed){
	alienNode->setPosition(alienNode->getPosition()+speed*vector3df(0.4,0,0));
}

void Alien::moveDown(){
	alienNode->setPosition(alienNode->getPosition()+vector3df(0,-5.0,0));
}

void Alien::destroy(){
	alienNode->remove();
	alienNode = NULL;
}