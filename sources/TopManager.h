/*
 * Manager.h
 *
 */

#ifndef TOPMANAGER_H_
#define TOPMANAGER_H_

#include <vector>
#include <list>
#include "GameOverlayManager.h"

class Map;
class Player;
class GraphicManager;
class PhysicsManager;
class GameOverlayManager;
class GameObject;
class Graph;

/**
 * @class TopManager
 * @brief Singelton class. Manager class to get other managers
 * Use that class to get anything you need in any place in the code.
 * You may get  PhysicsManager, GraphicManager, GameOverlayManager, Map, Players or Waypoints
 */
class TopManager
{

public:

    ~TopManager();

    /**
     * @brief Instance for singelton
     * @return pointer to Manager
     */
    static TopManager* Instance();

    /**
     * @brief getter PhsicsManager
     * @return Pointer to PhysicsManager
     */
    PhysicsManager* getPhysicsManager();

    /**
     * @brief getter for GraphicsManager
     * @return pointer to GraphicManager
     */
    GraphicManager* getGraphicManager();

    /**
     * @brief getter for OverlayManager
     * @return pointer to OverlayManager
     */
    GameOverlayManager* getOverlayManager();

    /**
     * @brief getter fo Map
     * @return pointer to Map
     */
    Map* getMap();

    /**
     * @brief getter for Player
     * @param playerId
     * @return pointer to Player
     */
    Player* getPlayer();

    /**
     * @brief getter for Graph
     * @return pointer to Graph
     */
    Graph* getGraph();

    /**
     * @brief Adds player to game
     */
    void addPlayer();

    /**
     * @brief load the map
     */
    void loadMap();

    /**
     * @brief getter for m_mapLoaded
     * @return
     */
    bool isMapLoaded();

    /**
     * @brief update function. is called every frame
     * @param timestep
     */
    void update(const float& timestep);

    /**
     * @brief ends the game
     * @param win
     */
    void game_over(const bool & win);

    /**
     * @brief toggle movement of opponents
     */
    void toggleOpponentMovement();

    /**
     * @brief getter for m_moveOpponents
     * @return m_moveOpponents
     */
    bool getMoveOpponents();

    /**
     * @brief getter for m_waypoints
     * @return
     */
    std::vector<Ogre::Vector3> getWaypoints();

private:

    TopManager();
    static TopManager* m_Instance;
    PhysicsManager* m_PhysicsManager;
    GraphicManager* m_GraphicManager;
    GameOverlayManager* m_OverlayManager;
    Map* m_Map;
    bool m_mapLoaded;
    std::vector<Player*> PlayerList;
    std::vector<Ogre::Vector3> m_waypoints;
    Graph* m_graph;
    bool m_gameOver;
    bool m_moveOpponents;

};

#endif /* MANAGER_H_ */
