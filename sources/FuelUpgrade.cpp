/*
 * FuelUpgrade.cpp
 *
 */

#include "TopManager.h"
#include "Player.h"
#include "Vehicle.h"
#include "FuelUpgrade.h"

FuelUpgrade::FuelUpgrade(const std::string & MeshName)
    : GameMapObject(MeshName)
{

}

void FuelUpgrade::CollideWith(const ObjectType & type)
{
    this->translate(0.f, 5.f, 0.f);
    TopManager::Instance()->getPlayer()->getVehicle()->fillTank();
}
