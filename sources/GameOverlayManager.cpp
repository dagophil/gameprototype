/*
 * OverlayManager.cpp
 *
 */

#include "GameOverlayManager.h"

#include "Player.h"

GameOverlayManager::GameOverlayManager() {}

GameOverlayManager::~GameOverlayManager()
{
  // TODO Auto-generated destructor stub
}

Ogre::OverlayManager * GameOverlayManager::getOverlayManager()
{
  return m_overlayMgr;
}

void GameOverlayManager::init()
{
  m_overlayMgr = Ogre::OverlayManager::getSingletonPtr();
  m_dimX = TopManager::Instance()->getGraphicManager()->getViewport()->getActualWidth();
  m_dimY = TopManager::Instance()->getGraphicManager()->getViewport()->getActualHeight();

  // Load the font (fixes bug with invisible overlays).
  Ogre::FontManager::getSingleton().getByName("SdkTrays/Caption")->load();

  // creates overlays (for all players)
  Ogre::Overlay *overlayPlayer = Ogre::OverlayManager::getSingleton().getByName("Player/Overlay");
  //Ogre::OverlayManager::getSingleton().getOverlayElement("Player/TextScore")->setPosition(0,0);
  overlayPlayer->show();

  Ogre::Overlay *overlayClock = Ogre::OverlayManager::getSingleton().getByName("Clock/Overlay");
  overlayClock->show();

  update();
  createMapOverlay();
}

void GameOverlayManager::update()
{
  // changes overlays to actual values (player lives, etc..) called after every change of score

  Player* player = TopManager::Instance()->getPlayer();

  std::string scoreOverlayName = "Player/TextScore";
  std::stringstream ss;
  ss << "Leben: ";
  ss << player->getLives();
  //std::cout << "Leben: "<<player->getLives()<< std::endl;
  std::string liveText;
  liveText = ss.str();

  Ogre::OverlayManager::getSingleton().getOverlayElement(scoreOverlayName)->setCaption(liveText);


  // Get current playing time in minutes, seconds and milliseconds.
  long milliseconds = player->getMilliseconds();
  long seconds = milliseconds/1000;
  long minutes = seconds/60;
  milliseconds = milliseconds % 1000;
  seconds = seconds % 60;

  // Create a string for the playing time.
  // Format min:secs:msecs with leading zeros for seconds and milliseconds.
  std::stringstream ss2;
  ss2 << std::setfill('0');
  ss2 << "Zeit: ";
  ss2 << minutes << ":" << std::setw(2) << seconds << ":" << std::setw(3) << milliseconds;
  std::string clockText = ss2.str();

  // Update the clock text overlay.
  std::string clockOverlayName = "Clock/Text";
  Ogre::OverlayManager::getSingleton().getOverlayElement(clockOverlayName)->setCaption(clockText);

}

void GameOverlayManager::createMapOverlay()
{
  // Create map container
  /*Ogre::OverlayContainer* mapContainer = static_cast<Ogre::OverlayContainer*>(
       m_overlayMgr->createOverlayElement("Panel", "MapContainer"));
  mapContainer->setMetricsMode(Ogre::GMM_RELATIVE);
  mapContainer->setPosition(0.5, 1);
  mapContainer->setMetricsMode(Ogre::GMM_PIXELS);
  mapContainer->setDimensions(100, 100);

  Ogre::OverlayElement* map = static_cast<Ogre::OverlayElement*>(m_overlayMgr->createOverlayElement("Panel","Map"));
  map->setMaterialName("Overlay/Map");
  map->setDimensions(100,100);
  mapContainer->addChild(map);
  mapContainer->show();

  Ogre::Overlay* overlay = m_overlayMgr->create("MapOverlay");
  overlay->setZOrder(500);
  overlay->add2D(mapContainer);
  */
  Ogre::OverlayManager::getSingleton().getOverlayElement("MapContainer")->setPosition((m_dimX / 2) - 120,m_dimY - 240);

  Ogre::Overlay* playerMarker;
  playerMarker = Ogre::OverlayManager::getSingleton().getByName("Player/MapPosition");
  playerMarker->show();

  //xxx Ogre::Overlay *overlayMap = Ogre::OverlayManager::getSingleton().getByName("Map/Overlay");
  //xxx enable again if used... overlayMap->show();
}

void GameOverlayManager::updateMapOverlay()
{
  int offsetX;
  int offsetY;
  offsetX = (m_dimX / 2) - 120;
  offsetY = (m_dimY) - 240;

  int posX = TopManager::Instance()->getPlayer()->getX() + 20;
  int posY = TopManager::Instance()->getPlayer()->getZ() + 20;
  std::string overlayName;
  overlayName = "Player/MapMarker";
  Ogre::OverlayManager::getSingleton().getOverlayElement(overlayName)->setPosition(posX + offsetX,posY + offsetY);
  Ogre::OverlayManager::getSingleton().getOverlayElement(overlayName)->setParameter("rotation","30,0,1,0");
}
