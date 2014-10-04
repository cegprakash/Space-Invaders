#ifdef _MSC_VER
// We'll define this to stop MSVC complaining about sprintf().
#define _CRT_SECURE_NO_WARNINGS
#pragma comment(lib, "Irrlicht.lib")
#endif

#include <irrlicht.h>

using namespace irr;
using namespace scene;
using namespace video;
using namespace core;
using namespace gui;
using namespace io;

class MyEventReceiver : public IEventReceiver
{
public:
    // This is the one method that we have to implement
    virtual bool OnEvent(const SEvent& event)
    {
        // Remember whether each key is down or up
        if (event.EventType == irr::EET_KEY_INPUT_EVENT)
            KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;

        return false;
    }

    // This is used to check whether a key is being held down
    virtual bool IsKeyDown(EKEY_CODE keyCode) const
    {
        return KeyIsDown[keyCode];
    }
    
    MyEventReceiver()
    {
        for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
            KeyIsDown[i] = false;
    }

private:
    // We use this array to store the current state of each key
    bool KeyIsDown[KEY_KEY_CODES_COUNT];
};


int main()
{
	MyEventReceiver receiver;

    IrrlichtDevice* device = createDevice(video::EDT_OPENGL,
            core::dimension2d<u32>(640, 480), 16, false, false, false, &receiver);
	IVideoDriver* driver = device->getVideoDriver();
    ISceneManager* smgr = device->getSceneManager();
	smgr->addLightSceneNode(0,vector3df(50,50,50));
	ICameraSceneNode *camera = smgr->addCameraSceneNode();

	IMeshSceneNode *node = smgr->addCubeSceneNode();
	
	node->setPosition(vector3df(0,75,0));

	camera->setTarget(vector3df(0,1,0));

	
	smgr->getMeshManipulator()->setVertexColors(node->getMesh(), SColor(0,0,255,255));
	smgr->addLightSceneNode();

	while(device->run()){

		if(receiver.IsKeyDown(irr::KEY_LEFT)){
			node->setPosition(node->getPosition()+vector3df(0,0,-0.1));
		}
		else if(receiver.IsKeyDown(irr::KEY_RIGHT)){
			node->setPosition(node->getPosition()+vector3df(0,0,0.1));
		}
		else if(receiver.IsKeyDown(irr::KEY_SPACE)){
			
		}
		driver->beginScene(true, true, SColor(123,100,100,100));
        smgr->drawAll();
		driver->endScene();
	}



	return 0;
}
