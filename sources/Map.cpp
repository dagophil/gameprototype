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
#include "Upgrade.h"
#include "PointReader.h"
#include "Opponent.h"
#include <OGRE/Ogre.h>
#include <OGRE/OgreVector3.h>


float collison_length = 2.f;

Map::Map()
{
    Ogre::ResourceGroupManager::getSingletonPtr()->createResourceGroup("Map");
    Ogre::ResourceGroupManager::getSingletonPtr()->initialiseResourceGroup("Map");

    createGround();
    createCity();
    createUpgrades();
    createOpponents();

    m_startPositions[0] = btVector4(-22.f, 2.f,-84.f,0.f);
    m_startPositions[1] = btVector4(190.f,2.f,190.f,180.f);
    m_startPositions[2] = btVector4(10.f,2.f,190.f,90.f);
    m_startPositions[3] = btVector4(190.f,2.f,10.f,270.f);
}

Map::~Map()
{
    m_upgrades.clear();
}

void Map::update(const float & timestep)
{
    typedef std::vector<GameMapObject*>::iterator objIter;
    for (objIter iter = m_upgrades.begin(); iter != m_upgrades.end(); ++iter)
    {
        (*iter)->update(timestep);
    }

    typedef std::vector<Opponent*>::iterator oppIter;
    for(oppIter iter = m_opponents.begin(); iter != m_opponents.end(); ++iter)
    {
        (*iter)->update(timestep);
    }
}

void Map::createGround()
{
    // create plane with stones texture as floor
    Ogre::Plane plane;
    plane.normal = Ogre::Vector3::UNIT_Y;
    plane.d = 0;

    Ogre::MeshManager::getSingleton().createPlane("ground", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane, 100000.0f, 100000.0f, 10, 10, true, 1, 50.0f, 50.0f, Ogre::Vector3::UNIT_Z);

    m_ground = new GameMapObject("ground", true, false, GameObject::Ground);
    m_ground->translate(0.f,0.f,0.f);
    m_ground->setMaterialName("groundMat");
    m_ground->setCastShadows(false);
}

void Map::createCity()
{
    m_city = new GameMapObject("city.mesh");
    m_city->translate(0.f,0.f,0.f);
    m_city->scale(2.f,2.f,2.f);
    m_city->setCastShadows(true);
    m_city->setMaterialName("cityMat");
}

void Map::createUpgrades()
{
    typedef std::vector<Ogre::Vector3>::iterator vecIter;

    PointReader reader("fuelupgrades.txt");
    std::vector<Ogre::Vector3> waypoints = std::vector<Ogre::Vector3>(reader.getWayPoints());
    for (vecIter iter = waypoints.begin(); iter != waypoints.end(); iter++) {
        GameMapObject* upgr = new Upgrade("oildrum.mesh", GameObject::FuelUpgrade);
        upgr->setMaterialName("Oildrum-ref");
        upgr->translate(2*iter->x, 1.5f, 2*iter->z);
        m_upgrades.push_back(upgr);
    }
}

void Map::createOpponents()
{
	for (int i = 0; i < 10; i++) {
		Opponent* opp = new Opponent("opponent.mesh", GameObject::Opponent);
		opp->translate(-16, 1.5, -74);
		opp->scale(0.5, 0.5, 0.5);
		opp->findPath();
		m_opponents.push_back(opp);
	}

}

void Map::changeToDayMaterials()
{
    m_city->setMaterialName("cityMat");
    m_ground->setMaterialName("groundMat");

    typedef std::vector<GameMapObject*>::iterator upgrIter;
    for (upgrIter iter = m_upgrades.begin(); iter != m_upgrades.end(); iter++)
    {
        if ((*iter)->getType() == GameObject::FuelUpgrade)
        {
            (*iter)->setMaterialName("Oildrum-ref");
        }
    }
}

void Map::changeToNightMaterials()
{
    m_city->setMaterialName("Simple_Perpixel");
    m_ground->setMaterialName("Simple_Perpixel");

    typedef std::vector<GameMapObject*>::iterator upgrIter;
    for (upgrIter iter = m_upgrades.begin(); iter != m_upgrades.end(); iter++)
    {
        if ((*iter)->getType() == GameObject::FuelUpgrade)
        {
            (*iter)->setMaterialName("Simple_Perpixel_Oildrum");
        }
    }
}

const btVector4 Map::getStartPos(int playerId)
{
    return m_startPositions[playerId];
}
