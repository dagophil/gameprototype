#ifndef VEHICLE_H_
#define VEHICLE_H_


/**
 *
 * @class Vehicle
 * @brief vehicle class
 *
 */
#include "TopManager.h"

#include "GameMovableObject.h"
#include "MotionState.h"
#include "MeshStrider.h"
#include "PhysicsManager.h"

#include <string>
#include <btBulletDynamicsCommon.h>
#include <string>
#include <sstream>

class Player;

/**
 *
 * @class Vehicle
 * @brief Class for a Vehicle
 * Vehicle is the class for graphical and physical representation of the players Vehicle
 * It creates the Vehicle graphics in the constructor function of the class.
 * During the update() operation it recalculates the speed of the car.
 * Since Vehicle is a movable object, it is derived from the GameMovableObject class.
 */

class Vehicle : public GameMovableObject
{
public:

  /**
   * @brief constructor
   * @param meshName
   * @param mass
   * @param player
   *
   */
  Vehicle(const std::string&meshName, const float&mass, Player* player);
  ~Vehicle();
  virtual GameObject::ObjectType getType();
  virtual void CollideWith(const GameObject::ObjectType&);
  virtual void ShowYourself();
  virtual void PlayCollisionAnimation();

  /**
   * @brief setter for brake
   * @param brake Bool for active brake
   */
  void setBrake(bool brake);

  /**
   * @brief setter for throttle
   * @param throttle Bool for acceleration
   */
  void setThrottle(bool throttle);

  /**
   * @brief setter for steering
   * @param steering Float in range -1..1 to set steering
   */
  void setSteering(float steering);

  /**
   * @brief setter for reverse gear
   * @param reverse
   */
  void setReverse(bool reverse);

  /**
   *
   * @brief Update function. Is called every frame.
   */
  void update();

  /**
   * @brief resets vehicle orientation
   */
  void resetOrientation();
private:
  bool m_brake;
  bool m_throttle;
  bool m_reverse;
  float m_steering;
  float m_wheelRotation;

  Ogre::SceneNode* m_wheelNode[4];

  /// btRaycastVehicle::btVehicleTuning - Bullet vehicle tuning (vehicle with the specified parameters)
  btRaycastVehicle::btVehicleTuning m_Tuning;
  /// btVehicleRaycaster Bullet class interface between simulation and ray-casting
  btVehicleRaycaster   *m_VehicleRayCaster;
  /// btRaycastVehicle Bullet class for Vehicle 
  btRaycastVehicle   *m_RaycastVehicle;
  /// btCollisionShape class provides an interface for collision shapes that can be shared among btCollisionObjects.
  /// Collision shape for vehicle Chassis
  btCollisionShape   *m_ChassisShape;
  /// Collision shape for the Wheel
  btCollisionShape   *m_WheelShape;
  /// Reference to the player connected to the Vehicle
  Player *m_Player;
};

#endif
