#include "LevelController.h"

LevelController::LevelController(){

	device = createDevice(video::EDT_OPENGL, core::dimension2d<u32>(1000, 752), 16, false, false, false, &receiver);
	driver = device->getVideoDriver();
	smgr = device->getSceneManager();
	soundEngine = irrklang::createIrrKlangDevice();
	soundEngine->play2D("audio/IrrlichtTheme.ogg", true);

	bgTexture = driver->getTexture("images/spaceInvadersBG.jpg");
    
	currentLevel = 1;
	score = 0;
	lives = 3;
	shooter.initShooter(smgr->addMeshSceneNode(smgr->getMesh("mesh/SpaceShip.dae")));

	smgr->addLightSceneNode(0,vector3df(0,200,-400));
	ICameraSceneNode *camera = smgr->addCameraSceneNode();
	camera->setPosition(vector3df(0,200,-400));
	camera->setTarget(vector3df(0,200,1));			//camera at -z faces z.
	
	gui = device->getGUIEnvironment();
	font = gui->getFont("font/fonthaettenschweiler.bmp");
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
		fireAlienBullets();
		updateAlienBullets();

		driver->beginScene(true, true, SColor(123,100,100,100));
		driver->draw2DImage(bgTexture, core::position2d<s32>(0,0),
                core::rect<s32>(0,0,1000,752), 0,
                video::SColor(255,255,255,255), true);
		
		dimension2d<u32> size = font->getDimension(getScoreString().c_str());
		font->draw(getScoreString().c_str(),rect<s32>(5,5, 5+size.Width, 5+size.Height), SColor(255,255,255,255));
		 size = font->getDimension(getLivesString().c_str());
		font->draw(getLivesString().c_str(),rect<s32>(850,5, 850+size.Width, 5+size.Height), SColor(255,255,255,255));
		smgr->drawAll();
		gui->drawAll();
		driver->endScene();
	}
}

wstring LevelController::getScoreString(){
	stringstream ss; ss<<score;
	std::string scoreValueString;
	ss>>scoreValueString;
	std::string resultStr = "Score : "+scoreValueString;
	wstring scoreString(resultStr.begin(),resultStr.end());
	return scoreString;
}

wstring LevelController::getLivesString(){
	stringstream ss; ss<<lives;
	std::string livesValueString;
	ss>>livesValueString;
	std::string resultStr = "Lives : "+livesValueString;
	wstring livesString(resultStr.begin(),resultStr.end());
	return livesString;
}
void LevelController::generateLevel(){
	int i, j;

	for(i = 0; i < 5; i++)
		for(j = 0; j < 8; j++){
			IMeshSceneNode* alienNode =  smgr->addMeshSceneNode(smgr->getMesh("mesh/SpaceShip.dae"));	
			alienNode->setScale(vector3df(5));
			alienNode->setRotation(vector3df(270,0,0));
			Alien alien(alienNode, ALIEN_EASY);
			vector3df alienSize = alienNode->getMesh()->getBoundingBox().getExtent();
			vector3df position(-200+j*5*alienSize.X+j*40, 250+i*40+5*i*alienSize.Y, 0);
			alienNode->setPosition(position);
			aliens.push_back(alien);
		}
}

void LevelController::fireAlienBullets(){
	for(int i=0; i<(int)aliens.size(); i++){
		if(rand()%(aliens.size()*100/(currentLevel))==0){
			if(aliens[i].bullet->bulletNode == NULL){
				aliens[i].bullet = new Bullet(smgr->addCubeSceneNode(10.0,0,-1,aliens[i].alienNode->getPosition()));
			}
		}	
	}
}

void LevelController::updateAlienBullets(){
	for(int i=0; i<(int)aliens.size();i++){
		if(aliens[i].bullet->bulletNode != NULL){
			if(aliens[i].bullet->bulletNode->getTransformedBoundingBox().intersectsWithBox(shooter.shooterNode->getTransformedBoundingBox())){
				lives--;
				soundEngine->play2D("audio/LifeGone.mp3");
				aliens[i].bullet->destroy();
			}
			else if(aliens[i].bullet->bulletNode->getPosition().Y < 0)
			{
				aliens[i].bullet->destroy();
			}
			else{
				aliens[i].bullet->moveDown();
			}
		}
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
				score += 10;
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
			aliens[i].moveDown(currentLevel);
			aliens[i].moveRight((float)currentLevel);
		}
		aliensMoveDirection = !aliensMoveDirection;
	
	}
	else if(rightPosition > 360.0){
		for(int i=0; i<(int)aliens.size(); i++){
			aliens[i].moveDown(currentLevel);
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