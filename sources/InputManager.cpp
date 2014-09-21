#include "InputManager.h"

InputManager* InputManager::m_Instance = 0;

InputManager* InputManager::Instance()
{
    if(InputManager::m_Instance == 0)
    {
        InputManager::m_Instance = new InputManager();
    }
    return InputManager::m_Instance;
}

InputManager::InputManager()
{
    Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");
    OIS::ParamList pl;
    size_t windowHnd = 0;
    std::ostringstream windowHndStr;

    TopManager::Instance()->getGraphicManager()->getRenderWindow()->getCustomAttribute("WINDOW", &windowHnd);
    windowHndStr << windowHnd;
    pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

    m_OIS = OIS::InputManager::createInputSystem(pl);
    Ogre::LogManager::getSingletonPtr()->logMessage("*** Initialied OIS ***");
}

OIS::InputManager* InputManager::getOIS()
{
    return m_OIS;
}
