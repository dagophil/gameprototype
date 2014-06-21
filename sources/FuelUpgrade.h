/*
 * FuelUpgrade.h
 *
 */

#ifndef FUELUPGRADE_H_
#define FUELUPGRADE_H_

#include "GameMapObject.h"
#include <string>

/**
 * @class FuelUpgrade
 * @brief The FuelUpgrade class
 */
class FuelUpgrade : public GameMapObject
{
public:

    /**
     * @brief constructor
     * @param MeshName name of mesh
     */
    FuelUpgrade(const std::string & MeshName);

    /**
     * @brief CollideWith
     * @param type type of other object
     */
    void CollideWith(const ObjectType & type);

private:

};

#endif /* FUELUPGRADE_H_ */
