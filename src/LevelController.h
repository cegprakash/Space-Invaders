#ifndef LEVELCONTROLLER_H
#define LEVELCONTROLLER_H

#include "Shooter.h"
#include "Constants.h"
#include "Alien.h"
#include "MyEventReceiver.h"
#include <cstring>

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
		IGUIFont *font;
		IGUIEnvironment* gui;
		void fireAlienBullets();
		void updateAlienBullets();
		wstring getScoreString();
		wstring getLivesString();

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
		void updateAliens(float diffSeconds);
		void strikeAliens();
		~LevelController();
};

#endif