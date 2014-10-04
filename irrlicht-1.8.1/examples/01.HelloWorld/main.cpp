#include <irrlicht.h>
#include<iostream>

#include <irrlicht.h>

#include "driverChoice.h"

#include <string.h>

#include <stdlib.h>

#include <sstream>

using namespace irr;

using namespace video;

using namespace scene;

using namespace core;

using namespace gui;

using namespace std;

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

#ifdef _MSC_VER
#pragma comment(lib, "Irrlicht.lib")
#endif

irr::scene::ICameraSceneNode *fpsCamera;

class MyEventReceiver : public IEventReceiver

{

public:

    bool isMouseDown;

    

virtual bool OnEvent(const SEvent& event)

{

if (event.EventType == irr::EET_KEY_INPUT_EVENT){

KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;

        }

        

        if (event.EventType == irr::EET_MOUSE_INPUT_EVENT){

            switch(event.MouseInput.Event)

            {

                case EMIE_LMOUSE_PRESSED_DOWN:

                    isMouseDown = true;

                    break;

                    

                default:

                    isMouseDown = false;

                    

            }

        }

        

        

return true;

}

    

virtual bool IsKeyDown(EKEY_CODE keyCode) const

{

return KeyIsDown[keyCode];

}

MyEventReceiver()

{

for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)

KeyIsDown[i] = false;

        isMouseDown = false;

    }

    

private:

// We use this array to store the current state of each key

bool KeyIsDown[KEY_KEY_CODES_COUNT];

    

};

int main()

{

    int i;

    int selectedBoneId=-1;

    

    

    MyEventReceiver receiver;

    

IrrlichtDevice* device = createDevice(video::EDT_OPENGL,

                                          core::dimension2d<u32>(640, 480), 16, false, false, false, &receiver);

    

if (!device)

return 1;

    ISceneManager* smgr = device->getSceneManager();

    IVideoDriver* driver = device->getVideoDriver();

    

	IMeshSceneNode* node = smgr->addCubeSceneNode(); 
    

    fpsCamera = smgr->addCameraSceneNodeFPS(0, 30, 0.1);

    vector3df nodePos(-50,0,-50);

    fpsCamera->setPosition(vector3df(-50,0,-50));

    

    scene::ISceneCollisionManager* cmgr = smgr->getSceneCollisionManager();

    

    

    

    scene::ITriangleSelector* selector = 0;

    

    

    

    

    node->setJointMode(EJUOR_CONTROL); // tell irrlicht that you want to control joint positions

    

    int numBones = node->getJointCount();

    

    

    

    for(int i=1;i<=numBones;i++){

        IBoneSceneNode* currentNode = node->getJointNode(i-1);

        currentNode->setID((i<<1)|1);

        IMeshSceneNode *cub = smgr->addCubeSceneNode();

        

        selector = smgr->createTriangleSelector(cub->getMesh(), cub);

        cub->setTriangleSelector(selector);

        selector->drop();

        

        cub->setParent(currentNode);

        cub->setID((i<<1)|1);

        cub->setScale(vector3df(0.05,0.05,0.05));

        

    }

    

    

    while(device->run())

    {

        

        driver->beginScene(true, true, video::SColor(255,200,200,200));

        driver->setTransform(video::ETS_WORLD, core::matrix4());

        smgr->drawAll();

        triangle3df hitTriangle;

        vector3df collisionPoint;

        line3df ray;

        ray.start = fpsCamera->getPosition();

        ray.end = ray.start + (fpsCamera->getTarget() - ray.start).normalize() * 10000.0f;

    

        ISceneNode* hitNode = cmgr->getSceneNodeAndCollisionPointFromRay(ray, collisionPoint ,hitTriangle, 1);

        

        

        if(hitNode){

            

            

            int id = hitNode->getID();

            id >>= 1;

            std:: string s(node->getJointNode(id-1)->getName());

            if(receiver.isMouseDown){

                selectedBoneId = id-1;

            }

            

            stringstream ss(s);

            s = "Hitting "+s;

            wchar_t * name = new wchar_t[s.length()+1];

            for(i=0;i<=s.length();i++)

                name[i]=s[i];

            device->setWindowCaption(name);

        }

        else{

            if(receiver.isMouseDown)

                selectedBoneId = -1;

            device->setWindowCaption(L"No node selected");

        }

        

        if(receiver.IsKeyDown(irr::KEY_UP)){

            fpsCamera->setPosition(fpsCamera->getPosition()+vector3df(0,0.2,0));

            fpsCamera->setRotation((nodePos-fpsCamera->getPosition()).normalize());

        }

        else if(receiver.IsKeyDown(irr::KEY_DOWN)){

            fpsCamera->setPosition(fpsCamera->getPosition()+vector3df(0,-0.2,0));

            fpsCamera->setRotation((nodePos-fpsCamera->getPosition()).normalize());

        }

        else if(receiver.IsKeyDown(irr::KEY_LEFT)){

            fpsCamera->setPosition(fpsCamera->getPosition()+vector3df(-0.2,0,0));

            fpsCamera->setRotation((nodePos-fpsCamera->getPosition()).normalize());

        }

        else if(receiver.IsKeyDown(irr::KEY_RIGHT)){

            fpsCamera->setPosition(fpsCamera->getPosition()+vector3df(0.2,0,0));

            fpsCamera->setRotation((nodePos-fpsCamera->getPosition()).normalize());

        }

        

        if(selectedBoneId!=-1){

            if(receiver.IsKeyDown(irr::KEY_KEY_X)){

                vector3df dir = node->getJointNode(selectedBoneId)->getRotation();

                dir = dir + vector3df(1,0,0);

                node->getJointNode(selectedBoneId)->setRotation(dir);

            }

            else if(receiver.IsKeyDown(irr::KEY_KEY_Y)){

                vector3df dir = node->getJointNode(selectedBoneId)->getRotation();

                dir = dir + vector3df(0,1,0);

                node->getJointNode(selectedBoneId)->setRotation(dir);

            }

            else if(receiver.IsKeyDown(irr::KEY_KEY_Z)){

                vector3df dir = node->getJointNode(selectedBoneId)->getRotation();

                dir = dir + vector3df(0,0,1);

                node->getJointNode(selectedBoneId)->setRotation(dir);

            }

               

        }

        

        

        driver->endScene();

    }

return 0;

}
