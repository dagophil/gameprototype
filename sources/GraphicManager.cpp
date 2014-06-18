/*
 * GraphicManager.cpp
 *
 */
#include "TopManager.h"
#include "GraphicManager.h"
#include "BaseApplication.h"
#include "TopManager.h"
#include "Keyboard.h"

GraphicManager::GraphicManager(){}

GraphicManager::~GraphicManager(){}

void GraphicManager::chooseSceneManager()
{
  mSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC);
}

void GraphicManager::createLightNShadow()
{
  mSceneMgr->setAmbientLight(Ogre::ColourValue(0.3, 0.3, 0.3));

  Ogre::Light *light = mSceneMgr->createLight("Light1");
  light->setType(Ogre::Light::LT_POINT);
  light->setPosition(Ogre::Vector3(0, 1500, 0));
  light->setDiffuseColour(Ogre::ColourValue(0.8f, 0.8f, 0.8f));//(Ogre::ColourValue::White);
  light->setSpecularColour(Ogre::ColourValue(0.8f, 0.8f, 0.8f));//(Ogre::ColourValue::White);

  //Ogre::Light* l = TopManager::Instance()->getGraphicManager()->getSceneManager()->createLight("MainLight");
  //l->setType(Ogre::Light::LT_POINT);
  //l->setPosition(100,500,100);
  //l->setPosition(100,300,100);

  mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
}

void GraphicManager::createScene()
{
  mCamNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(100, 0, 100));
  mCamNode->attachObject(mCamera);

  createLightNShadow();

  m_waypoints = TopManager::Instance()->getWaypoints();

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
