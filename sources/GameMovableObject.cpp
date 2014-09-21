#include "GameMovableObject.h"

#include <vector>
#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>

#include <BulletCollision/Gimpact/btGImpactShape.h>

#include "MotionState.h"
#include "TopManager.h"
#include "PhysicsManager.h"
#include "GraphicManager.h"
#include "MeshStrider.h"
#include "MotionState.h"


GameMovableObject::GameMovableObject(const std::string& MeshName, const float&Mass)
{
    m_Entity = TopManager::Instance()->getGraphicManager()->getSceneManager()->createEntity(MeshName);
    m_SceneNode = TopManager::Instance()->getGraphicManager()->getSceneManager()->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(0,0,0));
    m_Entity->getMesh()->setAutoBuildEdgeLists(true);
    m_Entity->setCastShadows(true);
    m_SceneNode->attachObject(m_Entity);

    Ogre::MeshPtr MeshPtr = Ogre::Singleton<Ogre::MeshManager>::getSingletonPtr()->load(MeshName, "Map");  //TODO gedanken zu resource-groups machen !
    MeshStrider* Strider = new MeshStrider(MeshPtr.get());
    btCollisionShape* CollisionShape = new btBvhTriangleMeshShape(Strider,true,true);
    btTransform Transform;
    Transform.setIdentity();
    Transform.setOrigin(btVector3(0,0,0));
    btScalar mass(Mass);
    btVector3 localInertia(0,0,0);
    btVector3 AabbMin;
    btVector3 AabbMax;
    CollisionShape->getAabb(Transform,AabbMin,AabbMax);
    btCollisionShape* BoxShape = new btBoxShape(AabbMax);
    BoxShape->calculateLocalInertia(mass,localInertia);
    MotionState *motionState = new MotionState(Transform, m_SceneNode);
    btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,motionState,BoxShape,localInertia);
    btRigidBody *body = new btRigidBody(rbInfo);
    TopManager::Instance()->getPhysicsManager()->getDynamicsWorld()->addRigidBody(body);
    delete CollisionShape;

    setRigidBody(body);
    setSceneNode(m_SceneNode);
    body->setUserPointer(this);
    setEntity(m_Entity);
}
