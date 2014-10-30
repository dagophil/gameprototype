/*
 * Map.h
 *
 */

#ifndef MAP_H_
#define MAP_H_
#include <vector>
#include "GameMapObject.h"
#include "Upgrade.h"
#include "Player.h"
#include "Opponent.h"
#include <string>
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

    typedef std::vector<Opponent*>::iterator OpponentIter;
    typedef std::vector<Upgrade*>::iterator UpgradeIter;
    typedef std::vector<Ogre::Vector3>::iterator VecIter;

    Map();

    ~Map();

    static const std::string MAT_OILDRUM;
    static const std::string MAT_OILDRUM_PP;
    static const std::string MAT_GROUND;
    static const std::string MAT_GROUND_PP;
    static const std::string MAT_CITY;
    static const std::string MAT_CITY_PP;
    static const std::string MAT_OPP_RED;
    static const std::string MAT_OPP_BLUE;
    static const std::string MAT_OPP_GREEN;
    static const std::string MAT_OPP_YELLOW;
    static const std::string MAT_OPP_PURPLE;

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

    /**
     * @brief toggle visibility of opponent bounding boxes
     */
    void toggleOpponentBoundingBoxes();

    /**
     * @brief return the number of opponents
     */
    size_t getNumOpponents() const;

private:

    void createGround();
    void createCity();
    void createUpgrades();
    void createOpponents();

    GameMapObject* m_city;
    GameMapObject* m_ground;
    std::vector<Upgrade*> m_upgrades;
    std::vector<Opponent*> m_opponents;
    btVector4 m_startPositions[4];

};

#endif /* MAP_H_ */
