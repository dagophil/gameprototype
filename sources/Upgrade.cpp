/*
 * FuelUpgrade.cpp
 *
 */

#include "TopManager.h"
#include "Player.h"
#include "Vehicle.h"
#include "Upgrade.h"

Upgrade::Upgrade(const std::string & MeshName, const ObjectType & type)
    : GameMapObject(MeshName, false, true)
{
    m_type = type;
}

void Upgrade::CollideWith(const ObjectType & type)
{
    this->translate(0.f, -5.f, 0.f);

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

GameObject::ObjectType Upgrade::getType()
{
    return m_type;
}
