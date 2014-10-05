#include "Shooter.h"

void Shooter::initShooter(IMeshSceneNode *node){
	shooterNode = node;
	node->setRotation(vector3df(90,0,0));
	node->setScale(vector3df(3));
	bullets.clear();
}

void Shooter::moveLeft(){
	if(shooterNode->getPosition().X < -375.0)
		return;
	shooterNode->setPosition(shooterNode->getPosition()+vector3df(-1,0,0));
};

void Shooter::moveRight(){
	if(shooterNode->getPosition().X > 375.0)
		return;
	shooterNode->setPosition(shooterNode->getPosition()+vector3df(1,0,0));
}

void Shooter::fireBullet(IMeshSceneNode *node){
	node->setPosition(shooterNode->getPosition());
	bullets.push_back(node);
}

void Shooter::updateBullets(){
	for(int i=0; i < (int)bullets.size();){
		if(bullets[i].bulletNode->getPosition().Y > 500.0){
			bullets[i].destroy();
			bullets.erase(bullets.begin()+i);
		}
		else{
			bullets[i].moveUp();
			i++;
		}
	}
}