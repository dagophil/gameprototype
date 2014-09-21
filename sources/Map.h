/*
 * Map.h
 *
 */

#ifndef MAP_H_
#define MAP_H_
#include <vector>
#include "GameMapObject.h"
#include "Player.h"
#include "Opponent.h"
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
    void update(const float & timestep);

    /**
     * @param Player
     */
    const btVector4 getStartPos(int PlayerId);

    /**
     * @brief set materials to day materials
     */
    void changeToDayMaterials();

    /**
     * @brief set materials to night materials
     */
    void changeToNightMaterials();

private:

    void createGround();
    void createCity();
    void createUpgrades();
    void createOpponents();

    GameMapObject* m_city;
    GameMapObject* m_ground;
    std::vector<GameMapObject*> m_upgrades;
    std::vector<Opponent*> m_opponents;
    btVector4 m_startPositions[4];

};

#endif /* MAP_H_ */
