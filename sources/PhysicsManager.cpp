/*
 * PhysicsManager.cpp
 *
 */

#include "PhysicsManager.h"

#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>
#include <BulletCollision/Gimpact/btGImpactCollisionAlgorithm.h>
#include <iostream>

PhysicsManager::PhysicsManager()
{
    m_CollisionConfiguration = new btDefaultCollisionConfiguration();
    m_Dispatcher = new  btCollisionDispatcher(m_CollisionConfiguration);
    m_Broadphase = new btDbvtBroadphase();
    btSequentialImpulseConstraintSolver* sol = new btSequentialImpulseConstraintSolver;
    m_ConstraintSolver = sol;
    m_DynamicsWorld = new btDiscreteDynamicsWorld(m_Dispatcher,m_Broadphase,m_ConstraintSolver,m_CollisionConfiguration);
    m_DynamicsWorld->setGravity(btVector3(0, -10, 0));
}

btDiscreteDynamicsWorld* PhysicsManager::getDynamicsWorld()
{
    return m_DynamicsWorld;
}

btBroadphaseInterface* PhysicsManager::getBroadphase()
{
    return m_Broadphase;
}

btDispatcher* PhysicsManager::getDispatcher()
{
    return m_Dispatcher;
}

btConstraintSolver* PhysicsManager::getConstraintSolver()
{
    return m_ConstraintSolver;
}

btCollisionConfiguration* PhysicsManager::getCollisionConfiguration()
{
    return m_CollisionConfiguration;
}
