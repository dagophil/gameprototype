/*
 * DebugDrawer.h
 *
 */

#ifndef DEBUGDRAWER_H_
#define DEBUGDRAWER_H_


#include <btBulletCollisionCommon.h>
#include <OGRE/OgreCommon.h>
#include <vector>

#include "TopManager.h"
#include "GraphicManager.h"

/**
 * @class DebugDrawer
 * @brief Draws bounding boxes
 * Used basically for debugging purpose.
 * Normally not displayed in the game.
 */
class DebugDrawer : public btIDebugDraw
{
public:
  DebugDrawer();
  virtual ~DebugDrawer();
/**
 * @brief function to draw a line between two points
 * @param from start position
 * @param to	end position
 * @param color	color (rgb value)
 */
  virtual void drawLine(const btVector3 &from, const btVector3 &to, const btVector3 &color);
  virtual void drawContactPoint(const btVector3&, const btVector3&, btScalar, int, const btVector3&){}
  virtual void reportErrorWarning(const char*){}
  virtual void draw3dText(const btVector3&, const char*){}
  virtual void setDebugMode(int){}
  virtual int getDebugMode() const {return 2; } //(1<<13)-1;}
  void resetLines();
private:
  std::vector<Ogre::SceneNode*> m_lines;
};

#endif /* DEBUGDRAWER_H_ */
