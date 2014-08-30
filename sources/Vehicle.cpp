#include "Vehicle.h"
#include "Map.h"

float max_throttle = 500.f; //this should be engine/velocity dependent
float max_brake = 50.f;

float max_steering = 0.3f;
float wheelRadius = 0.5f;
float wheelFriction = 5; //BT_LARGE_FLOAT;
float suspensionStiffness = 200.f;
float suspensionDamping = 2.3f;
float suspensionCompression = 4.4f;
float rollInfluence = 0.1f; //1.0f;
float maxSuspensionForce = 4500.f;

btScalar suspensionRestLength(.4f);

btVector3 wheelDirectionCS0(0,-1,0);
btVector3 wheelAxleCS(-1,0,0);

btVector3 hit_impulse(0.f,5000.f,0.f);

Vehicle::Vehicle(const std::string&MeshName, const float&Mass, Player* Player) :
  m_brake(false),
  m_throttle(false),
  m_reverse(false),
  m_steering(0.f),
  m_wheelRotation(0.f),
  m_fuel(100)
{
  Ogre::Entity* Entity = TopManager::Instance()->getGraphicManager()->getSceneManager()->createEntity(MeshName);
  Ogre::SceneNode* Node = TopManager::Instance()->getGraphicManager()->getSceneManager()->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(0,0,0));
  Ogre::SceneNode* GrafikNode = Node->createChildSceneNode(Ogre::Vector3(0.f,0.f,0.f)); //-2.1f,0.f));
  Entity->setCastShadows(true);
  GrafikNode->attachObject(Entity);

  Ogre::SceneNode* HeadlightNode = Node->createChildSceneNode(Ogre::Vector3(0.5f, 2.f, 0.f));
  HeadlightNode->pitch(Ogre::Degree(190));
  HeadlightNode->yaw(Ogre::Degree(-10));
  Ogre::Light* headlight1 = TopManager::Instance()->getGraphicManager()->getSceneManager()->getLight("Headlight1");
  HeadlightNode->attachObject(headlight1);

  Ogre::SceneNode* Headlight2Node = Node->createChildSceneNode(Ogre::Vector3(-0.5f, 2.f, 0.f));
  Headlight2Node->pitch(Ogre::Degree(190));
  Headlight2Node->yaw(Ogre::Degree(10));
  Ogre::Light* headlight2 = TopManager::Instance()->getGraphicManager()->getSceneManager()->getLight("Headlight2");
  Headlight2Node->attachObject(headlight2);

  Ogre::Entity* wheel0 = TopManager::Instance()->getGraphicManager()->getSceneManager()->createEntity("wheel.mesh");
  m_wheelNode[0] = GrafikNode->createChildSceneNode(Ogre::Vector3(1.24, 0.49,-2.1));
  m_wheelNode[0]->attachObject(wheel0);

  Ogre::Entity* wheel1 = TopManager::Instance()->getGraphicManager()->getSceneManager()->createEntity("wheel.mesh");
  m_wheelNode[1] = GrafikNode->createChildSceneNode(Ogre::Vector3(-1.24, 0.49,-2.1));
  m_wheelNode[1]->attachObject(wheel1);

  Ogre::Entity* wheel2 = TopManager::Instance()->getGraphicManager()->getSceneManager()->createEntity("wheel.mesh");
  m_wheelNode[2] = GrafikNode->createChildSceneNode(Ogre::Vector3(-1.24, 0.49,1.6));
  m_wheelNode[2]->attachObject(wheel2);

  Ogre::Entity* wheel3 = TopManager::Instance()->getGraphicManager()->getSceneManager()->createEntity("wheel.mesh");
  m_wheelNode[3] = GrafikNode->createChildSceneNode(Ogre::Vector3(1.24, 0.49, 1.6));
  m_wheelNode[3]->attachObject(wheel3);


  Ogre::MeshPtr MeshPtr = Ogre::Singleton<Ogre::MeshManager>::getSingletonPtr()->load(MeshName, "Map");  //TODO gedanken zu resource-groups machen !
  MeshStrider* Strider = new MeshStrider(MeshPtr.get());
  btCollisionShape* TriangleMeshShape = new btBvhTriangleMeshShape(Strider,true,true);
  btVector3 Aabbmin;
  btVector3 Aabbmax;
  btTransform Transform;
  Transform.setIdentity();
  Transform.setOrigin(btVector3(0,0,0));
  TriangleMeshShape->getAabb(Transform,Aabbmin,Aabbmax);
  btVector3 Aabb = 0.5 * (Aabbmax - Aabbmin);
  m_ChassisShape = new btBoxShape(Aabb);
  btVector3 offset = -0.5 * (Aabbmax + Aabbmin);
  GrafikNode->translate(offset.getX(),offset.getY(),offset.getZ());


  btScalar mass(Mass);
  btVector3 localInertia(0,0,0);
  m_ChassisShape->calculateLocalInertia(mass,localInertia);
  MotionState* motionState = new MotionState(Transform, Node);
  btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,motionState,m_ChassisShape,localInertia);
  btRigidBody* Chassis = new btRigidBody(rbInfo);

  btTransform CenterOfMassTransform = Chassis->getCenterOfMassTransform();
  btVector3 CoMOrigin = CenterOfMassTransform.getOrigin();
  CoMOrigin.setY(CoMOrigin.getY() - (Aabb.getY() * 0.75));
  CenterOfMassTransform.setOrigin(CoMOrigin);
  Chassis->setCenterOfMassTransform(CenterOfMassTransform);

  m_Player = Player;
  setRigidBody(Chassis);
  setSceneNode(Node);
  Chassis->setUserPointer(this);

  // Set start position
  int PlayerId = Player->getId();
  btVector4 StartPos = TopManager::Instance()->getMap()->getStartPos(PlayerId);
  translate(StartPos.getX(),StartPos.getY(),StartPos.getZ());
  yaw(Ogre::Degree(StartPos.getW()));


  m_VehicleRayCaster = new btDefaultVehicleRaycaster(TopManager::Instance()->getPhysicsManager()->getDynamicsWorld());
  m_RaycastVehicle = new btRaycastVehicle(m_Tuning,Chassis,m_VehicleRayCaster);


  Chassis->setActivationState(DISABLE_DEACTIVATION);
  TopManager::Instance()->getPhysicsManager()->getDynamicsWorld()->addRigidBody(Chassis);
  TopManager::Instance()->getPhysicsManager()->getDynamicsWorld()->addAction(m_RaycastVehicle);


  bool isFrontWheel = false;
  //wheelRadius = 0.3*Aabbmax.getY();
  btVector3 connectionPointCS0(-Aabb.getX(),-0.5 * Aabb.getY(), -Aabb.getZ());
  //btVector3 connectionPointCS0(0,-0.5*Aabbmax.getY(), 0);
  //btVector3 connectionPointCS0(-1.24,-1.756, -2.35);
  m_RaycastVehicle->addWheel(connectionPointCS0,wheelDirectionCS0,wheelAxleCS,suspensionRestLength,wheelRadius,m_Tuning,isFrontWheel);

  connectionPointCS0 = btVector3(Aabb.getX(),-0.5 * Aabb.getY(), -Aabb.getZ());
  //connectionPointCS0= btVector3(Aabbmax.getX(),-0.5*Aabbmax.getY(), 0);
  //connectionPointCS0= btVector3(+1.24,-1.756, -2.35);
  m_RaycastVehicle->addWheel(connectionPointCS0,wheelDirectionCS0,wheelAxleCS,suspensionRestLength,wheelRadius,m_Tuning,isFrontWheel);

  isFrontWheel = true;

  connectionPointCS0 = btVector3(-Aabb.getX(),-0.5 * Aabb.getY(), Aabb.getZ());
  m_RaycastVehicle->addWheel(connectionPointCS0,wheelDirectionCS0,wheelAxleCS,suspensionRestLength,wheelRadius,m_Tuning,isFrontWheel);

  connectionPointCS0 = btVector3(Aabb.getX(),-0.5 * Aabb.getY(), Aabb.getZ());
  m_RaycastVehicle->addWheel(connectionPointCS0,wheelDirectionCS0,wheelAxleCS,suspensionRestLength,wheelRadius,m_Tuning,isFrontWheel);

  for (int i = 0; i < m_RaycastVehicle->getNumWheels(); i++)
  {
    btWheelInfo&wheel = m_RaycastVehicle->getWheelInfo(i);
    wheel.m_suspensionStiffness = suspensionStiffness;
    wheel.m_wheelsDampingRelaxation = suspensionDamping;
    wheel.m_wheelsDampingCompression = suspensionCompression;
    wheel.m_frictionSlip = wheelFriction;
    wheel.m_rollInfluence = rollInfluence;
    wheel.m_maxSuspensionForce = maxSuspensionForce;
  }

  delete Strider;

}
Vehicle::~Vehicle(){}


