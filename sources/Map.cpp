/*
 * Map.cpp
 *
 */

#include "Map.h"
#include "GameMapObject.h"
#include "GameMovableObject.h"
#include "TopManager.h"
#include "GraphicManager.h"
#include "Vehicle.h"
#include "FuelUpgrade.h"
#include <OGRE/Ogre.h>


float collison_length = 2.f;

Map::Map()
{
  Ogre::ResourceGroupManager::getSingletonPtr()->createResourceGroup("Map");
  Ogre::ResourceGroupManager::getSingletonPtr()->initialiseResourceGroup("Map");

  createGround();
  createCity();
  createUpgrades();

  m_startPositions[0] = btVector4(-20.f, 2.f,-85.f,0.f);
  m_startPositions[1] = btVector4(190.f,2.f,190.f,180.f);
  m_startPositions[2] = btVector4(10.f,2.f,190.f,90.f);
  m_startPositions[3] = btVector4(190.f,2.f,10.f,270.f);
}

void Map::createTrainingEnvironment()
{
  Ogre::ResourceGroupManager::getSingletonPtr()->createResourceGroup("Map");
  Ogre::ResourceGroupManager::getSingletonPtr()->initialiseResourceGroup("Map");

  Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
  Ogre::MeshManager::getSingleton().createPlane("ground", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane, 240, 240, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);

  GameMapObject* groundObj = new GameMapObject("ground");
  groundObj->translate(100.f,-10.f,100.f);
  groundObj->setMaterialName("Floor");
  groundObj->setCastShadows(false);
  MapObjects.push_back(groundObj);

  Ogre::Plane wall1(Ogre::Vector3::UNIT_Y, 0);
  Ogre::MeshManager::getSingleton().createPlane("wall1", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, wall1, 20, 240, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_X);

  GameMapObject* wall1Obj = new GameMapObject("wall1");
  wall1Obj->translate(100.f,0.f,-20.f);
  wall1Obj->pitch(Ogre::Degree(90));
  wall1Obj->setMaterialName("Green");
  wall1Obj->setCastShadows(false);
  MapObjects.push_back(wall1Obj);

  Ogre::Plane wall2(Ogre::Vector3::UNIT_Y, 0);
  Ogre::MeshManager::getSingleton().createPlane("wall2", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, wall2, 20, 240, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_X);

  GameMapObject* wall2Obj = new GameMapObject("wall2");
  wall2Obj->translate(100.f,0.f,220.f);
  wall2Obj->pitch(Ogre::Degree(-90));
  wall2Obj->setMaterialName("Green");
  wall2Obj->setCastShadows(false);
  MapObjects.push_back(wall2Obj);

  Ogre::Plane wall3(Ogre::Vector3::UNIT_Y, 0);
  Ogre::MeshManager::getSingleton().createPlane("wall3", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, wall3, 20, 240, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_X);

  GameMapObject* wall3Obj = new GameMapObject("wall3");
  wall3Obj->translate(-20.f,0.f,100.f);
  wall3Obj->pitch(Ogre::Degree(-90));
  wall3Obj->roll(Ogre::Degree(-90));
  wall3Obj->setMaterialName("Blue");
  wall3Obj->setCastShadows(false);
  MapObjects.push_back(wall3Obj);

  Ogre::Plane wall4(Ogre::Vector3::UNIT_Y, 0);
  Ogre::MeshManager::getSingleton().createPlane("wall4", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, wall4, 20, 240, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_X);

  GameMapObject* wall4Obj = new GameMapObject("wall4");
  wall4Obj->translate(220.f,0.f,100.f);
  wall4Obj->pitch(Ogre::Degree(-90));
  wall4Obj->roll(Ogre::Degree(90));
  wall4Obj->setMaterialName("Blue");
  wall4Obj->setCastShadows(false);
  MapObjects.push_back(wall4Obj);

  m_startPositions[0] = btVector4(100.f,-4.f,100.f,0.f);
  m_startPositions[1] = btVector4(190.f,-4.f,190.f,180.f);
  m_startPositions[2] = btVector4(10.f,-4.f,190.f,90.f);
  m_startPositions[3] = btVector4(190.f,-4.f,10.f,270.f);

}

Map::~Map()
{
    MapObjects.clear();
}

void Map::createGround()
{
	// create plane with stones texture as floor
	Ogre::Plane plane;
	plane.normal = Ogre::Vector3::UNIT_Y;
	plane.d = 0;
 
	Ogre::MeshManager::getSingleton().createPlane("ground", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane, 100000.0f, 100000.0f, 10, 10, true, 1, 50.0f, 50.0f, Ogre::Vector3::UNIT_Z);

    GameMapObject* groundObj = new GameMapObject("ground");
    groundObj->translate(0.f,0.f,0.f);
    groundObj->setMaterialName("groundMat");
    groundObj->setCastShadows(false);
    MapObjects.push_back(groundObj);
}

void Map::createCity()
{
    GameMapObject* cityObj = new GameMapObject("city.mesh");
    cityObj->translate(0.f,0.f,0.f);
    cityObj->scale(2.f,2.f,2.f);
    cityObj->setCastShadows(true);
    MapObjects.push_back(cityObj);
}

void Map::createUpgrades()
{
    GameMapObject* upgr = new FuelUpgrade("Cube.mesh");
    upgr->translate(-24.f, 1.5f,-64.f);
    MapObjects.push_back(upgr);
}

const btVector4 Map::getStartPos(int playerId)
{
  return m_startPositions[playerId];
}
