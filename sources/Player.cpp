#include "Player.h"

#include "Vehicle.h"

Player::Player(int playerId) : m_playerId(playerId),m_lives(5)
{
    m_joystick = true;
    srand(time(NULL) );
    m_vehicle = new Vehicle("car.mesh",400.f,this);
    //m_vehicle->translate(10*playerId,10*playerId,10*playerId);
    m_timer = new Ogre::Timer();
    m_automatic = false;

    try
    {
        m_input = new PlayerInput;
        m_input->init(playerId,this);
    }
    catch(...) {}

    createPlayerCam();
    createViewport();
}

Vehicle* Player::getVehicle()
{
    return m_vehicle;
}

void Player::update(const float & timestep)
{
    if(m_joystick)
    {
        m_input->capture();
    }

    if(m_automatic) {
        // Beschleunigen.
        if (m_vehicle->getKmh() < 20) {
            m_vehicle->setThrottle(true);
        } else {
            m_vehicle->setThrottle(false);
        }

        std::cout << std::endl;

        Ogre::Vector3 forwardVector = m_vehicle->getForwardVector();
        std::cout << "Forwards: " << forwardVector << std::endl;

        Ogre::Vector3 position = m_vehicle->getSceneNode()->getPosition() / 2;
        position.y = 0;
        std::cout << "Current position: " << position << std::endl;

        float positionAngle = Ogre::Math::ATan(forwardVector.z / forwardVector.x).valueRadians();
        if (forwardVector.x < 0) {
            positionAngle += Ogre::Math::PI;
        }
        while (positionAngle > Ogre::Math::PI) {
            positionAngle -= 2*Ogre::Math::PI;
        }
        while (positionAngle < -Ogre::Math::PI) {
            positionAngle += 2*Ogre::Math::PI;
        }
        std::cout << "Position angle: " << positionAngle << std::endl;

        Graph::Node current_node = m_path.back();
        std::cout << "Current node: " << current_node << std::endl;

        Ogre::Vector3 delta = current_node - position;
        std::cout << "Delta vector: " << delta << std::endl;

        float deltaAngle = Ogre::Math::ATan(delta.z / delta.x).valueRadians();
        if (delta.x < 0) {
            deltaAngle += Ogre::Math::PI;
        }
        deltaAngle -= Ogre::Math::PI/2;
        deltaAngle -= positionAngle;
        while (deltaAngle > Ogre::Math::PI) {
            deltaAngle -= 2*Ogre::Math::PI;
        }
        while (deltaAngle < -Ogre::Math::PI) {
            deltaAngle += 2*Ogre::Math::PI;
        }
        std::cout << "Delta angle (corrected): " << deltaAngle << std::endl;

        // Rechts / Links bestimmen.
        if (deltaAngle > 10 * Ogre::Math::PI / 180) {
            std::cout << "Rechts!" << std::endl;
            m_vehicle->setSteering(1.f);
        } else if (deltaAngle < 10 * Ogre::Math::PI / 180) {
            std::cout << "Links!" << std::endl;
            m_vehicle->setSteering(-1.f);
        } else {
            m_vehicle->setSteering(0.f);
        }

        if (delta.length() < 5) {
            m_path.pop_back();
            std::cout << "Knoten " << current_node << " entfernt." << std::endl;
        }

        if (delta.length() > 15) {
            findNewPath();
        }
    }

    m_vehicle->update(timestep);
    TopManager::Instance()->getOverlayManager()->update();
}

void Player::disableJoystick()
{
    m_joystick = false;
}

void Player::createViewport()
{
    Ogre::RenderWindow* window = TopManager::Instance()->getGraphicManager()->getRenderWindow();
    m_playerVp =  window->addViewport(m_playerCam,1,0,0,1,1);
    m_playerVp->setOverlaysEnabled(true);
    m_playerCam->setAspectRatio(Ogre::Real(m_playerVp->getActualWidth()) / Ogre::Real(m_playerVp->getActualHeight()));
}

void Player::addLive()
{
    m_lives++;
}

void Player::removeLive()
{
    m_lives--;
    m_vehicle->PlayCollisionAnimation();
    if (m_lives <= 0)
    {
        TopManager::Instance()->game_over(false);
    }
    //TopManager::Instance()->getOverlayManager()->update();
}

int Player::getLives()
{
    return m_lives;
}

void Player::createPlayerCam()
{
    std::stringstream playerstringstream;
    playerstringstream << "playerCam" << m_playerId;
    std::string playerstring;
    playerstringstream >> playerstring;
    m_playerCam = TopManager::Instance()->getGraphicManager()->getSceneManager()->createCamera(playerstring);
    Ogre::SceneNode * camNode = m_vehicle->getSceneNode()->createChildSceneNode(Ogre::Vector3(0,+5,-20));
    m_playerCam->setAutoTracking(true,m_vehicle->getSceneNode(),Ogre::Vector3(0,0,0));
    m_playerCam->setNearClipDistance(0.1);
    camNode->attachObject(m_playerCam);
}

int Player::getX()
{
    return m_vehicle->getSceneNode()->getPosition().x;
}

int Player::getY()
{
    return m_vehicle->getSceneNode()->getPosition().y;
}

int Player::getZ()
{
    return m_vehicle->getSceneNode()->getPosition().z;
}

Ogre::Radian Player::getAngle()
{
    return m_vehicle->getSceneNode()->getOrientation().getPitch();

}

int Player::getId()
{
    return m_playerId;
}

unsigned long Player::getMilliseconds()
{
    return m_timer->getMilliseconds();
}

void Player::toggleAutomatic()
{
    // Toggle automatic driving.
    m_automatic = !m_automatic;

    // If automatic driving was started, find a new path.
    if (m_automatic)
    {
        findNewPath();
    }
    else
    {
        std::cout << "AUTOMATIC OFF" << std::endl;
    }
}

void Player::findNewPath()
{
    std::cout << "AUTOMATIC ON" << std::endl;

    Ogre::Vector3 position = m_vehicle->getSceneNode()->getPosition();
    position.y = 0;
    position = position /2;
    std::cout << "Start position: " << position << std::endl;

    Graph* graph = TopManager::Instance()->getGraph();
    const Graph::Node & start(graph->getNearestNode(position));
    std::cout << "Start node: " << start << std::endl;

    const std::vector<Graph::Node> & nodes = graph->getNodes();
    const Graph::Node & goal = nodes.at(0);
    std::cout << "Goal node: " << goal << std::endl;

    AStar astar(graph);
    m_path = astar.findPath(start, goal);
}

void Player::setAutomatic(bool a) {
    m_automatic = a;
}

bool Player::getAutomatic() {
    return m_automatic;
}
