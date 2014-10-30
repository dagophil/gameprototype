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

const std::string Map::MAT_OILDRUM = "Oildrum-ref";
const std::string Map::MAT_OILDRUM_PP = "Oildrum-ref-PP";
const std::string Map::MAT_GROUND = "groundMat";
const std::string Map::MAT_GROUND_PP = "groundMat-PP";
const std::string Map::MAT_CITY = "cityMat";
const std::string Map::MAT_CITY_PP = "cityMat-PP";
const std::string Map::MAT_OPP_RED = "redMat";
const std::string Map::MAT_OPP_BLUE = "blueMat";
const std::string Map::MAT_OPP_GREEN = "greenMat";
const std::string Map::MAT_OPP_YELLOW = "yellowMat";
const std::string Map::MAT_OPP_PURPLE = "purpleMat";

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
    for (UpgradeIter iter = m_upgrades.begin(); iter != m_upgrades.end(); ++iter)
    {
        (*iter)->update(timestep);
    }

    for(OpponentIter iter = m_opponents.begin(); iter != m_opponents.end(); ++iter)
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
    m_ground->setMaterialName(MAT_GROUND);
    m_ground->setCastShadows(false);
}

void Map::createCity()
{
    m_city = new GameMapObject("city.mesh");
    m_city->translate(0.f,0.f,0.f);
    m_city->scale(2.f,2.f,2.f);
    m_city->setCastShadows(true);
    m_city->setMaterialName(MAT_CITY);
}

void Map::createUpgrades()
{
    PointReader reader("fuelupgrades.txt");
    std::vector<Ogre::Vector3> waypoints = std::vector<Ogre::Vector3>(reader.getWayPoints());
    for (VecIter iter = waypoints.begin(); iter != waypoints.end(); ++iter) {
        Upgrade* upgr = new Upgrade("oildrum.mesh", GameObject::FuelUpgrade);
        upgr->setMaterialName(MAT_OILDRUM);
        upgr->translate(2*iter->x, 1.5f, 2*iter->z);
        upgr->yaw(Ogre::Degree(rand() % 360));
        m_upgrades.push_back(upgr);
    }
}

void Map::createOpponents()
{
	std::vector<std::string> colors;
    colors.push_back(MAT_OPP_RED);
    colors.push_back(MAT_OPP_BLUE);
    colors.push_back(MAT_OPP_GREEN);
    colors.push_back(MAT_OPP_YELLOW);
    colors.push_back(MAT_OPP_PURPLE);

    for (int i = 0; i < 40; i++) {
		Opponent* opp = new Opponent("opponent.mesh", GameObject::Opponent);
		// opp->translate(-16, 1.5, -74);
		opp->scale(0.5, 0.5, 0.5);
		opp->findPath();
		int randomSpeed = rand() % 100 + 10;
		if ( i % 2 == 0) {
			opp->setRollSpeed(-randomSpeed / 50.0);
		}
		else {
			opp->setRollSpeed(randomSpeed / 50.0 );
		}
        opp->getEntity()->getSubEntity(0)->setMaterialName(colors.at(i % colors.size()));
		m_opponents.push_back(opp);
	}
}

void Map::toggleOpponentBoundingBoxes()
{
    for (OpponentIter iter = m_opponents.begin(); iter != m_opponents.end(); ++iter)
    {
        (*iter)->toggleBoundingBox();
    }
}

void Map::changeToDayMaterials()
{
    m_city->setMaterialName(MAT_CITY);
    m_ground->setMaterialName(MAT_GROUND);

    for (UpgradeIter iter = m_upgrades.begin(); iter != m_upgrades.end(); ++iter)
    {
        if ((*iter)->getType() == GameObject::FuelUpgrade)
        {
            (*iter)->setMaterialName(MAT_OILDRUM);
        }
    }

    for (OpponentIter iter = m_opponents.begin(); iter != m_opponents.end(); ++iter)
    {
        size_t subCount = (*iter)->getEntity()->getNumSubEntities();
        for (size_t i = 0; i < subCount; ++i)
        {
            std::string oldMat = (*iter)->getEntity()->getSubEntity(i)->getMaterialName();
            std::string newMat = oldMat.substr(0, oldMat.size()-3);
            (*iter)->getEntity()->getSubEntity(i)->setMaterialName(newMat);
        }
    }
}

void Map::changeToNightMaterials()
{
    m_city->setMaterialName(MAT_CITY_PP);
    m_ground->setMaterialName(MAT_GROUND_PP);

    for (UpgradeIter iter = m_upgrades.begin(); iter != m_upgrades.end(); ++iter)
    {
        if ((*iter)->getType() == GameObject::FuelUpgrade)
        {

            (*iter)->setMaterialName(MAT_OILDRUM_PP);
        }
    }

    for (OpponentIter iter = m_opponents.begin(); iter != m_opponents.end(); ++iter)
    {
        size_t subCount = (*iter)->getEntity()->getNumSubEntities();
        for (size_t i = 0; i < subCount; ++i)
        {
            std::string oldMat = (*iter)->getEntity()->getSubEntity(i)->getMaterialName();
            std::string newMat = oldMat + "-PP";
            (*iter)->getEntity()->getSubEntity(i)->setMaterialName(newMat);
        }
    }
}

size_t Map::getNumOpponents() const
{
    return m_opponents.size();
}

const btVector4 Map::getStartPos(int playerId)
{
    return m_startPositions[playerId];
}
