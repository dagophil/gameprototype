/*
 * main.cpp
 *
 */

#include "TopManager.h"
#include "GraphicManager.h"

// Basic stuff to run the application class

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

int main(int argc, char* argv[])
{
    TopManager::Instance();
    try
    {
        TopManager::Instance()->getGraphicManager()->go();
    }
    catch(Ogre::Exception& e)
    {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
        MessageBox(NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
        std::cerr << "An exception has occured: " <<
                     e.getFullDescription().c_str() << std::endl;
#endif
    }
    return 0;
}
