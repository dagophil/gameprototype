#ifndef PLAYER_H_
#define PLAYER_H_


#include <vector>
#include "PlayerInput.h"
#include "TopManager.h"
#include "GraphicManager.h"
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <OGRE/OgreCommon.h>
#include <cstdlib>
/**
 *
 * @class Player
 * @brief Player class
 * Everything related to the player logic like view, controllers score, lives, etc is here
 * It has a connection to the corresponding Vehicle class (which is responsible for Physics and Graphics)
 */

class PlayerInput;
class Vehicle;

class Player
{
public:

  /**
   *
   * @param playerId player number
   */
  Player(int playerId);

  /**
   *
   * @brief getter for Vehicle*
   * @return Pointer to corresponding Vehicle.
   */
  Vehicle*getVehicle();

  /**
   *
   * @brief function to call once per frame
   *
   */
  void update();

  /**
   * @brief function to increase score
   */
  void addLive();

  /**
   * @brief function to decrease score
   */
  void removeLive();

  /**
   * @brief getter for number of lives
   * @return
   */
  int getLives();

  /**
   * @brief getter for x-position
   * @return
   */
  int getX();

  /**
   * @brief getter for y-position
   * @return
   */
  int getY();

  /**
   * @brief getter for z-position
   * @return
   */
  int getZ();

  /**
   * @brief getter for angle
   */
  Ogre::Radian getAngle();

  /**
   * @brief getter for player id
   * @return
   */
  int getId();

  /**
   * @brief getter for milliseconds since creation
   * @return
   */
  unsigned long getMilliseconds();

  void disableJoystick();
private:
  void createViewport();
  void createPlayerCam();
  void updateTank();
  int m_playerId;
  int m_lives;
  Vehicle * m_vehicle;
  PlayerInput * m_input;
  Ogre::Viewport* m_playerVp;
  Ogre::Camera * m_playerCam;
  Ogre::Timer * m_timer;
  int m_joystick;
};

#endif
