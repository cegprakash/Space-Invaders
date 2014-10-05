#ifndef LEVELCONTROLLER_H
#define LEVELCONTROLLER_H

#include "Shooter.h"
#include "Constants.h"
#include "Alien.h"
#include "MyEventReceiver.h"

class LevelController{
	private:
		MyEventReceiver receiver;
		IrrlichtDevice* device;
		IVideoDriver* driver;
		ITexture* bgTexture;
		bool aliensMoveDirection;
		int getLeftMostAlien();
		int getRightMostAlien();
		int getBottomMostAlien();
		irrklang::ISoundEngine* soundEngine;

		void fireAlienBullets();
		void updateAlienBullets();
	public:

		ISceneManager* smgr;

		int currentLevel;
		int score;
		int lives;

		Shooter shooter;
		vector<Alien> aliens;

		LevelController();
		bool isGameOver();
		void generateLevel();
		void play();
		void updateAliens();
		void strikeAliens();
		~LevelController();
};

#endif