/*
 * FuelUpgrade.h
 *
 */

#ifndef UPGRADE_H_
#define UPGRADE_H_

#include "GameMapObject.h"
#include <string>

/**
 * @class Upgrade
 * @brief The Upgrade class can be used for fuel and health upgrades
 */
class Upgrade : public GameMapObject
{
public:

    /**
     * @brief constructor
     * @param MeshName name of mesh
     */
    Upgrade(const std::string & MeshName, const ObjectType & type);

    /**
     * @brief CollideWith
     * @param type type of other object
     */
    void CollideWith(const ObjectType & type);

    ObjectType getType();

private:

    ObjectType m_type;

};

#endif /* UPGRADE_H_ */
