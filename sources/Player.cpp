#include "Player.h"

#include "Vehicle.h"

Player::Player(int playerId)
    : m_playerId(playerId),
      m_lives(10),
      m_opponent(0)
{
    m_joystick = true;
    srand(time(NULL) );
    m_vehicle = new Vehicle("car.mesh",400.f,this);
    //m_vehicle->translate(10*playerId,10*playerId,10*playerId);
    m_timer = new Ogre::Timer();

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

void Player::addOpponent() {
	m_opponent++;
}

int Player::getOpponent()
{
    return m_opponent;
}
