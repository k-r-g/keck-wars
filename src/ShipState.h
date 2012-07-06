/**************************************************************************
* Classes/Structures: GameState, Player State, Space Object               *
*                                                                         *
* Author: Brian Birmingham and Dirien Perez                               *
*                                                                         *
* Description: Information passed between Game Control and Game State     *
*				interface uses these structures as it's organization.     *
*                                                                         *
* Modifications: Brian Birmingham 9-24-99 Initial Version                 *
*                                                                         *
*                Brian Birmingham 9-28-99 Added additonal Vectors to the  *
*                                         SpaceObject class, added define *
*                                         statements, reworked int values *
*                                         for flight controls in the      *
*                                         PlayerState object.			  *
*                                                                         *
*                Dirien Perez 9-29-99     Changed struct name PlayerState *
*                                         to ShipState                    *
*                                                                         *
*                Brian Birmingham 9-29-99 Added radius field to           *
*                                         SpaceObject and fixed minor     *
*                                         errors in comments and added a  *
*                                         few more.                       *
*                                                                         *
*                Brian Birmingham 10-2-99 Removed the array of ships from *
*                                         GameState, since they will be   *
*                                         represented in the SpaceObjects *
*                                         array.  Added numberOfShips     *
*                                         to GameState to specify where   *
*                                         non-Ship Space Objects start.   *
*                                                                         *
*                Dirien Perez    10-3-99  Added the position, direction,  *
*                                         and up vectors to the ShipState *
*                                         struct.                         *
*                                                                         *
*                Brian Birmingham 10-4-99 Removed the position, direction,*
*                                         and attitude vectors from the   *
*                                         ShipState struct.  They are     *
*                                         present in the Ship class, and  *
*                                         maintained as part of the       *
*                                         GameState, not the ShipState.   *
*                                                                         *
*                Brian Birmingham10-11-99 Changed Game State's structure  *
*                                         from an Array to a linked list  *
*                                                                         *
**************************************************************************/
#ifndef SHIPSTATE_H
#define SHIPSTATE_H

#define PITCHEVEN 0
#define PITCHUP -1
#define PITCHDOWN 1
#define YAWEVEN 0
#define YAWLEFT -1
#define YAWRIGHT 1
#define ROLLEVEN 0
#define ROLLCOUNTERCLOCKWISE -1
#define ROLLCLOCKWISE 1

struct ShipState{

	ShipState(){
		this->firing=false;
		this->disruptors=false;
		this->pitch=0;
		this->pause=false;
		this->quit=false;
		this->roll=0;
		this->speed=0;
		this->yaw=0;
	}

	int id;
	// matches id of spaceObject in GameState.
	// also matches the array index in GameControls array of Ship States.

	bool firing;
	// indicates whether or not the player is firing.

	bool disruptors;
	// indicates whether or not the player is firing disruptors.

	int pitch;
	// 0 no pitch, -1 pitch up, 1 pitch down.

	int yaw;
	// 0 no yaw, -1 yaw left, 1 yaw right.

	int roll;
	// 0 no roll, -1 roll counter clockwise, 1 roll clockwise.

	int speed;
	// valid from 0 to 100.

	bool pause;
	// When true will communicate that a player wants to toggle the game's
	// pause state.

	bool quit;
	// When true will signal NetworkControl to shut down the
	// connection, or GameControl to shut down the server.

	ShipState *next;
	// The next ShipState in the list.
};

#endif