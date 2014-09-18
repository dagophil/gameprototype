/*
 * FuelUpgrade.cpp
 *
 */

#include "TopManager.h"
#include "Player.h"
#include "Vehicle.h"
#include "Upgrade.h"

Upgrade::Upgrade(const std::string & MeshName, const ObjectType & type)
    : GameMapObject(MeshName, false, true, type),
      m_respawnY(1.5),
      m_respawnTime(5),
      m_hidden(false),
      m_hiddenTime(-1)
{

}

void Upgrade::CollideWith(const ObjectType & type)
{
    this->setY(-50);
    m_hidden = true;
    m_hiddenTime = 0;

    switch (m_type) {
    case FuelUpgrade:
        TopManager::Instance()->getPlayer()->getVehicle()->fillTank();
        break;
    case HealthUpgrade:
        TopManager::Instance()->getPlayer()->addLive();
        break;
    default:
        break;
    }
}

void Upgrade::update(const float & timestep)
{
    GameMapObject::update(timestep);
    if (m_hidden)
    {
        m_hiddenTime += timestep;
        if (m_hiddenTime > m_respawnTime)
        {
            m_hidden = false;
            m_hiddenTime = -1;
            this->setY(m_respawnY);
        }
    }
}
