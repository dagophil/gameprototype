/*
 * MapObject.cpp
 *
 */
#include "GameMapObject.h"
#include <string>

#include <OGRE/OgreCommon.h>
#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>
//#include <BulletCollision/Gimpact/btGImpactShape.h>
#include <BulletCollision/CollisionDispatch/btGhostObject.h>

#include "MeshStrider.h"
#include "TopManager.h"
#include "GraphicManager.h"
#include "PhysicsManager.h"
#include "MotionState.h"


GameMapObject::GameMapObject(const std::string & MeshName, const bool & contactResponse)
{
  m_Entity = TopManager::Instance()->getGraphicManager()->getSceneManager()->createEntity(MeshName);
  m_SceneNode = TopManager::Instance()->getGraphicManager()->getSceneManager()->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(0,0,0));
  m_Entity->setCastShadows(true);
  m_SceneNode->attachObject(m_Entity);

  Ogre::MeshPtr MeshPtr = Ogre::Singleton<Ogre::MeshManager>::getSingletonPtr()->load(MeshName, "Map");
  MeshStrider* Strider = new MeshStrider(MeshPtr.get());
  //btCollisionShape* CollisionShape = new btGImpactMeshShape (Strider);
  btCollisionShape* CollisionShape = new btBvhTriangleMeshShape(Strider,true,true);
  btTransform Transform;
  Transform.setIdentity();
  Transform.setOrigin(btVector3(0,0,0));
  btScalar mass(0.);
  btVector3 localInertia(0,0,0);
  MotionState* motionState = new MotionState(Transform, m_SceneNode);
  btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,motionState,CollisionShape,localInertia);
  btRigidBody* body = new btRigidBody(rbInfo);
  if(!contactResponse) {
      body->setCollisionFlags(body->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);
  }
  TopManager::Instance()->getPhysicsManager()->getDynamicsWorld()->addRigidBody(body);

  setRigidBody(body);
  setSceneNode(m_SceneNode);
  body->setUserPointer(this);
}

GameMapObject::~GameMapObject()
{
//std::cout<<"wall stirbt"<<std::endl;
}


GameObject::ObjectType GameMapObject::getType()
{
  return Wall;
}

void GameMapObject::CollideWith(const ObjectType&){}

void GameMapObject::ShowYourself(){}

void GameMapObject::PlayCollisionAnimation(){}
