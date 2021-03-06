/*
 * GraphicManager.h
 *
 */

#ifndef GRAPHICMANAGER_H_
#define GRAPHICMANAGER_H_

#include "BaseApplication.h"
#include "InputManager.h"
#include <OGRE/OgreCommon.h>

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


/**
 *
 * @class GraphicManager
 * @brief Graphic manager
 *
 */
class GraphicManager : public BaseApplication
{

public:

    GraphicManager();

    ~GraphicManager();

    /**
     * @brief getter for SceneManager
     * @return Ogre::SceneManager
     */
    Ogre::SceneManager* getSceneManager();

    /**
     * @brief creator for scene
     */
    virtual void createScene();

    /**
     * @brief frame renderer
     * @param evt Event
     * @return bool if frame is rendered
     */
    virtual bool frameRenderingQueued(const Ogre::FrameEvent & evt);

    /**
     * @brief creator for viewports
     */
    virtual void createViewports();

    /**
     * @brief getter for Ogre::RenderWindow
     * @return pointer to Ogre::RenderWindow
     */
    Ogre::RenderWindow* getRenderWindow();

    /**
     * @brief setter for shutdown
     * @param shutdown bool for shutdown
     * using this with a true value will shutdown the game in the next frame
     */
    void setShutdown(bool shutdown);

    /**
     * @brief create camera, not rendered, only for overlays
     */
    virtual void createCamera();

    /**
     * @brief chooses the scene manager
     */
    virtual void chooseSceneManager();

    /**
     * @brief getter for Ogre::Viewport
     * @return Ogre::Viewport*
     */
    Ogre::Viewport* getViewport();

    /**
     * @brief toggle day and night modus (lights)
     */
    void toggleDayNight();

    /**
     * @brief set all lights to day mode
     */
    void makeDayLights();

    /**
     * @brief set all lights to night mode
     */
    void makeNightLights();

private:

    Ogre::Viewport* m_vp;
    std::vector<Ogre::Vector3> m_waypoints;
    void createLightNShadow();
    bool m_daylight;

};

#endif /* GRAPHICMANAGER_H_ */
