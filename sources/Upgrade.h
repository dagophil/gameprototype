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

    /**
     * @brief getter for m_type
     * @return
     */
    ObjectType getType();

    /**
     * @brief update method, called every frame
     * @param timestep
     */
    void update(const float & timestep);

    /**
     * @brief y value after respawn
     */
    float m_respawnY;

    /**
     * @brief time to respawn
     */
    float m_respawnTime;

private:

    ObjectType m_type;
    bool m_hidden;
    float m_hiddenTime;

};

#endif /* UPGRADE_H_ */
