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
#include <OGRE/Ogre.h>


float collison_length = 2.f;

Map::Map()
{
  Ogre::ResourceGroupManager::getSingletonPtr()->createResourceGroup("Map");
  Ogre::ResourceGroupManager::getSingletonPtr()->initialiseResourceGroup("Map");

  createGround();
  createCity();

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

  MapObjects[0] = new GameMapObject("ground");
  MapObjects[0]->translate(100.f,-10.f,100.f);
  MapObjects[0]->setMaterialName("Floor");
  MapObjects[0]->setCastShadows(false);

  Ogre::Plane wall1(Ogre::Vector3::UNIT_Y, 0);
  Ogre::MeshManager::getSingleton().createPlane("wall1", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, wall1, 20, 240, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_X);

  MapObjects[1] = new GameMapObject("wall1");
  MapObjects[1]->translate(100.f,0.f,-20.f);
  MapObjects[1]->pitch(Ogre::Degree(90));
  MapObjects[1]->setMaterialName("Green");
  MapObjects[1]->setCastShadows(false);

  Ogre::Plane wall2(Ogre::Vector3::UNIT_Y, 0);
  Ogre::MeshManager::getSingleton().createPlane("wall2", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, wall2, 20, 240, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_X);

  MapObjects[2] = new GameMapObject("wall2");
  MapObjects[2]->translate(100.f,0.f,220.f);
  MapObjects[2]->pitch(Ogre::Degree(-90));
  MapObjects[2]->setMaterialName("Green");
  MapObjects[2]->setCastShadows(false);

  Ogre::Plane wall3(Ogre::Vector3::UNIT_Y, 0);
  Ogre::MeshManager::getSingleton().createPlane("wall3", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, wall3, 20, 240, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_X);

  MapObjects[3] = new GameMapObject("wall3");
  MapObjects[3]->translate(-20.f,0.f,100.f);
  MapObjects[3]->pitch(Ogre::Degree(-90));
  MapObjects[3]->roll(Ogre::Degree(-90));
  MapObjects[3]->setMaterialName("Blue");
  MapObjects[3]->setCastShadows(false);

  Ogre::Plane wall4(Ogre::Vector3::UNIT_Y, 0);
  Ogre::MeshManager::getSingleton().createPlane("wall4", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, wall4, 20, 240, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_X);

  MapObjects[4] = new GameMapObject("wall4");
  MapObjects[4]->translate(220.f,0.f,100.f);
  MapObjects[4]->pitch(Ogre::Degree(-90));
  MapObjects[4]->roll(Ogre::Degree(90));
  MapObjects[4]->setMaterialName("Blue");
  MapObjects[4]->setCastShadows(false);

  m_startPositions[0] = btVector4(100.f,-4.f,100.f,0.f);
  m_startPositions[1] = btVector4(190.f,-4.f,190.f,180.f);
  m_startPositions[2] = btVector4(10.f,-4.f,190.f,90.f);
  m_startPositions[3] = btVector4(190.f,-4.f,10.f,270.f);

}

Map::~Map(){}

void Map::createGround()
{
	// create plane with stones texture as floor
	Ogre::Plane plane;
	plane.normal = Ogre::Vector3::UNIT_Y;
	plane.d = 0;
 
	Ogre::MeshManager::getSingleton().createPlane("ground", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane, 100000.0f, 100000.0f, 10, 10, true, 1, 50.0f, 50.0f, Ogre::Vector3::UNIT_Z);

	MapObjects[0] = new GameMapObject("ground");
    MapObjects[0]->translate(0.f,0.f,0.f);
    MapObjects[0]->setMaterialName("groundMat");
    MapObjects[0]->setCastShadows(false);
}

void Map::createCity()
{
	MapObjects[1] = new GameMapObject("city.mesh");
    MapObjects[1]->translate(0.f,0.f,0.f);
	MapObjects[1]->scale(2.f,2.f,2.f);
    MapObjects[1]->setCastShadows(true);

}

const btVector4 Map::getStartPos(int playerId)
{
  return m_startPositions[playerId];
}
