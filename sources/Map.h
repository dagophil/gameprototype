/*
 * Map.h
 *
 */

#ifndef MAP_H_
#define MAP_H_
#include <vector>
#include "GameMapObject.h"
#include "Player.h"
#include <map>

/**
 * @class Map
 * @brief Map class
 * This holds all the unmovable objects (GameMapObjects) and defines the map of the game.
 * 
 */

class Map
{
public:
  Map();
  ~Map();

  /**
   * @brief function to call once per frame
   */
  void update();

  /**
   * @param Player
   */
  const btVector4 getStartPos(int PlayerId);

  /**
   * @brief getter for m_city
   * @return
   */
  GameMapObject* getCity();

  /**
   * @brief getter for m_ground
   * @return
   */
  GameMapObject* getGround();

private:
  void createGround();
  void createCity();
  void createTrainingEnvironment();
  void createUpgrades();

  std::vector<GameMapObject*> MapObjects;
  GameMapObject* m_city;
  GameMapObject* m_ground;
  btVector4 m_startPositions[4];
};


#endif /* MAP_H_ */
