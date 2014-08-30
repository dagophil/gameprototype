/*
 * GraphicManager.cpp
 *
 */
#include "TopManager.h"
#include "GraphicManager.h"
#include "BaseApplication.h"
#include "TopManager.h"
#include "Keyboard.h"
#include "Vehicle.h"
#include "GameMapObject.h"
#include "Map.h"

GraphicManager::GraphicManager(){}

GraphicManager::~GraphicManager(){}

void GraphicManager::chooseSceneManager()
{
  mSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC);
}

void GraphicManager::createLightNShadow()
{
  // Create sunlight
  Ogre::Light* light = mSceneMgr->createLight("Light1");
  light->setType(Ogre::Light::LT_POINT);
  light->setPosition(Ogre::Vector3(0, 1500, 0));
  light->setDiffuseColour(Ogre::ColourValue(0.8f, 0.8f, 0.8f));
  light->setSpecularColour(Ogre::ColourValue(0.8f, 0.8f, 0.8f));

  // Create headlights for the car
  Ogre::Light* headlights[] = {mSceneMgr->createLight("Headlight1"),
                               mSceneMgr->createLight("Headlight2")};
  for (int i=0; i<2; ++i)
  {
      headlights[i]->setCastShadows(false);
      headlights[i]->setType(Ogre::Light::LT_SPOTLIGHT);
      headlights[i]->setSpotlightRange(Ogre::Radian(0.1), Ogre::Radian(M_PI/3.f));
      headlights[i]->setDiffuseColour(Ogre::ColourValue(1.f, 1.f, 1.f));
      headlights[i]->setSpecularColour(Ogre::ColourValue(1.f, 1.f, 1.f));
  }

  makeDayLights();
}

void GraphicManager::toggleDayNight()
{
    if (m_daylight)
    {
        makeNightLights();
    }
    else
    {
        makeDayLights();
    }
}

void GraphicManager::makeDayLights()
{
    // Brighten the sun
    Ogre::Light* light = mSceneMgr->getLight("Light1");
    light->setVisible(true);

    // Darken the headlights
    Ogre::Light* headlight1 = mSceneMgr->getLight("Headlight1");
    headlight1->setVisible(false);
    Ogre::Light* headlight2 = mSceneMgr->getLight("Headlight2");
    headlight2->setVisible(false);

    // Change city and ground material
    if (TopManager::Instance()->isMapLoaded())
    {
        GameMapObject* city = TopManager::Instance()->getMap()->getCity();
        city->setMaterialName("cityMat");

        GameMapObject* ground = TopManager::Instance()->getMap()->getGround();
        ground->setMaterialName("groundMat");
    }

    mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
    mSceneMgr->setAmbientLight(Ogre::ColourValue(0.3, 0.3, 0.3));
    m_daylight = true;
}

void GraphicManager::makeNightLights()
{
    // Darken the sun
    Ogre::Light* light = mSceneMgr->getLight("Light1");
    light->setVisible(false);

    // Brighten the headlights
    Ogre::Light* headlight1 = mSceneMgr->getLight("Headlight1");
    headlight1->setVisible(true);
    Ogre::Light* headlight2 = mSceneMgr->getLight("Headlight2");
    headlight2->setVisible(true);

    // Change city and ground material
    if (TopManager::Instance()->isMapLoaded())
    {
        GameMapObject* city = TopManager::Instance()->getMap()->getCity();
        city->setMaterialName("Simple_Perpixel");

        GameMapObject* ground = TopManager::Instance()->getMap()->getGround();
        ground->setMaterialName("Simple_Perpixel");
    }

    mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_MODULATIVE);
    mSceneMgr->setAmbientLight(Ogre::ColourValue(0.1, 0.1, 0.1));
    m_daylight = false;
}

void GraphicManager::createScene()
{
  mCamNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(100, 0, 100));
  mCamNode->attachObject(mCamera);

  createLightNShadow();

  m_waypoints = TopManager::Instance()->getWaypoints();


  // Draw (or dont draw) the waypoints
  if (false)
  {
      //create waypoint
      Ogre::SceneNode* wprnode = mSceneMgr->getRootSceneNode()-> createChildSceneNode("waypointsroot");

      for (std::size_t i = 0; i < m_waypoints.size(); ++i)
      {
        std::stringstream ss;
        ss << "wp" << i;

        std::stringstream ss2;
        ss2 << "wpnode" << i;

        Ogre::SceneNode* citynode = wprnode->createChildSceneNode();

        Ogre::Entity* entCity = mSceneMgr->createEntity( ss.str(), "Cube.mesh");
        entCity->setCastShadows(true);
        citynode->attachObject(entCity);
        citynode->setPosition(m_waypoints[i].x, 0, m_waypoints[i].z);
        citynode->scale(0.5, 0.5, 0.5);
        //citynode->setPosition(-20, 1,-75);     //TEST
      }
      wprnode->scale(2,2,2);
  }



  TopManager::Instance()->loadMap();
  TopManager::Instance()->addPlayer();
  TopManager::Instance()->getOverlayManager()->init();
  Keyboard::Instance()->init();
  mSceneMgr->setSkyDome(true, "skymat", 76.0, 16.0, 5000.0,true);

#ifdef PROFILE
  new Ogre::Profiler();
  Ogre::Timer* timer = new Ogre::Timer();

  Ogre::Profiler::getSingleton().setTimer(timer);
  Ogre::Profiler::getSingleton().setEnabled(true);
  Ogre::Profiler::getSingleton().setUpdateDisplayFrequency(60);
#endif
}

Ogre::SceneManager* GraphicManager::getSceneManager()
{
  return mSceneMgr;
}

Ogre::RenderWindow* GraphicManager::getRenderWindow()
{
  return mWindow;
}

bool GraphicManager::frameRenderingQueued(const Ogre::FrameEvent&evt)
{
#ifdef PROFILE
  Ogre::Profiler::getSingleton().beginProfile("Ogre Main Loop");
#endif

  if(mWindow->isClosed())
    return false;

  if(mShutDown)
    return false;

  //Need to capture/update each device
  Keyboard::Instance()->capture();
  mTrayMgr->frameRenderingQueued(evt);
  TopManager::Instance()->update(evt.timeSinceLastFrame);
#ifdef PROFILE
  Ogre::Profiler::getSingleton().endProfile("Ogre Main Loop");
#endif
  return true;
}


void GraphicManager::createViewports(void)
{
  // Create one viewport, entire window
  m_vp = mWindow->addViewport(mCamera,500,0,0,1,1);
  m_vp->setBackgroundColour(Ogre::ColourValue(0,0,0));

  // Alter the camera aspect ratio to match the viewport
  mCamera->setAspectRatio(Ogre::Real(m_vp->getActualWidth()) / Ogre::Real(m_vp->getActualHeight()));

  m_vp->setClearEveryFrame(false);
}

Ogre::Viewport* GraphicManager::getViewport()
{
  return m_vp;
}

void GraphicManager::setShutdown(bool shutdown)
{
  mShutDown = shutdown;
}

void GraphicManager::createCamera(void)
{
  // Create the camera
  mCamera = mSceneMgr->createCamera("PlayerCam");

  // Position it at 500 in Z direction
  mCamera->setPosition(Ogre::Vector3(0,0,80));
  // Look back along -Z
  mCamera->lookAt(Ogre::Vector3(0,0,-300));
  mCamera->setNearClipDistance(0.1);

  //mCameraMan = new OgreBites::SdkCameraMan(mCamera);   // create a default camera controller
}
