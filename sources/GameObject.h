#ifndef OBJECT_H_
#define OBJECT_H_

#include <OGRE/OgreRoot.h>
#include <OGRE/OgreEntity.h>
#include <btBulletDynamicsCommon.h>

/**
 *
 * @class GameObject
 * @brief Abstract class for all movable and non-movable game objects
 */

class GameObject
{
public:

  /// Define all types of the objects here
  enum ObjectType {Wall, AbstractObject, Vehicle, FuelUpgrade, HealthUpgrade};

  /**
   * @brief getter for object type
   * @return
   */
  virtual ObjectType getType() = 0;

  /**
   * handles collsion with object
   * @param type type of other object
   */
  virtual void CollideWith(const ObjectType&type) = 0;

  /**
   * @brief not used
   */
  virtual void ShowYourself() = 0;

  /**
   * @brief animation for collision
   */
  virtual void PlayCollisionAnimation() = 0;

  /**
   * @brief getter for scene node
   * @return
   */
  Ogre::SceneNode*getSceneNode();

  /**
   * @brief setter for scene node
   * @param node
   */
  void setSceneNode(Ogre::SceneNode* node);

  /**
   * @brief getter for scene node
   * @return
   */
  Ogre::Entity*getEntity();

  /**
   * @brief setter for scene node
   * @param node
   */
  void setEntity(Ogre::Entity* node);

  /**
   * @brief getter for rigid body
   * @return
   */
  btRigidBody*getRigidBody();

  /**
   * @brief setter for rigid body
   * @param body
   */
  void setRigidBody(btRigidBody* body);

  /**
   * @brief yaws object
   * @param angle
   */
  void yaw(const Ogre::Radian&angle);

  /**
   * @brief pitchs object
   * @param angle
   */
  void pitch(const Ogre::Radian&angle);

  /**
   * @brief rolls object
   * @param angle
   */
  void roll(const Ogre::Radian&angle);

  /**
   * @brief translates object
   * @param x
   * @param y
   * @param z
   */
  void translate(float x, float y, float z);

  /**
   * @brief scales object
   * @param dx
   * @param dy
   * @param dz
   */
  void scale(float dx, float dy, float dz);

  /**
   * @brief sets material name of object
   * @param name
   *
   */
  void setMaterialName(const std::string&name);

  /**
   * @brief enables or disables shadows of object
   * @param shadows
   */
  void setCastShadows(bool shadows);
protected:

  /**
   * @brief scene node of object
   */
  Ogre::SceneNode*  m_SceneNode;

  /**
   * @brief entity of object
   */
  Ogre::Entity*   m_Entity;

  /**
   * @brief rigid body of object
   */
  btRigidBody*    m_RigidBody;
};

#endif

