/*
 * Manager.cpp
 *
 */
#include <bullet/btBulletCollisionCommon.h>
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
#include "DebugDrawer.h"
#include "PointReader.h"
#include "Graph.h"

TopManager* TopManager::m_Instance = 0;

TopManager* TopManager::Instance()
{
  if(m_Instance == 0)
    m_Instance = new TopManager();
  return m_Instance;
}

void collisionCallback(btDynamicsWorld *world, btScalar timeStep)
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
          if(contactManifold->getContactPoint(j).getDistance() < 0.f)
          {
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
  m_debugDrawer = new DebugDrawer();

  m_PhysicsManager->getDynamicsWorld()->setDebugDrawer(m_debugDrawer);
  m_PhysicsManager->getDynamicsWorld()->setInternalTickCallback(collisionCallback);

  PointReader reader("waypoints1.txt");

  std::vector<Ogre::Vector3> waypoints = reader.getWayPoints();
  for (size_t i = 0; i < waypoints.size(); ++i) {
      m_waypoints.push_back(Ogre::Vector3(waypoints[i]));
  }

  m_graph = new Graph(m_waypoints);

  m_mapLoaded = false;
}

TopManager::~TopManager()
{
  delete m_PhysicsManager;
  delete m_debugDrawer;
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

void TopManager::update(const float & timestep)
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

/*
#ifdef PROFILE
  Ogre::Profiler::getSingleton().beginProfile( "debugDrawer" );
#endif
  DebugDrawer* debugDrawer = static_cast<DebugDrawer*>(m_debugDrawer);
  debugDrawer->resetLines();
  m_PhysicsManager->getDynamicsWorld()->debugDrawWorld();

#ifdef PROFILE
  Ogre::Profiler::getSingleton().endProfile( "debugDrawer" );
#endif
*/
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
