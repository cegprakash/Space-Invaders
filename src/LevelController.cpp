#include "LevelController.h"

LevelController::LevelController(){

	device = createDevice(video::EDT_OPENGL, core::dimension2d<u32>(1000, 752), 16, false, false, false, &receiver);
	driver = device->getVideoDriver();
	smgr = device->getSceneManager();
	soundEngine = irrklang::createIrrKlangDevice();
	soundEngine->play2D("audio/IrrlichtTheme.ogg", true);

	bgTexture = driver->getTexture("images/spaceInvadersBG.jpg");
    //driver->makeColorKeyTexture(images, core::position2d<s32>(1000,752));

	currentLevel = 1;
	score = 0;
	lives = 3;
	shooter.initShooter((IMeshSceneNode*)smgr->addCubeSceneNode());
	//shooter.shooterNode->setMaterialTexture(0,driver->getTexture("Roket.png"));

	smgr->addLightSceneNode(0,vector3df(0,200,-400));
	ICameraSceneNode *camera = smgr->addCameraSceneNode();
	camera->setPosition(vector3df(0,200,-400));
	camera->setTarget(vector3df(0,200,1));			//camera at -z faces z.
}

bool LevelController::isGameOver(){
	if(lives == 0)	return true;
	if(aliens.size()!=0 && aliens[getBottomMostAlien()].alienNode->getPosition().Y < 7.0)	//Alien invasion successful
		return true;
	return false;
}

void LevelController::play(){

	bool shootPressed = false;

	while(!isGameOver() && device->run()){

		if(aliens.size() == 0){
			currentLevel++;
			generateLevel();
		}

		if(receiver.IsKeyDown(irr::KEY_LEFT)){
			shooter.moveLeft();
		}
		if(receiver.IsKeyDown(irr::KEY_RIGHT)){
			shooter.moveRight();
		}
		if(receiver.IsKeyDown(irr::KEY_SPACE)){
			if(!shootPressed){
				shooter.fireBullet(smgr->addCubeSceneNode());
				soundEngine->play2D("audio/ShooterFire.mp3");
			}
			shootPressed = true;
		}
		else shootPressed = false;

		shooter.updateBullets();
		strikeAliens();
		updateAliens();

		driver->beginScene(true, true, SColor(123,100,100,100));
		driver->draw2DImage(bgTexture, core::position2d<s32>(0,0),
                core::rect<s32>(0,0,1000,752), 0,
                video::SColor(255,255,255,255), true);

        smgr->drawAll();
		driver->endScene();
	}
}

void LevelController::generateLevel(){
	int i, j;

	for(i = 0; i < 5; i++)
		for(j = 0; j < 10; j++){
			IMeshSceneNode* alienNode = smgr->addCubeSceneNode();
			alienNode->setScale(vector3df(2));
			Alien alien(alienNode, ALIEN_EASY);
			vector3df alienSize = alienNode->getMesh()->getBoundingBox().getExtent();
			vector3df position(-200+j*30+j*alienSize.X, 250+i*25+i*alienSize.Y, 0);
			alienNode->setPosition(position);
			aliens.push_back(alien);
		}
}

void LevelController::strikeAliens(){
	int i, j;
	for(i = 0; i < (int)shooter.bullets.size(); ){
		bool targetFound = false;
		for(j = 0; j < (int)aliens.size(); ){
			if(aliens[j].alienNode->getTransformedBoundingBox().intersectsWithBox(shooter.bullets[i].bulletNode->getTransformedBoundingBox()))
			{
				soundEngine->play2D("audio/Blast.mp3");
				targetFound = true;
				shooter.bullets[i].destroy();
				shooter.bullets.erase(shooter.bullets.begin()+i);
				aliens[j].destroy();
				aliens.erase(aliens.begin()+j);
				break;
			}
			else j++;
		}
		if(!targetFound) i++;
	}
}

void LevelController::updateAliens(){
	if(aliens.size()==0)
		return;
	float leftPosition = aliens[getLeftMostAlien()].alienNode->getPosition().X;
	float rightPosition = aliens[getRightMostAlien()].alienNode->getPosition().X;
	if(leftPosition < -360.0){
		for(int i=0; i<(int)aliens.size(); i++){
			aliens[i].moveDown();
			aliens[i].moveRight((float)currentLevel);
		}
		aliensMoveDirection = !aliensMoveDirection;
	
	}
	else if(rightPosition > 360.0){
		for(int i=0; i<(int)aliens.size(); i++){
			aliens[i].moveDown();
			aliens[i].moveLeft((float)currentLevel);
		}
		aliensMoveDirection = !aliensMoveDirection;
	}
	else{
		if(aliensMoveDirection)
			for(int i=0; i<(int)aliens.size(); i++)
				aliens[i].moveRight((float)currentLevel);
		else
			for(int i=0; i<(int)aliens.size();i++)
				aliens[i].moveLeft((float)currentLevel);
	}
}

int LevelController::getLeftMostAlien(){
	int i;
	int index = -1;
	float position = 999.0;
	for(i=0; i < (int)aliens.size(); i++){
		if(position > aliens[i].alienNode->getPosition().X){
			position = aliens[i].alienNode->getPosition().X;
			index = i;
		}
	}
	return index;
}

int LevelController::getRightMostAlien(){
	int i;
	int index = -1;
	float position = -999.0;
	for(i=0; i < (int)aliens.size(); i++){
		if(position < aliens[i].alienNode->getPosition().X){
			position = aliens[i].alienNode->getPosition().X;
			index = i;
		}
	}
	return index;
}

int LevelController::getBottomMostAlien(){
	int i;
	int index = -1;
	float position = 999.0;
	for(i=0; i < (int)aliens.size(); i++){
		if(position > aliens[i].alienNode->getPosition().Y){
			position = aliens[i].alienNode->getPosition().Y;
			index = i;
		}
	}
	return index;
}

LevelController::~LevelController(){
	soundEngine->drop();
}