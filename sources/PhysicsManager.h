/*
 * PhysicsManager.h
 *
 */

#ifndef PHYSICSMANAGER_H_
#define PHYSICSMANAGER_H_

#include <btBulletDynamicsCommon.h>

/**
 * @class PhysicsManager
 * @brief Manager for physics
 * This is a main connection point between the Bullet library and other classes.
 */

class PhysicsManager
{
public:
  PhysicsManager();
  /**
   * @brief getter for dynamics world
   * @return
   */
  btDiscreteDynamicsWorld*getDynamicsWorld();

  /**
   * @brief getter for broadphase
   * @return
   */
  btBroadphaseInterface*getBroadphase();

  /**
   * @brief getter for dispatcher
   * @return
   */
  btDispatcher*getDispatcher();

  /**
   * @brief getter for constraint solver
   * @return
   */
  btConstraintSolver*getConstraintSolver();

  /**
   * getter for collsion configuration
   * @return
   */
  btCollisionConfiguration*getCollisionConfiguration();
private:
  btDiscreteDynamicsWorld*  m_DynamicsWorld;
  btBroadphaseInterface*    m_Broadphase;
  btDispatcher*         m_Dispatcher;
  btConstraintSolver*     m_ConstraintSolver;
  btCollisionConfiguration* m_CollisionConfiguration;
};


#endif /* PHYSICSMANAGER_H_ */
