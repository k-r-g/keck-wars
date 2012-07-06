/**************************************************************************
*                                                                         *
* Class Name: GameControl                                                 *
*                                                                         *
* Author: Brian Birmingham                                                *
*                                                                         *
* Description: The purpose of this system is to maintain the state of the *
*              game by sending out the current GameState and retrieving a *
*              ShipState from each of the GameStateDesinations.  It       *
*              then uses this information to create a new GameState.      *
*                                                                         *
* Revisions:  Brian Birmingham 9-22-99 Initial Version                    *
*                                                                         *
*             Brian Birmingham 9-28-99 Removed an unnecessary method and  *
*                                      fixed some method return types.    *
*                                                                         *
*             Brian Birmingham 9-28-99 Fixed original constructor, added  *
*                                      a new constructor.  Changed Player *
*                                      States to Ship States for clarity. *
*                                                                         *
**************************************************************************/
#ifndef GAMECONTROL_H
#define GAMECONTROL_H

//#include <iostream>
#include <string>
#include "GameStateDestination.h"
#include "GameEndManager.h"
#include "FlightGraphics.h"
//#include "GameState.h"
//#include "ShipState.h"
//#include "Geometry.h"
class GameStateDestination;
//struct GameState;
//class SpaceObject;
//class Ship;
//struct ShipState;
//class Plane;
//class Point;
//class Vector;
//class Ray;
using namespace std;

#define MAXPLAYERS 8
#define DISTANCEFROMCENTER 1000
//#define PI 3.141592

#define DEADKECKWINGLIFE 0
#define DEADENEMYONELIFE -1
#define DEADENEMYTWOLIFE -2
#define DEADENEMYTHREELIFE -3
#define DEADCARGOSHIPLIFE -4
// note that the above defines must all be 0 or lower for the death of
// ships to occur correctly in single player games.

class GameControl {

public:

	GameControl(GameStateDestination *gameStateDestinations,
		int numberOfShips, int shipTypes[]);
	// Constructor for Multi Player games requires that all the modules
	// that need Game State updates be given to it in an array.  It
	// requires that the number of ships be specified so it knows how
	// big the array of Ship States is.

	GameControl(GameStateDestination *gameStateDestinations,
		int numberOfShips, string buffer);
	// Constructor for Single Player games requires that all the modules
	// that need Game State updates be given to it in an array.  It
	// requires that the number of ships be specified so it knows how
	// big the array of Ship States should be.  It also requires a file
	// descriptor for the file that will specify mission details.

	~GameControl();
	// Deconstructor releases all memory, and shuts down Game Control.

	void startGame();
	// This game is called by Setup Game to start the game running.  
	// It releases the thread of control from Setup Game to Game Control
	// allowing Game Control to enter a loop where it distributes
	// GameStates and retreives ShipStates, and finally updates the
	// GameState before moving to the top of the loop.  When the game is
	// over, the method returns and control is given to Setup Game again.

protected:

	int GCPROCESSINGLEVEL;
	// this variable will determine how much information is processed when
	// creating a new Game State.
	// 0 - only Exit commands
	// 1 - Ship Direction changes (ship does not move)
	// 2 - Ship movement and speed
	// 3 - Weapon Projectiles and Explosions
	// 4 - Collision Detection and Damage assignment

	struct ShipPosition{
		Point location;
		Vector direction;
		Vector up;
		Vector right;
	};

	struct ClockInfo{
		unsigned __int64 lastFireTime;
		unsigned __int64 lastShieldGenTime;
		unsigned __int64 lastAccelTime;
	};

	ShipPosition startingPositions[MAXPLAYERS];

	ClockInfo playerClocks[MAXPLAYERS];

	int timesDied[MAXPLAYERS];

	int dockings;

	int cargoDeaths;

	int shipTypes[MAXPLAYERS];

	int numberOfShips;
	// Stores the number of ships that are in the game.

	unsigned __int64 clock;
	// the number of gamestates sent out.

	bool respawnOn;

	GameEndManager GEM;
	// The Manager for determining the end of the game.

	GameState *newState;
	// The state of the game being created in this iteration.

	GameState *lastState;
	// The state that everybody refers to while the new one is being built.

	GameStateDestination* gameStateDestinations;
	// An array of pointers for all modules the game state needs to be
	// sent to.

	ShipState* shipStates;
	// An array for storing pointers to all the ShipStates of the 
	// players in the game.

	ShipState* localShip;
	// This Ship State is the Local Player's Ship State.  It must be kept
	// track of so that when the local player quits, the game ends.

	SpaceObject* lastSO;
	// Points to the last Space Object in the GameState.

	void initializeGame(GameStateDestination *gsds, int nos);
	// This method is called by both constructors to prepare the Game.

	void createShipStateStructures();
	// This will be called by all constructors to initialize the list of
	// ShipStates that GameControl stores internally.

