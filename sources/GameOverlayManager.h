/*
 * OverlayManager.h
 *
 */

#ifndef OVERLAYMANAGER_H_
#define OVERLAYMANAGER_H_


#include <OGRE/OgreOverlayManager.h>
#include <OGRE/OgreOverlay.h>
#include <OGRE/OgreOverlayContainer.h>
#include <OGRE/OgreTextAreaOverlayElement.h>

#include "TopManager.h"
#include "GameObject.h"

/**
 * @class GameOverlayManager
 * @brief manager class for overlays
 */
class GameOverlayManager
{

public:

  GameOverlayManager();
  virtual ~GameOverlayManager();

  /**
   * getter for OgreOverlayManager
   * @return Ogre::OverlayManager*
   */
  Ogre::OverlayManager *getOverlayManager();

  /**
   * @brief update function, has to be called after each change in score
   */
  void update();

  /**
   * @brief init function for overlays
   */
  void init();

  /**
   * @brief updates minimap, must be called each frame
   */
  void updateMapOverlay();

  void showGameOver(std::string largeText, std::string smallText);

private:

  void createMapOverlay();
  Ogre::OverlayManager * m_overlayMgr;
  Ogre::Overlay* m_overlay;
  int m_dimX;
  int m_dimY;

};

#endif /* OVERLAYMANAGER_H_ */
