/*
 * Keyboard.cpp
 *
 */

#include "Keyboard.h"
#include "AStar.h"
#include "Graph.h"
#include "Vehicle.h"

enum {THROTTLE, BRAKE, STEER_LEFT, STEER_RIGHT, REVERSE, RESET, AUTOMATIC};

Keyboard* Keyboard::m_Instance = 0;

Keyboard* Keyboard::Instance()
{
  if(m_Instance == 0)
    m_Instance = new Keyboard();
  return m_Instance;
}

Keyboard::Keyboard()
{
  m_Instance = this;

  m_pInputManager = InputManager::Instance()->getOIS();
  m_pKeyboard = static_cast<OIS::Keyboard*>(m_pInputManager->createInputObject(OIS::OISKeyboard, true));
  m_pKeyboard->setEventCallback(this);
  m_pPlayerKeys = new OIS::KeyCode[6];
}

void Keyboard::init()
{
  m_pPlayer = TopManager::Instance()->getPlayer();
  m_pVehicle = m_pPlayer->getVehicle();
  m_pPlayerKeys[THROTTLE] = OIS::KC_UP;
  m_pPlayerKeys[BRAKE] = OIS::KC_DOWN;
  m_pPlayerKeys[STEER_LEFT] = OIS::KC_LEFT;
  m_pPlayerKeys[STEER_RIGHT] = OIS::KC_RIGHT;

  m_pPlayerKeys[REVERSE] = OIS::KC_R;
  m_pPlayerKeys[RESET] = OIS::KC_RETURN;
  m_pPlayerKeys[AUTOMATIC] = OIS::KC_A;
}

Keyboard::~Keyboard()
{
  delete m_pPlayerKeys;
}

void Keyboard::capture()
{
  m_pKeyboard->capture();
}

bool Keyboard::keyPressed(const OIS::KeyEvent&arg)
{
  if(arg.key == OIS::KC_ESCAPE)
  {
    TopManager::Instance()->getGraphicManager()->setShutdown(true);
    return false;
  }
  if(arg.key == m_pPlayerKeys[THROTTLE])
  {
    m_pVehicle->setThrottle(true);
    return true;
  }
  if(arg.key == m_pPlayerKeys[BRAKE])
  {
    m_pVehicle->setBrake(true);
    return true;
  }
  if(arg.key == m_pPlayerKeys[STEER_LEFT])
  {
    m_pVehicle->setSteering(-1.f);
    return true;
  }
  if(arg.key == m_pPlayerKeys[STEER_RIGHT])
  {
    m_pVehicle->setSteering(1.f);
    return true;
  }
  if(arg.key == m_pPlayerKeys[RESET])
  {
    m_pVehicle->resetOrientation();
    return true;
  }
  if(arg.key == m_pPlayerKeys[REVERSE])
  {
    m_pVehicle->setReverse(true);
    return true;
  }

  // Drive automatically
  if(arg.key == OIS::KC_A)
  {
    std::cout << std::endl;
    std::cout << "AUTOMATIC" << std::endl;
    std::cout << std::endl;

    Ogre::Vector3 position = TopManager::Instance()->getPlayer()->getVehicle()->getSceneNode()->getPosition();

    Graph* graph = TopManager::Instance()->getGraph();

    std::cout << "nodes.size() from keyboard :  " << graph->getNodes().size() << std::endl;

    position.y = 0;
    position = position /2;
    std::cout << std::endl;
    std::cout << position << std::endl;
    std::cout << std:: endl;

    Graph::Node* pos(graph->getNearestNode(position));
    std::vector<Graph::Node*> nodes = graph->getNodes();
    Graph::Node* goal = nodes[0];

    AStar* astar = new AStar(graph, pos, goal);

    astar->findPath();

	std::vector<Graph::Node*> path;

	path = astar->getPath();
    return true;
  }

  // Lighting (day / night)
  if (arg.key == OIS::KC_L)
  {
      TopManager::Instance()->getGraphicManager()->toggleDayNight();
  }

  return true;
}

bool Keyboard::keyReleased(const OIS::KeyEvent&arg)
{
  if(arg.key == m_pPlayerKeys[STEER_LEFT] || arg.key == m_pPlayerKeys[STEER_RIGHT])
  {
    m_pVehicle->setSteering(0.f);
    return true;
  }
  if(arg.key == m_pPlayerKeys[BRAKE])
  {
    m_pVehicle->setBrake(false);
    return true;
  }
  if(arg.key == m_pPlayerKeys[THROTTLE])
  {
    m_pVehicle->setThrottle(false);
    return true;
  }
  if(arg.key == m_pPlayerKeys[REVERSE])
  {
    m_pVehicle->setReverse(false);
    return true;
  }

  return true;
}
