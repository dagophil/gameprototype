#ifndef InputManager_H_
#define InputManager_H_

#include <OGRE/OgreCamera.h>
#include <OGRE/OgreEntity.h>
#include <OGRE/OgreLogManager.h>
#include <OGRE/OgreRoot.h>
#include <OGRE/OgreViewport.h>
#include <OGRE/OgreSceneManager.h>
#include <OGRE/OgreRenderWindow.h>
#include <OGRE/OgreConfigFile.h>

#include <OIS/OISEvents.h>
#include <OIS/OISInputManager.h>
#include <OIS/OISKeyboard.h>
#include <OIS/OISMouse.h>
#include <OIS/OISJoyStick.h>

#include <OGRE/SdkTrays.h>
#include <OGRE/SdkCameraMan.h>

#include "TopManager.h"
#include "GraphicManager.h"

/**
 *
 * @class InputManager
 * @brief Extended OIS InputManager
 * Singelton class, that initialises OIS at first call.
 *
 */

class InputManager
{
public:
  /**
   * @brief Singelton Instance
   * @return Pointer to InputManager
   */
  static InputManager *Instance();

  /**
   * @brief getter for OISInputManager
   * @return pointer to OISInputManager
   */
  OIS::InputManager*getOIS();
private:
  InputManager();
  static InputManager * m_Instance;
  OIS::InputManager * m_OIS;
};
#endif
