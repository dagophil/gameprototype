#ifndef MOVABLEOBJECT_H_
#define MOVABLEOBJECT_H_

#include "GameObject.h"

#include <BulletDynamics/Dynamics/btRigidBody.h>
#include <string>

/**
 *
 * @class GameMovableObject
 * @brief abstract class for movable objects
 *
 */
class GameMovableObject : public GameObject
{
public:
  GameMovableObject(){}

  /**
   * @brief constructor
   * @param name name of mesh
   * @param mass mass of object
   *
   */
  GameMovableObject(const std::string&name, const float&mass);
  ~GameMovableObject(){}

  /**
   * @brief getter for object type
   * @return
   */
  virtual ObjectType getType(){return AbstractObject; }

  /**
   * @brief handles collsions
   * @param type type of second object in collision
   */
  virtual void CollideWith(const ObjectType&type){}

  /**
   * @brief not used
   */
  virtual void ShowYourself(){}

  /**
   * @brief animation for collision
   */
  virtual void PlayCollisionAnimation(){}
private:
};

#endif
