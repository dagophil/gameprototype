/*
 * GameMapObject.h
 *
 */

#ifndef MAPOBJECT_H_
#define MAPOBJECT_H_

#include "GameObject.h"
#include "MeshStrider.h"
#include <string>

#include <OGRE/OgreCommon.h>

/**
 * @class GameMapObject
 * @brief Class for objects in the map (static, non-movable)
 * May be used for Obstacles, Bombs, Secrets, Healpods etc.
 */

class GameMapObject : public GameObject
{
public:

  GameMapObject(){};

  /**
  * @brief contructor
  * @param mesh name of mesh
  *
  */
  GameMapObject(const std::string&mesh, const bool & contactResponse = true, const bool & rotates = false);

  ~GameMapObject();

  /**
   * @brief function to call once per frame
   */
  void update();

  /**
  * @brief getter for Object type
  * @return ObjectType
  */
  virtual GameObject::ObjectType getType();

  /**
   * @brief handles collision with other object
   * @param type of other object
   */
  virtual void CollideWith(const ObjectType&type);

  /**
   * @brief not used
   */
  virtual void ShowYourself();

  /**
   * @brief pmays animaion at collision
   *
   */
  virtual void PlayCollisionAnimation();
private:

  bool m_Rotates;

};

#endif /* MAPOBJECT_H_ */
