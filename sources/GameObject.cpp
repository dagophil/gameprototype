#include "GameObject.h"

#include <OGRE/OgreRoot.h>
#include <OGRE/OgreEntity.h>
#include <btBulletDynamicsCommon.h>

#include <iostream>


void GameObject::setSceneNode(Ogre::SceneNode* SceneNode)
{
    m_SceneNode = SceneNode;
}

Ogre::SceneNode* GameObject::getSceneNode()
{
    return m_SceneNode;
}

void GameObject::setEntity(Ogre::Entity* Entity)
{
    m_Entity = Entity;
}

Ogre::Entity* GameObject::getEntity()
{
    return m_Entity;
}

void GameObject::setRigidBody(btRigidBody* RigidBody)
{
    m_RigidBody = RigidBody;
}

btRigidBody* GameObject::getRigidBody()
{
    return m_RigidBody;
}


void GameObject::yaw(const Ogre::Radian& angle)
{
    m_SceneNode->yaw(angle);
    btTransform Transform;
    m_RigidBody->getMotionState()->getWorldTransform(Transform);
    m_RigidBody->setWorldTransform(Transform);
}

void GameObject::pitch(const Ogre::Radian& angle)
{
    m_SceneNode->pitch(angle);
    btTransform Transform;
    m_RigidBody->getMotionState()->getWorldTransform(Transform);
    m_RigidBody->setWorldTransform(Transform);
}

void GameObject::roll(const Ogre::Radian& angle)
{
    m_SceneNode->roll(angle);
    btTransform Transform;
    m_RigidBody->getMotionState()->getWorldTransform(Transform);
    m_RigidBody->setWorldTransform(Transform);
}

void GameObject::translate(float x, float y, float z)
{
    m_SceneNode->translate(x, y, z);
    btTransform Transform;
    m_RigidBody->getMotionState()->getWorldTransform(Transform);
    m_RigidBody->setWorldTransform(Transform);
}

void GameObject::scale(float x, float y, float z)
{
    m_SceneNode->scale(x, y, z);
    btVector3 Scale = m_RigidBody->getCollisionShape()->getLocalScaling();
    Scale.setX(Scale.getX() * x);
    Scale.setY(Scale.getY() * y);
    Scale.setZ(Scale.getZ() * z);
    m_RigidBody->getCollisionShape()->setLocalScaling(Scale);
}

const Ogre::Vector3 & GameObject::getPosition()
{
    return m_SceneNode->getPosition();
}

void GameObject::setPosition(const Ogre::Vector3 & position)
{
    m_SceneNode->setPosition(position);
}

const float & GameObject::getX()
{
    return m_SceneNode->getPosition().x;
}

void GameObject::setX(const float & x)
{
    this->m_SceneNode->setPosition(x, this->getPosition().y, this->getPosition().z);
}

const float & GameObject::getY()
{
    return m_SceneNode->getPosition().y;
}

void GameObject::setY(const float & y)
{
    this->m_SceneNode->setPosition(this->getPosition().x, y, this->getPosition().z);
}

const float & GameObject::getZ()
{
    return m_SceneNode->getPosition().z;
}

void GameObject::setZ(const float & z)
{
    this->m_SceneNode->setPosition(this->getPosition().x, this->getPosition().y, z);
}

void GameObject::setMaterialName(const std::string& Name)
{
    getEntity()->setMaterialName(Name);
}

void GameObject::setCastShadows(bool CastShadows)
{
    getEntity()->setCastShadows(CastShadows);
}
