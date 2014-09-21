/*
 * MotionState.cpp
 *
 */

#include "MotionState.h"

MotionState::MotionState(const btTransform & initialpos, Ogre::SceneNode* node)
{
    mVisibleobj = node;
    mPos1 = initialpos;
}

MotionState::~MotionState() {}

void MotionState::setNode(Ogre::SceneNode* node)
{
    mVisibleobj = node;
}

void MotionState::getWorldTransform(btTransform & worldTrans) const
{
    Ogre::Vector3 Position = mVisibleobj->getPosition();
    Ogre::Quaternion Orientation = mVisibleobj->getOrientation();
    worldTrans.setOrigin(btVector3(Position.x,Position.y,Position.z));
    worldTrans.setRotation(btQuaternion(Orientation.x,Orientation.y,Orientation.z,Orientation.w));
}

void MotionState::setWorldTransform(const btTransform & worldTrans)
{
    if(NULL == mVisibleobj)
        return;
    btQuaternion rot = worldTrans.getRotation();
    mVisibleobj->setOrientation(rot.w(), rot.x(), rot.y(), rot.z());
    btVector3 pos = worldTrans.getOrigin();
    mVisibleobj->setPosition(pos.x(), pos.y(), pos.z());
}