	void storeStartingPositions();
	// Stores the current positions of the ships in the Game State into
	// the array of starting positions.  This method should therefore be
	// called at the begining of the game's execution.

	void initializePlayerClocks();
	// Sets clock information for all players to 0 based on numberOfShips.
	// Use only at the begining of the game's execution.

	void createShipsInGameState(GameState *gameState);
	// This will be called by all constructors to initialize the list of
	// Ships in the GameState object.

	void loadShipInformation(int id, GameState *gameState, string segment);
	// This method loads a ship's information into the game state based on
	// it's id number and a segment describing it in the format:
	// <type>:<team>:<x>,<y>,<z>:<fd i>,<fd j>,<fd k>:<up i>,<up j>,<up k>;

	void readInGameStateFromFile(GameState *gameState, string Buffer);
	// This method reads the information from the specified file into the
	// specified game state.  It is the single player replacement for
	// multi-player's "createShipsInGameState."

	void addKeckLab(string segment);
	// This will add the KeckLab to the Game State with an id equal to the
	// number of ships. (since ship ids start at 0).  It's position in the
	// list of space objects will be immediately after all the ships.

	void setVictoryOrDefeatConditions(string segment);
	// This will set either victory or defeat conditions based on a string
	// passed in that follows the format:
	// [VICTORY|DEFEAT]:<field>=<value>{+<field>=<value>};

	Point extractPointFrom(string segment);
	// Returns a point parsed from a string segment in the format:
	// <x>,<y>,<z>:
	// or
	// <x>,<y>,<z>;

	Vector extractVectorFrom(string segment);
	// Returns a vector parsed from a string segment in the format:
	// <i>,<j>,<k>:
	// or
	// <i>,<j>,<k>;

	void addVictoryOrDefeatCondition(string segment, string type);

	void destroyShipStateList(ShipState* current);
	// This method will recursively destroy the list of Ship States.

	void destroySpaceObjectList(SpaceObject* current);
	// This method will recursively destroy the list of Space Objects.

	void updateShipAttitudes();
	// This method will update all the Ship Attitudes.

	void updateShipSpeeds();
	// This method will update all the Ship Speeds.

	void updateShipPositions();
	// This method will move all the Ships appropriately.

	void updateSpaceObjects();
	// This method will move all the space objects, and adjust Explosions.

	void regenShields(Ship* ship);
	// This method regenerates the shields of the ship based on clock time.

	void convertExplosionToFromShip(Ship* ship);
	// This method will determine wheter a ship should be changed to an
	// explosion or an explosion changed to a ship.

	void detectCollisions();
	// This mehtod will detect collisons, and apply damage.

	void updatePauseState();
	// This method will toggle the processing level between 0 and 4 based
	// on the pause value in user Ship States.

	void processQuits();
	// This method finds people who quit, and removes them from the game.
	// Throws a string if the list of gameStateDestinations, or the list 
	// of Ship States is smaller than indicated by the "numberOfShips"
	// variable.

	void destroyShip(int shipID);
	// Removes the ship from the GameState and removes its corresponding
	// Ship State from the list of Locally stored Ship States.

	void sendGameState();
	// Exports the game state to all members of the gameStateDestinations
	// array, and retrieves all the arrays of ShipState pointers.
	// Throws a string if the list of gameStateDestinations is smaller 
	// than indicated by the "numberOfShips" variable.

	void copyShipStateInformationFrom(ShipState* current);
	// Copies information from the specified ShipState into the appropriate
	// node of the List stored in this class, determined by the id field.

	bool isCollisionBetween(SpaceObject *first, SpaceObject *second);
	// Returns true if the objects are touching, and false if they are not.
	// This is determined by comparing the sum of their radii to the
	// distance between them.

	void grantKillTo(int attackerID, int deadID);
	// finds the player with the ID passed in and adds a kill to their
	// tally.

	void updateShipAttitude(Ship* ship, ShipState* shipState);
	// Takes the specified ship from the GameState's array of Space
	// Objects, and  adjusts it's attitude based on it's pitch, yaw, and
	// roll flags in the ShipState array.

	void updateShipSpeed(Ship* ship, int desiredSpeed);
	// Takes the specified ship from the GameState's array of Space
	// Objects, and adjusts it's speed based on the speed flag in the Ship
	// State array.

	void updateWeaponPosition(SpaceObject* weapon);
	// Takes the specified Space Object from the GameState's array of Space
	// Objects, and moves it to a new Point in space based on it's current
	// speed and direction of travel.

	void updateExplosion(SpaceObject* explosion);
	// increases the radius of the specified Space Object, and decreases
	// its damage.  This method should only be called for an Explosion.

	void dockCargoShip(int id);
	// This method will find the Cargo Ship with the listed id and remove
	// it from the Game State, 

	bool vectorsAreEqual(Vector v, Vector u);
	// makes calls to the "equals" function in Geometry.h, with a slightly
	// higher epsilon value (error margin), and returns the result.

};

#endif