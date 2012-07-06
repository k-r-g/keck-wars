/************************************************************************
* Class Name:  ComputerPilot                                           
*                                                                      
* Author: Monica Alvarado                                              
*                                                                      
* Description: This class is implements the computer pilot.           
*                                                                      
* Revisions:  Monica Alvarado - 9/14/99  - Initial Version             
*                                                           
************************************************************************/
#ifndef COMPUTERPILOT_H
#define COMPUTERPILOT_H

#include "ShipInterface.h"
#include "geometry.h"
#include "GameState.h"

struct GameState;
class SpaceObject;
class ShipInterface;

#define OUTTER_RANGE 0
#define MIDDLE_RANGE 25
#define INNER_RANGE 50
#define SHIP_CAN_ATTACK 30
#define SHIP_CAN_NOT_ATTACK 50
#define STRONG_SHIELDS 100
#define GOOD_SHIELDS 30
#define NOT_SO_GOOD_SHIELDS 60
#define NO_SHIELD_PROTECTION 70
#define ENOUGH_SHIELDS 10
#define OK_SHIELDS 35
#define WEAK_SHIELDS 20
#define NO_SHIELDS 0
#define PROJECTILE_AHEAD 50
#define IN_ATTACK_POSITION 50
#define NOT_IN_ATTACK_POSITION 30
#define UNAWARE_TARGET 70
#define A_THREAT  30
#define NOT_A_THREAT 30
#define ATTACKING 80
#define ENEMY_STRONG_SHIELDS 10
#define ENEMY_OK_SHIELDS 20
#define ENEMY_LOW_SHIELDS 35
#define ENEMY_NO_SHIELDS 50
#define ENEMY_LOW_HEALTH 50
#define ENEMY_OK_HEALTH 30
#define ENEMY_GOOD_HEALTH 10
#define DANGER 70

class ComputerPilot {
  
  struct ShipInfo {
    int shipId;
	int mode;				//single- or multi-player game?
	int health;	
	int shields;
	int speed;
	int type;				//The ComputerPlayer's type/mission.
    int currentState; 		//The Current FSM state.
	GameState* gameState;	//The current GameState.
	Vector direction;
	Vector up;
	Vector right;
	Point position;
  };
 
  public:
    

 	
	ShipInfo shipInfo;

	ShipInterface* shipInterface;
	// the shipInterface the pilot communicates with.

	  ComputerPilot(int id, int type, int mode, ShipInterface* si); 	            
	// Constructor, creates a ComputerPilot.
	// The ship's id, the type of ship it is and the 
	// game mode (single-player, multi-player needs to be specified
	// so that the init() method can correctly initialize the pilot.

	  ~ComputerPilot(); 			
    // Deconstructor, closes the ComputerPilot.

    
	void update(GameState* gameState);
	// ShipInterface will update the ComputerPilot's GameState by 
	// calling this method.
	
	void think();
	// controls the actions of the pilot.  It gets 
	// called right after the ComputerPilot is updated by ShipInterface
	// and uses the other methods in ComputerPilot to see if it should
	// continue with the same state or choose a new one.  

	void initShip(); 
	//initiates a computerPilot according to its type.

	void evadingPattern(int pattern);
	// Moves the ship around depending on the pattern number (1-4).
	// uses turnAwayFrom();

	int chooseNextState();
	// Analyzes the ships's state, and inputs from the 
	// current GameState, and the player's personality
	// and returns the new state to transition to.


    Point aim(Point target, int targetSpeed, Vector direction,
			 Point origin, int speed, int projectileSpeed, Vector mydirection);
	// Something at position origin, with speed speed wants to shoot
	// a projectile with speed projectileSpeed at a target at 
	// postion target, moving at speed targetSpeed.
	// Returns true if the origin is a good position to shoot from
	// false if not.

	bool isBeingAttacked(); 	
	// Looks around for explosions and projectiles close by.

	bool enemyIsClose();
	// It returns true if there's an enemy close by
	// whose id != the current target.  False otherwise.

	void turnToward(Point position);
	// Turns the ComputerPilot towards point position.

	void turnAwayFrom(Point position);
	// Turns the ComputerPilot away from point position.

	void attack();
	// Attacks the closest enemy ship.  
	// A target must be selected before calling this method.
	// (in chooseNextState())

	void evade();
	//Evades the closest enemy ship.
	// An attacker must be selected before calling this method.
	// (in chooseNextState())

	void flock();
	// Makes the pilot flock with its 'friend' ships in
	// single-player games.

	void pattern();
	// Makes the pilot take randomly-generated paths
	// in space();

	void checkRoute();
	// method provided for the cargoships.  
	// It updates and orients the ships (towards!) the KeckLab.

};

#endif
