#ifndef PLAYERINPUT_H_
#define PLAYERINPUT_H_

#include <OIS/OISJoyStick.h>
#include <OIS/OISInputManager.h>
#include "InputManager.h"
#include "Player.h"
#include <OGRE/OgreLogManager.h>
#include <iostream>

class Player;
class Vehicle;

/**
 * Enumeration of types of controllers
 *
 */
enum controllerType
{
    logitech,   /** Logitech gamepad */
    ps3     /** Playstation gamepad */
};

/**
 *
 * @class PlayerInput
 * @brief Class to handle inputs for players
 *
 * Each Player gets its own PlayerInput class to handle its inputs
 *
 */
class PlayerInput : public OIS::JoyStickListener
{

public:

    PlayerInput();
    /**
     * @brief capture function (inherited from OIS)
     */
    void capture();

    /**
     * @brief initialisation function
     * @param playerId number of the player (starting with 0)
     * @param player Pointer to player class
     */
    void init(int playerId, Player* player);

    /**
     * @brief function called after joystick button is pressed
     * @param evt
     * @param button
     * @return
     */
    virtual bool buttonPressed(const OIS::JoyStickEvent& evt, int button);

    /**
     *
     * @brief function called after joystick button is released
     * @param evt
     * @param button
     * @return
     */
    virtual bool buttonReleased(const OIS::JoyStickEvent& evt, int button);

    /**
     *
     * @brief function called after joystick axis is moved
     * @param evt
     * @param axis
     * @return
     */
    virtual bool axisMoved(const OIS::JoyStickEvent& evt, int axis);

private:

    static const int AXIS_RANGE = 32768;
    void setButtonAxisMap(controllerType type);
    int m_controllerId;
    Player* m_player;
    Vehicle* m_vehicle;
    int m_buttonMap[12];
    int m_axisMap[4];
    bool m_forceFeedback;
    OIS::JoyStick* m_joystick;
    OIS::InputManager* m_inputManager;

};

#endif
