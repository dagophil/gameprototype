/*
 * Keyboard.h
 *
 */

#ifndef KEYBOARD_H_
#define KEYBOARD_H_

#include <OIS/OISJoyStick.h>
#include <OIS/OISInputManager.h>
#include "InputManager.h"
#include "Player.h"
#include <OGRE/OgreLogManager.h>
#include <iostream>

class Player;
class Vehicle;

/**
 * @class Keyboard
 * @brief Class to handle keyboard inputs
 */
class Keyboard : public OIS::KeyListener
{

public:

    static Keyboard* Instance();
    virtual ~Keyboard();
    void capture();
    void init();

private:

    Keyboard();
    static Keyboard* m_Instance;
    virtual bool keyPressed(const OIS::KeyEvent&);
    virtual bool keyReleased(const OIS::KeyEvent&);

    /**
     * @brief array to store config for buttons
     */
    OIS::KeyCode* m_pPlayerKeys;

    OIS::Keyboard* m_pKeyboard;
    OIS::InputManager* m_pInputManager;
    Vehicle* m_pVehicle;
    Player * m_pPlayer;

};

#endif /* KEYBOARD_H_ */
