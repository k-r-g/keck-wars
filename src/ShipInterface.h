/**************************************************************************
* Structures: Ship Interface		                                      *
*                                                                         *
* Author: Dirien Perez                                                    *
*                                                                         *
* Description: The ShipStateInterface class is responsible for            *
*              interfacing between Game Control and the UI, AI, and Flight*
*              Graphics modules.                                          *
*              Game Control sends the Game State to the Ship State        *
*              Interface via the updateGameState() method, and it extracts*
*              the individual Ship States                                 *
*              from it.  Then the update() method is called on the AI, UI,*
*              and Flight Graphics modules as well as the so they may     *
*              update their internal variables, generate sounds, and      *
*              modify the graphics, respectively. The ShipStateInterface  *
*              is also responsible for sending new ship states to the Game*
*              Control after an input event or AI decision has occurred.  *
*                                                                         *
* Modifications: Dirien Perez     9-12-99 Initial Version                 *
*                Dirien Perez     9-29-99 Added Cockpit Class             *
*                Dirien Perez	 10-03-99 Defined UpdateShips,            *
*                                         updateGameState and             *
*                                         updateUIRequests Methods.       *
*                Dirien Perez    10-04-99 Added private and public fields.*
*                Dirien Perez    10-05-99 Modified ShipState array to be a*
*                                         a field to keep track of the    *
*                                         current Ship                   
*				 Dirien Perez	 10-13-99 Change the arrays data structu  *
*										  ctures to List				  *
*				 Dirien Perez	 10-13-99 Compiled Header File			  *
*				 Dirien Perez	 10-16-99 Added methods to update status  *
*                                         of players					  *
*				 Dirien Perez	 10-17-99 Add isAIpilot field and method  *
*										  to determine the type of player *
*																		  *
**************************************************************************/
#ifndef SHIPINTERFACE_H
#define SHIPINTERFACE_H

#include "GameStateDestination.h"
#include "SoundPlayer.h"
#include "ComputerPilot.h"
#include "ShipState.h"
#include "GameState.h"

class GameStateDestination;
class SoundPlayer;
class ComputerPilot;
struct ShipState;
struct GameState;
class SpaceObject;
class Ship;



class ShipInterface : public GameStateDestination {
//private:
public:

	// the current game state
    GameState currentGameState;

	ShipState* theShip;
	// the array of current ship states.

	SoundPlayer* currentSound;
	// the current sound player for the UI module.

	ComputerPilot* currentAIPlayer;
	// the current player for the AI module.

	int externalID;

	bool isAIPilot;
	// this determines whether or not this player is an Computer Pilot or 
	//  a human player.
      
public:

	ShipState* updateGameState(GameState* gameState);
	//  This method is called by Game Control to pass the Game State,
	//  returning a list of one length ship state after the information 
	//	has been processed.

	void updateShips();
	//  This method is responsible for creating and updating 
	//  the internal ship states.  Once a new game state is 
	//  received from Game Control via the updateGameState() 
	//  method the updateShips() method is called to filter
	//  the ship states from the other game state information.
	

	//  After the ships are updated the update() and sound event() methods
	//	from Flight Graphics, AI and UI are called respectively to pass
	//	the information to inform graphics to update the display, to inform
	//	AI of the new Ship State, and to inform UI to generate sounds.    
	
	void startFire();
	//  This method is called by the User Interface and AI to update 
	//	the fire status of their player.	

	void stopFire();
	//	This method is called by the User Interface and AI to update 
	//	the fire status of their player.
	
	
	void pitch(int movement);
	//	This method is called by the User Interface and AI to update 
	//	the pitch orientation of their player. 
	
	
	void roll(int movement);
	//	This method is called by the User Interface and AI modules to 
	//	update the roll attributes of their player;

	
	void yaw(int movement);
	//	This method is called by the User Interface and AI modules to 
	//	update the yaw movements of their player.
	
	
	void speed(int actualSpeed);
	//	This method is called by the User Interface and AI modules to 
	//	update the speed of their player.

	
	void quit();
	//	This method is called by the UI module to indicate the player 
	//	quit the game.

    ShipInterface(int shipID) {
		isAIPilot = false;
		externalID = shipID;
	    theShip = new ShipState();
		theShip->id = shipID;
		theShip->firing = false;
		theShip->pitch = 0;
		theShip->yaw = 0;
		theShip->roll = 0;
		theShip->speed = 0;
		theShip->quit = false;
		theShip->next = NULL;
	    currentSound = new SoundPlayer();
	    currentAIPlayer = NULL;
	}
	// Constructor

	~ShipInterface(){
		delete theShip;
		delete currentSound;
	}

	 
	void isComputerPilotSI(ComputerPilot* cp);
	// Give pointer to Computer Pilot

	void setAIPlayer(bool isAI) {isAIPilot = isAI;};
    // Sets the AI Pilot flag

};

#endif