void Vehicle::setBrake(bool brake)
{
  m_brake = brake;
}

void Vehicle::setThrottle(bool throttle)
{
  m_throttle = throttle;
}

void Vehicle::setSteering(float steering)
{
  m_steering = -steering * max_steering;
}

void Vehicle::setReverse(bool reverse)
{
  m_reverse = reverse;
}

GameObject::ObjectType Vehicle::getType()
{
  return GameObject::Vehicle;
}

void Vehicle::CollideWith(const GameObject::ObjectType&type)
{
  //Hier fehlt noch was
  switch(type)
  {
    case Wall:
      break;
    case AbstractObject:
      break;
    case GameObject::Vehicle:
      break;
    default:
      break;
  }

}

void Vehicle::ShowYourself()
{
  //Hier fehlt noch was
}

void Vehicle::PlayCollisionAnimation()
{
  getRigidBody()->applyCentralImpulse(hit_impulse);
}

void Vehicle::update()
{
  float throttle = 0.f;
  float brake = 0.f;
  float kmh = m_RaycastVehicle->getCurrentSpeedKmHour();
  if (m_throttle)
  {
    if (kmh < 10.f && kmh > -20.f)
      throttle = max_throttle;
    else
    if (kmh < 25.f && kmh > -35.f)
      throttle = 0.7 * max_throttle;
    else
    if(m_steering < 0.5 * max_steering&&m_steering > -0.5 * max_steering)
    {
      if (kmh < 50.f && kmh > -75.f)
        throttle = 0.4 * max_throttle;
    }
  }
  if(m_reverse)
  {
    throttle *= -0.5f;
  }
  if (m_brake)
    brake = max_brake;
  int wheelIndex = 0;
  m_RaycastVehicle->applyEngineForce(throttle,wheelIndex);
  m_RaycastVehicle->setBrake(brake,wheelIndex);
  wheelIndex = 1;
  m_RaycastVehicle->applyEngineForce(throttle,wheelIndex);
  m_RaycastVehicle->setBrake(brake,wheelIndex);
  wheelIndex = 2;
  m_RaycastVehicle->applyEngineForce(throttle,wheelIndex);
  m_RaycastVehicle->setBrake(brake,wheelIndex);
  m_RaycastVehicle->setSteeringValue(m_steering,wheelIndex);
  wheelIndex = 3;
  m_RaycastVehicle->applyEngineForce(throttle,wheelIndex);
  m_RaycastVehicle->setBrake(brake,wheelIndex);
  m_RaycastVehicle->setSteeringValue(m_steering,wheelIndex);
  //Update Wheels:
  m_wheelRotation += 1.5f * kmh;
  while(m_wheelRotation > 360.f)
    m_wheelRotation -= 360.f;
  for (int i = 0; i < 4; i++)
  {
    m_RaycastVehicle->updateWheelTransform(i,true);
    m_wheelNode[i]->resetOrientation();
    if(m_RaycastVehicle->getWheelInfo(i).m_bIsFrontWheel)
    {
      m_wheelNode[i]->yaw(Ogre::Radian(m_steering));
    }
    m_wheelNode[i]->pitch(Ogre::Degree(m_wheelRotation));
  }
  if (kmh > 1) {
      // TODO: Find a framerate independent solution
      m_fuel -= kmh/100;
  } else if (kmh < -1) {
      m_fuel += kmh/100;
  }
}

void Vehicle::resetOrientation()
{
  getSceneNode()->translate(0.f,1.f,0.f);
  btTransform Transform;
  getRigidBody()->getMotionState()->getWorldTransform(Transform);
  btMatrix3x3 Matrix = Transform.getBasis();
  Matrix[0].setY(0.f);
  Matrix[1] = btVector3(0.f,1.f,0.f);
  Matrix[2].setY(0.f);
  Transform.setBasis(Matrix);
  getRigidBody()->setWorldTransform(Transform);
}


float Vehicle::getFuel()
{
    return m_fuel;
}

void Vehicle::fillTank()
{
    m_fuel += 20;
    if (m_fuel > 100) {
        m_fuel = 100;
    }
}
