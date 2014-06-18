/*
 * Manager.cpp
 *
 */
#include <btBulletDynamicsCommon.h>
#include <OGRE/OgreCommon.h>
#include <time.h>
#include <typeinfo>


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
          if(contactManifold->getContactPoint(j).getDistance() < 0.f) /*
            if (obAF->getType()==2)
              std::cout<<obBF<<std::endl;
            if (obBF->getType()==2)
              std::cout<<obAF<<std::endl;*/
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
  m_waypoints = reader.getWayPoints();
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

void TopManager::addPlayer()
{
  Player * newPlayer = new Player(PlayerList.size());
  PlayerList.push_back(newPlayer);
}

void TopManager::loadMap()
{
  m_Map = new Map;
}


void TopManager::update(const float&timestep)
{
#ifdef PROFILE
  Ogre::Profiler::getSingleton().beginProfile("Physik");
#endif
  m_PhysicsManager->getDynamicsWorld()->stepSimulation(2.0 * timestep, 10);

#ifdef PROFILE
  Ogre::Profiler::getSingleton().endProfile("Physik");
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
    PlayerList[i]->update();
  }

#ifdef PROFILE
  Ogre::Profiler::getSingleton().endProfile("Player Update");
#endif
}
