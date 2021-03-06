/*
 * Manager.cpp
 *
 */
#include <btBulletCollisionCommon.h>
#include <OGRE/OgreCommon.h>
#include <time.h>
#include <typeinfo>
#include <vector>

#include "TopManager.h"
#include "Player.h"
#include "Map.h"
#include "PhysicsManager.h"
#include "GraphicManager.h"
#include "GameOverlayManager.h"
#include "GameObject.h"
#include "GameMapObject.h"
#include "Vehicle.h"
#include "PointReader.h"
#include "Graph.h"

TopManager* TopManager::m_Instance = 0;

TopManager* TopManager::Instance()
{
    if(m_Instance == 0)
        m_Instance = new TopManager();
    return m_Instance;
}

void collisionCallback(btDynamicsWorld* world, btScalar timeStep)
{
    int numManifolds = world->getDispatcher()->getNumManifolds();
    for (int i = 0; i < numManifolds; i++)
    {
        btPersistentManifold* contactManifold =  world->getDispatcher()->getManifoldByIndexInternal(i);
        btCollisionObject* obA = const_cast<btCollisionObject*>(contactManifold->getBody0());
        btCollisionObject* obB = const_cast<btCollisionObject*>(contactManifold->getBody1());
        if(obA && obB)
        {
            GameObject* obAF = reinterpret_cast<GameObject*>(obA->getUserPointer());
            GameObject* obBF = reinterpret_cast<GameObject*>(obB->getUserPointer());

            if(obAF&&obBF)
            {
                int numContacts = contactManifold->getNumContacts();

                for (int j = 0; j < numContacts; j++)
                {
                    btManifoldPoint& pt = contactManifold->getContactPoint(j);
                    if(pt.getDistance() < 0.f)
                    {
//                        const btVector3 & ptA = pt.getPositionWorldOnA();
//                        const btVector3 & ptB = pt.getPositionWorldOnB();
//                        const btVector3 & normalOnB = pt.m_normalWorldOnB;
                        obAF->CollideWith(obBF->getType());
                        obBF->CollideWith(obAF->getType());
                        break;
                    }
                }
            }
        }
    }
}

TopManager::TopManager()
{
    srand(time(NULL));
    m_GraphicManager  = new GraphicManager;
    m_PhysicsManager  = new PhysicsManager;
    m_OverlayManager  = new GameOverlayManager;

    m_PhysicsManager->getDynamicsWorld()->setInternalTickCallback(collisionCallback);

    PointReader reader("waypoints_philip.txt");

    std::vector<Ogre::Vector3> waypoints = reader.getWayPoints();
    for (size_t i = 0; i < waypoints.size(); ++i) {
        m_waypoints.push_back(Ogre::Vector3(waypoints[i]));
    }

    m_graph = new Graph(m_waypoints);

    m_mapLoaded = false;
    m_gameOver = false;
    m_moveOpponents = true;
}

TopManager::~TopManager()
{
    delete m_PhysicsManager;
    delete m_OverlayManager;
    delete m_GraphicManager;
}

PhysicsManager* TopManager::getPhysicsManager()
{
    return m_PhysicsManager;
}

GraphicManager* TopManager::getGraphicManager()
{
    return m_GraphicManager;
}

GameOverlayManager* TopManager::getOverlayManager()
{
    return m_OverlayManager;
}

Map* TopManager::getMap()
{
    return m_Map;
}

Player* TopManager::getPlayer()
{
    return PlayerList[0];
}

Graph* TopManager::getGraph()
{
    return m_graph;
}

void TopManager::addPlayer()
{
    Player * newPlayer = new Player(PlayerList.size());
    PlayerList.push_back(newPlayer);
}

std::vector<Ogre::Vector3> TopManager::getWaypoints() {
    return m_waypoints;
}

void TopManager::loadMap()
{
    m_Map = new Map;
    m_mapLoaded = true;
}

bool TopManager::isMapLoaded()
{
    return m_mapLoaded;
}

void TopManager::toggleOpponentMovement()
{
    m_moveOpponents = !m_moveOpponents;
}

bool TopManager::getMoveOpponents()
{
    return m_moveOpponents;
}

void TopManager::game_over(const bool & win)
{
    m_gameOver = true;

    long milliseconds = PlayerList[0]->getMilliseconds();
    long seconds = milliseconds/1000;
    long minutes = seconds/60;
    milliseconds = milliseconds % 1000;
    seconds = seconds % 60;

    std::stringstream ss;
    ss << std::setfill('0');
    ss << "Deine Zeit: ";
    ss << minutes << ":" << std::setw(2) << seconds << ":" << std::setw(3) << milliseconds;

    if (win)
    {
        m_OverlayManager->showGameOver("Sieg!", ss.str());
    }
    else
    {
        m_OverlayManager->showGameOver("Verloren!", ss.str());
    }
}

void TopManager::update(const float & timestep)
{
    if (!m_gameOver)
    {
#ifdef PROFILE
        Ogre::Profiler::getSingleton().beginProfile("Physik");
#endif

        m_PhysicsManager->getDynamicsWorld()->stepSimulation(2.0 * timestep, 10);

#ifdef PROFILE
        Ogre::Profiler::getSingleton().endProfile("Physik");
#endif

        // Update the map
#ifdef PROFILE
        Ogre::Profiler::getSingleton().beginProfile("Map Update");
#endif

        m_Map->update(timestep);

#ifdef PROFILE
        Ogre::Profiler::getSingleton().endProfile("Map Update");
#endif

        // Update all Players
#ifdef PROFILE
        Ogre::Profiler::getSingleton().beginProfile("Player Update");
#endif

        for(unsigned int i = 0; i < PlayerList.size(); i++)
        {
            PlayerList[i]->update(timestep);
        }

#ifdef PROFILE
        Ogre::Profiler::getSingleton().endProfile("Player Update");
#endif
    }
}
