#include "PlayerInput.h"
#include "Player.h"

#include "Vehicle.h"

PlayerInput::PlayerInput()
{
    m_inputManager = InputManager::Instance()->getOIS();
}

void PlayerInput::setButtonAxisMap(controllerType type)
{
    switch(type)
    {
    case logitech:
        m_buttonMap[0]  =  0;
        m_buttonMap[1]  =  1;
        m_buttonMap[2]  =  2;
        m_buttonMap[3]  =  3;
        m_buttonMap[4]  =  4;
        m_buttonMap[5]  =  5;
        m_buttonMap[6]  =  6;
        m_buttonMap[7]  =  7;
        m_buttonMap[8]  =  8;
        m_buttonMap[9]  =  9;
        m_buttonMap[10] = 10;
        m_buttonMap[11] = 11;

        m_axisMap[0] = 0;
        m_axisMap[1] = 1;
        m_axisMap[2] = 2;
        m_axisMap[3] = 3;
        break;
    case ps3:
        m_buttonMap[0]  =  15;
        m_buttonMap[1]  =  14;
        m_buttonMap[2]  =  13;
        m_buttonMap[3]  =  12;
        m_buttonMap[4]  =  10;
        m_buttonMap[5]  =  11;
        m_buttonMap[6]  =  8;
        m_buttonMap[7]  =  9;
        m_buttonMap[8]  =  0;
        m_buttonMap[9]  =  3;
        m_buttonMap[10] =  1;
        m_buttonMap[11] =  2;

        m_axisMap[0] = 0;
        m_axisMap[1] = 1;
        m_axisMap[2] = 2;
        m_axisMap[3] = 3;
        break;
    }
}

void PlayerInput::init(int playerId, Player* player)
{
    m_controllerId = playerId;
    int nDev =  m_inputManager->getNumberOfDevices(OIS::OISJoyStick);
    m_player = player;
    m_vehicle = m_player->getVehicle();
    if(nDev > playerId)
    {
        m_joystick = static_cast<OIS::JoyStick*>(m_inputManager->createInputObject(OIS::OISJoyStick, true));
        m_joystick->setEventCallback(this);
        std::string vendor = m_joystick->vendor();
        if(m_joystick->vendor() == "Logitech Logitech RumblePad 2 USB")
        {
            setButtonAxisMap(logitech);
            m_forceFeedback = true;
            Ogre::LogManager::getSingletonPtr()->logMessage("*** 'Logitech Logitech RumblePad 2 USB' found ***");
        }
        if(m_joystick->vendor() == "Logitech Logitech Dual Action")
        {
            setButtonAxisMap(logitech);
            m_forceFeedback = false;
            Ogre::LogManager::getSingletonPtr()->logMessage("*** 'Logitech Logitech Pad 2 USB' found ***");
        }
        if(m_joystick->vendor() == "Sony PLAYSTATION(R)3 Controller")
        {
            setButtonAxisMap(ps3);
            m_forceFeedback = false;
            Ogre::LogManager::getSingletonPtr()->logMessage("*** 'Sony PLAYSTATION(R)3 Controller' found ***");
        }
    }
    else
    {
        m_player->disableJoystick();
    }
}


bool PlayerInput::buttonPressed(const OIS::JoyStickEvent & evt, int button)
{
    // 0 gas; 1 bremse; 2 waffe wechseln, 9 reset, 3 schieen, 8 shutdown, 4 rckwrtsgang

    if (button == m_buttonMap[0])
    {
        m_vehicle->setThrottle(true);
    }
    else
        if(button == m_buttonMap[1])
        {
            m_vehicle->setBrake(true);
        }
        else
            if(button == m_buttonMap[9])
            {
                m_vehicle->resetOrientation();
            }
            else
                if(button == m_buttonMap[8])
                {
                    TopManager::Instance()->getGraphicManager()->setShutdown(true);
                }
                else
                    if(button == m_buttonMap[4])
                    {
                        m_vehicle->setReverse(true);
                    }
    return true;
}

bool PlayerInput::buttonReleased(const OIS::JoyStickEvent & evt, int button)
{
    // 0 gas; 1 bremse
    if(button == m_buttonMap[0])
    {
        m_vehicle->setThrottle(false);
    }
    else
        if (button == m_buttonMap[1])
        {
            m_vehicle->setBrake(false);
        }
        else
            if(button == m_buttonMap[4])
            {
                m_vehicle->setReverse(false);
            }

    return true;
}

bool PlayerInput::axisMoved(const OIS::JoyStickEvent & evt, int axis)
{
    // set steering in range from -1 to 1
    if(axis == m_axisMap[0])
        m_vehicle->setSteering((float)evt.state.mAxes[axis].abs / AXIS_RANGE);
    return true;
}

void PlayerInput::capture()
{
    m_joystick->capture();
}
