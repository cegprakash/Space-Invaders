#include "LevelController.h"


 // ...

 // start up the engine

        
 // ...
 
 // after finished,
 // close the engine again, similar as calling 'delete'
 
int main()
{
	LevelController levelController;
	irrklang::ISoundEngine* engine = irrklang::createIrrKlangDevice();
	engine->play2D("audio/IrrlichtTheme.ogg", true); 
	levelController.play(); 
	engine->drop(); 
	return 0;
}