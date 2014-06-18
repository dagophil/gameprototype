/*
 * DebugDrawer.cpp
 *
 */

#include "DebugDrawer.h"

DebugDrawer::DebugDrawer()
{
  // TODO Auto-generated constructor stub

}

DebugDrawer::~DebugDrawer()
{
  // TODO Auto-generated destructor stub
}

void DebugDrawer::resetLines()
{
  for(unsigned int i = 0; i < m_lines.size(); i++)
  {
    m_lines[i]->detachAllObjects();
    delete m_lines[i];
  }
  m_lines.clear();
}

void DebugDrawer::drawLine(const btVector3 &from, const btVector3 &to, const btVector3 &color)
{
  Ogre::SceneManager * mSceneMgr = TopManager::Instance()->getGraphicManager()->getSceneManager();
  Ogre::ManualObject* myManualObject =  mSceneMgr->createManualObject();
  Ogre::SceneNode* myManualObjectNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
/*
  Ogre::MaterialPtr myManualObjectMaterial = Ogre::MaterialManager::getSingleton().create("manual1Material","debugger");
  myManualObjectMaterial->setReceiveShadows(false);
  myManualObjectMaterial->getTechnique(0)->setLightingEnabled(true);
  myManualObjectMaterial->getTechnique(0)->getPass(0)->setDiffuse(0,0,1,0);
  myManualObjectMaterial->getTechnique(0)->getPass(0)->setAmbient(0,0,1);
  myManualObjectMaterial->getTechnique(0)->getPass(0)->setSelfIllumination(0,0,1);
  */
//myManualObjectMaterial->dispose();  // dispose pointer, not the material


  myManualObject->begin("RED", Ogre::RenderOperation::OT_LINE_LIST);
  myManualObject->position(from.getX(), from.getY(), from.getZ());
  myManualObject->position(to.getX(), to.getY(), to.getZ());
  // etc

  myManualObject->end();

  myManualObjectNode->attachObject(myManualObject);
  m_lines.push_back(myManualObjectNode);
}
