/**************************************************************************
*                                                                         *
* Class Name: GameStateDestination                                        *
*                                                                         *
* Author: Brian Birmingham                                                *
*                                                                         *
* Description: This is an abstract class that is extended by all classes  *
*              that need to receive a GameState object from Game Control. *
*              These are GameStateInterface and Network Server.  In       *
*              extending this class, they must define the abstract method *
*              updateGameState to specify what they do with the GameState *
*              and how they determine what the array of PlayerState       *
*              addresses to be returned is.                               *
*                                                                         *
* Revisions:  Brian Birmingham 9-22-99 Initial Version                    *
*                                                                         *
*             Brian Birmingham 9-28-99 Added return type, fixed           *
*                                      descriptions and comments.         *
*                                                                         *
**************************************************************************/
#ifndef GAMESTATEDESTINATION_H
#define GAMESTATEDESTINATION_H

#include "ShipState.h"
#include "GameState.h"
struct ShipState;
struct GameState;

class GameStateDestination {

public:
	GameStateDestination *next;

	virtual ShipState* updateGameState(GameState *gameState) = 0;
	// The method called by GameControl to update the Game State and
	// get whatever the most recent player state is.  All classes that
	// extend this class must override this abstract method.
};

#endif