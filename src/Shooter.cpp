#include "Shooter.h"

void Shooter::initShooter(IMeshSceneNode *node){
	shooterNode = node;
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