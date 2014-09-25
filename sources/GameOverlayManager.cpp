/*
 * OverlayManager.cpp
 *
 */

#include "GameOverlayManager.h"

#include "Player.h"
#include "Vehicle.h"
#include "Map.h"

GameOverlayManager::GameOverlayManager() {}

GameOverlayManager::~GameOverlayManager() {}

Ogre::OverlayManager * GameOverlayManager::getOverlayManager()
{
    return m_overlayMgr;
}

void GameOverlayManager::init()
{
    m_overlayMgr = Ogre::OverlayManager::getSingletonPtr();
    m_dimX = TopManager::Instance()->getGraphicManager()->getViewport()->getActualWidth();
    m_dimY = TopManager::Instance()->getGraphicManager()->getViewport()->getActualHeight();

    // creates overlays (for all players)
    Ogre::Overlay* overlayPlayer = Ogre::OverlayManager::getSingleton().getByName("Player/Overlay");
    //Ogre::OverlayManager::getSingleton().getOverlayElement("Player/TextScore")->setPosition(0,0);
    overlayPlayer->show();

    Ogre::Overlay* overlayClock = Ogre::OverlayManager::getSingleton().getByName("Clock/Overlay");
    overlayClock->show();

    Ogre::Overlay* overlayFuel = Ogre::OverlayManager::getSingleton().getByName("Fuel/Overlay");
    overlayFuel->show();

	Ogre::Overlay* overlayOpponentcount = Ogre::OverlayManager::getSingleton().getByName("Opponentcount/Overlay");
    overlayOpponentcount->show();

    update();
}

void GameOverlayManager::update()
{
    Player* player = TopManager::Instance()->getPlayer();

    // Create a string for the lives.
    std::stringstream ssLives;
    ssLives << "Leben: " << player->getLives();

	// Create a string for the opponents
    size_t numOpponents = TopManager::Instance()->getMap()->getNumOpponents();
	std::stringstream ssOpponents;
    ssOpponents << "Gegner: " << player->getOpponent() << "/" << numOpponents;




	// Update the opponentcount overlay.
    Ogre::OverlayManager::getSingleton().getOverlayElement("Opponentcount/Text")->setCaption(ssOpponents.str());

    // Update the lives score overlay.
    Ogre::OverlayManager::getSingleton().getOverlayElement("Player/TextScore")->setCaption(ssLives.str());

    // Get current playing time in minutes, seconds and milliseconds.
    long milliseconds = player->getMilliseconds();
    long seconds = milliseconds/1000;
    long minutes = seconds/60;
    milliseconds = milliseconds % 1000;
    seconds = seconds % 60;

    // Create a string for the playing time.
    // Format min:secs:msecs with leading zeros for seconds and milliseconds.
    std::stringstream ssTime;
    ssTime << std::setfill('0');
    ssTime << "Zeit: ";
    ssTime << minutes << ":" << std::setw(2) << seconds << ":" << std::setw(3) << milliseconds;

    // Update the clock text overlay.
    Ogre::OverlayManager::getSingleton().getOverlayElement("Clock/Text")->setCaption(ssTime.str());

    // Create a string for the fuel percentage.
    std::stringstream ss;
    ss << "Tank: " << (int) player->getVehicle()->getFuel() << "%";

    // Update the fuel overlay.
    Ogre::OverlayManager::getSingleton().getOverlayElement("Fuel/Text")->setCaption(ss.str());
}

void GameOverlayManager::showGameOver(std::string largeText, std::string smallText)
{
    Ogre::Overlay* overlayGameOver = Ogre::OverlayManager::getSingleton().getByName("Gameover/Overlay");
    overlayGameOver->show();

    Ogre::OverlayManager::getSingleton().getOverlayElement("Gameover/Largetext")->setCaption(largeText);
    Ogre::OverlayManager::getSingleton().getOverlayElement("Gameover/Smalltext")->setCaption(smallText);
}
