/*
 * FuelUpgrade.cpp
 *
 */

#include "FuelUpgrade.h"

FuelUpgrade::FuelUpgrade(const std::string & MeshName)
    : GameMapObject(MeshName)
{

}

void FuelUpgrade::CollideWith(const ObjectType & type)
{
    this->translate(0.f, 5.f, 0.f);
    std::cout << type << std::endl;
}
