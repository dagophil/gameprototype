/*
 * MotionState.h
 *
 */

#ifndef MOTIONSTATE_H_
#define MOTIONSTATE_H_

#include <LinearMath/btMotionState.h>
#include <OGRE/Ogre.h>

/**
 * @class MotionState
 * @brief Motionstate for connection between Ogre and bullet
 */
class MotionState : public btMotionState
{

public:

    /**
     * @brief constructor
     * @param initialpos	not used
     * @param node			scene node of moved object
     */
    MotionState(const btTransform & initialpos, Ogre::SceneNode* node);

    virtual ~MotionState();

    /**
     * @brief not used
     * @param node
     */
    void setNode(Ogre::SceneNode* node);

    /**
     * @brief getter for world transform
     * @param worldTrans
     */
    virtual void getWorldTransform(btTransform& worldTrans) const;

    /**
     * @brief setter for world transform
     * @param worldTrans
     */
    virtual void setWorldTransform(const btTransform& worldTrans);

protected:

    /**
     * @brief scene node of moving object
     */
    Ogre::SceneNode* mVisibleobj;

    /**
     * @brief not used (initial position)
     */
    btTransform mPos1;

};

#endif /* MOTIONSTATE_H_ */
