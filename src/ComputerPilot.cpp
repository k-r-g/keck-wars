/****************************************************************************
*  ComputerPilot.cpp
*
*  Author:  Monica Alvarado
*
*  Description:  This file contains the implementation of the ComputerPilot
*				 used in the KeckWars project.
*
*  Revisions:
*		Monica Alvarado		-20 October 1999  --Initial proposal
*												
****************************************************************************/

#include "stdafx.h"
#include "ComputerPilot.h"
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int innerRadius = 1000;
int midRadius = 3000;
int outterRadius = 5000;
int attackerScore = 0;
int targetScore = 0;
int currentTargetScore = 0;
int currentAttackerScore = 0;

bool DoneWithLastState = true;
bool TargetFound = false;
bool AttackerFound = false;
Ship *target = NULL;
Ship *attacker = NULL;
Ship *leader = NULL;


int patternCounter = 0;
int state = 0;
int counter = 0;	
int leaderId = -1;
int attackerId = -1;
int targetId = -1;
int closeEnemyId = -1;

Point keckLabLocation(0,0,0);

Point attackerPosition, targetPosition, currentPosition;
Vector attackerDirection, targetDirection, currentDirection;

//------------------------------------------------------------------
// used for random numbers
// Random int on [0..r] 
//------------------------------------------------------------------

double random(double r) {
	int i;	
	double f;
	i = (rand() & 0xffff);
	f = r * (((double)(i)) / 65536.0);
	return int(f);
}


//------------------------------------------------------------------
// constructor
//------------------------------------------------------------------


ComputerPilot::ComputerPilot(int id, int type, int mode, ShipInterface* si) {
	shipInfo.shipId = id;
	shipInfo.type = type;
	shipInfo.mode = mode;
	shipInterface = si;
	initShip();
	
}
	

//------------------------------------------------------------------
// destructor.
//------------------------------------------------------------------


ComputerPilot::~ComputerPilot() {}

//------------------------------------------------------------------
// void initShip() initiates the ComputerPilot.
// It gives the pilot initial movement, so that it's not
// just sitting around waiting to be shot!!! 
// I use a random number generator so that the movements are not
// as predictable when they start up!
//------------------------------------------------------------------

void ComputerPilot::initShip() {
	if (shipInfo.mode == 1) {
		if (shipInfo.type != 4) {
			shipInterface->pitch(random(4));
			shipInterface->yaw(random(4));
			shipInterface->roll(random(4));
			shipInterface->startFire();
			shipInterface->speed(random(40));
			DoneWithLastState = true;
		}
		else {
			shipInterface->pitch(random(1));
			shipInterface->yaw(random(1));
			shipInterface->roll(random(1));
			shipInterface->startFire();
			shipInterface->speed(random(15));
			DoneWithLastState = true;
		}

	}
	else {
		shipInterface->pitch(random(4));
		shipInterface->yaw(random(4));
		shipInterface->roll((4));
		shipInterface->speed(random(15));
		shipInterface->startFire();
		DoneWithLastState = true;
	}
}

//------------------------------------------------------------------
// void update() receives a new gameState from ShipInterface and
// 'updates' the ComputerPilot's world.  Once this is done, it calls
// think() to get the pilot moving again.
//------------------------------------------------------------------

void ComputerPilot::update(GameState* gameState) {

	//clear all flags in the current ShipState.
	shipInterface->stopFire();
	shipInterface->yaw(0);
	shipInterface->roll(0);
	shipInterface->pitch(0);

	// update the game state
	shipInfo.gameState = gameState;

	Ship* current = (Ship *)(shipInfo.gameState->spaceObjects);
	while (current != NULL) {
		if (current->id == shipInfo.shipId) {
			shipInfo.position = current->position;
			shipInfo.direction = current->direction;
			shipInfo.up = current->up;
			shipInfo.right = current->right;
			shipInfo.speed = current->speed;
			shipInfo.health = current->life;
			shipInfo.shields = current->shields;
			think();
			break;
		}
		current = (Ship*)current->next;
	}
	return;
}

//------------------------------------------------------------------
// void attack(int target) chases and fires at an enemy ship 
// target.
//------------------------------------------------------------------

void ComputerPilot::attack() {

	DoneWithLastState = false;
	TargetFound = false;

	Ship* current;
	
	// First update the target id if we're just starting to attack.
	
	if (targetId == -1) {
		targetId = target->id;
	}
	
	// Once we know who our target is, attack unless there is an
	// explosion or a projectile close by and our health is low,
	// or if we're being attacked by some other ship that is not
	// our current target.

	while (true) {
		if (isBeingAttacked() && (shipInfo.health < 50)) {
			break;
		}
		if ((enemyIsClose()) && (closeEnemyId != targetId)) {
			break;
		}
		
		current = (Ship *)(shipInfo.gameState->spaceObjects);
		
		// update the target ship's position and direction.

		for (int i = 0; i < shipInfo.gameState->numberOfShips; i++) {
			if (current->id == targetId) {
				TargetFound = true;
				target = current;
				targetPosition = current->position;
				targetDirection = current->direction;
				break;
			}
			current = (Ship*)current->next;
		}

		// This flag prevents the pilot from trying to attack a
		// ship that has been destroyed.
		
		if (!TargetFound)
			break;

		// clear flag for next iteration
		TargetFound = false;
		
		double distance = shipInfo.position.distanceTo(targetPosition);
						
		
		// if we are very close, turn away and increase speed.
		// then break, so that we can change state.

		if (distance < 1000) {
			if ((shipInfo.health >= 50) && (strcmp(target->type, "CARGOSHIP") != 0)){
				turnAwayFrom(targetPosition);
				shipInterface->speed(200);
				break;
			}
			else {
				turnToward(targetPosition);
				shipInterface->startFire();
				return;
			}
		}
	
		// if we are close enough to shoot

		if (distance < 2000) {
						
				Point toAimAt = aim(targetPosition, target->speed, targetDirection,
				shipInfo.position, shipInfo.speed, 500, shipInfo.direction);

				// if we can't aim at it, then turn toward target position,
				// else, turn toward the new point, and shoot.
		
				if ((toAimAt.x == 0) && (toAimAt.y == 0) && (toAimAt.z == 0)) { 
						turnToward(targetPosition);
						shipInterface->startFire();
					if (shipInfo.speed > 100) {
						shipInterface->speed(shipInfo.speed+10);
					}
					
					return;
				}
				else {
					turnToward(targetPosition);
					shipInterface->startFire();
					if (shipInfo.speed > 100) {
						shipInterface->speed(shipInfo.speed+10);
					}
					return;
				}
			
		}
		
		// else we know, we're not in a good firing position and we get closer
		// in the direction of the target.

		else {
				turnToward(targetPosition);
				if (shipInfo.speed > 100) {
					shipInterface->speed(shipInfo.speed+10);
				}
				return;
		} 
	
	}
	targetId = -1;
	DoneWithLastState = true;
}


//------------------------------------------------------------------
// void (int attacker) evades an enemy ship provided with its
// ship id.
//------------------------------------------------------------------

void ComputerPilot::evade() {
	DoneWithLastState = false;
	AttackerFound = false;  

	SpaceObject* current = NULL;

   	if (attacker == NULL)
			return;

	if (attackerId == -1) {
		attackerId = attacker->id;
	}
	
	while (true) {
		current = shipInfo.gameState->spaceObjects;

		// First update the attacker's position and direction.  Here we
		// include every space object (i.e. not olnly the ships) because
		// we may be evading a 

		while (current != NULL) {
			if (current->id == attackerId) {
				AttackerFound = true;
				attackerPosition = current->position;
			}
			current = current ->next;
		}

		// if the attacker is at a safe distance, or if we couldn't find it,
		// we stop evading.
		
		if (!AttackerFound)
			break;

		// clear flag for next iteration
		AttackerFound = false;  

		
		if (attackerPosition.distanceTo(shipInfo.position) > 2000) 
			break;
		else {
				if (attacker == NULL)
					return;
		
     		if ((strcmp(attacker->type, "WEAPON") == 0)||(strcmp(attacker->type, "EXPLOSION") == 0)) {
			
				// if we're evading an explosion, we know that it is pretty close to 
				// us, so we simply find where it is and turn away from it.
				turnAwayFrom(attackerPosition);
				shipInterface->speed(shipInfo.speed*2);
				return;
			}
			// else we are evading a ship
			else {
				evadingPattern(random(3));
				return;
			}
		}
	}
	attackerId = -1;
	DoneWithLastState = true;
}

//------------------------------------------------------------------
// simple evading patterns and changes of speed.
//------------------------------------------------------------------

void ComputerPilot::evadingPattern(int pattern) {
	if (pattern == 0) {
		shipInterface->roll(1);
		shipInterface->yaw(1);
		shipInterface->pitch(-1);
		shipInterface->speed(200);
		return;
	}
	else if (pattern == 1) {
		shipInterface->roll(1);
		shipInterface->yaw(-1);
		shipInterface->pitch(1);
		shipInterface->speed(50);
		return;
	}
	else if (pattern == 2) {
		shipInterface->roll(-1);
		shipInterface->yaw(-1);
		shipInterface->pitch(1);
		shipInterface->speed(0);
		return;
	}
	else if (pattern == 3) {
		shipInterface->roll(-1);
		shipInterface->yaw(-1);
		shipInterface->pitch(-1);
		shipInterface->speed(100);
		return;
	}
}

//------------------------------------------------------------------
// void flock() is only available in a single-player game.  At the 
// beginning of the game, all the ComputerPilots 'flock' for a while
// until they start attacking.
//------------------------------------------------------------------

void ComputerPilot::flock() {
	
	DoneWithLastState = false;
	
	if (shipInfo.mode != 1) {
		shipInfo.currentState = 3;
		return;
	}

	Point leaderPosition;
	Ship* current = (Ship *)(shipInfo.gameState->spaceObjects);
    
	// first find the leader to follow.  Since the pilots don't
	// really communicate with each other, each pilot's leader is
	// the one with a ship id higher than its id.  All they will do
	// when they flock, is follow the leader.
	
	
	if (leaderId == -1) {
		if (shipInfo.shipId == 1) {
			pattern();
			return;
		}
		else if (shipInfo.shipId == 2) {
			// find out if ship id == 1 is alive
			for (int i = 0; i < shipInfo.gameState->numberOfShips; i++) {	
				if (current->id == shipInfo.shipId) {
					current = (Ship*)current->next;
					continue;
				}
				else if (current->id == 1) {
					leaderId = 1;
					break;
				}
				current = (Ship*)current->next;
			}
			// if its leader is dead, then pattern();
			if (leaderId == -1) {
				pattern();
				return;
			}
	
		}
		else if (shipInfo.shipId == 3) {
			// find out if ship id == 2 is alive
			for (int i = 0; i < shipInfo.gameState->numberOfShips; i++) {
				if (current->id == shipInfo.shipId) {
					current = (Ship*)current->next;
					continue;
				}
				else if (current->id == 2) {
					leaderId = 2;
					break;
				}
				current = (Ship*)current->next;
			}
		
			// if its leader is dead, then find ship id == 1

			if (leaderId == -1) {
				for (int i = 0; i < shipInfo.gameState->numberOfShips; i++) {
					if (current->id == shipInfo.shipId) {
						current = (Ship*)current->next;
						continue;
					}
					else if (current->id == 1) {
						leaderId = 1;
						break;
					}
					current = (Ship*)current->next;
				}
				if (leaderId == -1) {
					pattern();
					return;
				}
			}
		}

	}

	// Once we've know who our leader is, we simply start following him.
	// first we find him, then we follow

	// this counter is temporary.  The computerPilot should 'stop' flocking 
	// when (1) it is being attacker or (2) the enemy ship is close by to 
	// attack it.
	
	while (counter < 300) {

		if ((isBeingAttacked())||(enemyIsClose()))
			break;

		Ship* current = (Ship *)(shipInfo.gameState->spaceObjects);
		
		for (int i = 0; i < shipInfo.gameState->numberOfShips; i++) {
			if (current->id == shipInfo.shipId) {
				current = (Ship*)current->next;
				continue;
			}
			else if (current->id == leaderId) {
				leaderPosition = current->position;
				leader = current;
				break;
			}
			current = (Ship*)current->next;
		}
	
		if (shipInfo.position.distanceTo(leaderPosition) > 1000) {
			turnToward(leaderPosition);
			if (shipInfo.speed < 60) 
				shipInterface->speed(60);
			counter++;
			return;
		}
		// else we're close enough and we just start following it.
		// figure out the matrix stuff.
		else  {
								
			if (leaderPosition.x < shipInfo.position.x)
				shipInterface->yaw(-1);
			else
				shipInterface->yaw(1);
		
			if (leaderPosition.y < shipInfo.position.y)
				shipInterface->pitch(-1);
			else
				shipInterface->pitch(1);
		
			if (leader != NULL) {
				shipInterface->speed(leader->speed);
			}
			counter++;
			return;
	
		}
	}
	counter = 0;
	DoneWithLastState = true;
}

//------------------------------------------------------------------
// void pattern() takes the pilot to 'random walks' out in space.
// 
//------------------------------------------------------------------

void ComputerPilot::pattern() {
	DoneWithLastState = false;
	while (!isBeingAttacked()||!enemyIsClose()) {
		shipInterface->pitch(random(15));
		shipInterface->yaw(random(15));
		shipInterface->roll(random(15));
		return;
	}
	DoneWithLastState = true;
}


//------------------------------------------------------------------
// Something at position origin, with speed speed wants to shoot
// a projectile with speed projectileSpeed at a target at 
// postion target, moving at speed targetSpeed.
// Returns true if the origin is a good position to shoot from
// false if not.  The postion to aim at, is saved in aimPosition.
//------------------------------------------------------------------

Point ComputerPilot::aim(Point targetPostion, int targetSpeed, Vector targetDirection,
						Point myPosition, int mySpeed, int projectileSpeed, Vector myDirection) {
	Point aimPoint(0, 0, 0); 
	
	// what's the position of the target with respect to myPosition?
	
	Vector va = targetPosition - myPosition;
	Vector vb = (targetDirection*((double)targetSpeed * 0.5))-(myDirection*((double)mySpeed * 0.5));

	double A = vb.dot(vb)-projectileSpeed*projectileSpeed;
	double B = 2.0 * va.i * vb.i + 2.0 * va.j * vb.j + 2.0 * va.k * vb.k;
	double C = va.dot(va);
	double t, t1, t2, D, rootD;

	// A == 0 is special case

	if (A == 0.0) 	{
	
		// A==0 && B==0 implies no solution 
		if (B == 0.0) return aimPoint;

		// Simple solution 
		t = (-C / B);

		// Can't shoot missiles backwards 
		if (t < 0.0) return aimPoint;
	}
	else{
		// More complicated cases 
		// Compute discriminant 
		D = B*B - 4.0*A*C;

		// D < 0 implies no solution 
		if (D < 0.0) return aimPoint;

		// D == 0 implies one solution 
		if (D == 0.0)	{
			t = -B / (2.0 * A);
			if (t <= 0.0) return aimPoint;
		}
		else {
			// Two solutions 
			rootD = sqrt (D);
			t1 = (-B + rootD) / (2.0 * A);
			t2 = (-B - rootD) / (2.0 * A);

			// We need a non-negative solution 
			if ( (t1 < 0.0) && (t2 < 0.0) ) return aimPoint;

			if (t1 < 0.0)
				t = t2;
			else if (t2 < 0.0)
				t = t1;
			else {
				// Both non-negative, choose lesser (closer to target) 
				if (t1 < t2)
					t = t1;
				else
					t = t2;
			}
		}
	}
	aimPoint = Point(vb.i*t, vb.j*t, vb.k*t);
	aimPoint += va;
	aimPoint += myPosition;
	return aimPoint;
}


//------------------------------------------------------------------
// void turnToward() turns the ComputerPilot towards point p.
// based on the code in Orbit(), but without considering theta.
//------------------------------------------------------------------

void ComputerPilot::turnToward(Point p) {

	 Vector u= (shipInfo.up);
	 Vector f= -(shipInfo.direction);
	 Vector r= u.cross(f);
	 normalize(u);
	 normalize(f);
	 normalize(r);
	
	 Point s = shipInfo.position;	         
	 
	 // Calculate the rotation plus the ships position
	  Point q(p.x - s.x, p.y - s.y, p.z - s.z);
	  
	  q = Point((r.i*q.x)+(r.j*q.y)+(r.k*q.z),
  	            (u.i*q.x)+(u.j*q.y)+(u.k*q.z),
	            (f.i*q.x)+(f.j*q.y)+(f.k*q.z)
			   );
	     
  	 bool inFront = q.z < 0;

	 double right = (180/PI)*atan2(q.x,-q.z);
	 double up = (180/PI)*atan2(q.y,sqrt(q.x * q.x + q.z * q.z));
	  
	  
	 if (inFront) {

		 if (right >= 0 ) {
			 if (right > 2) {
				if (right >= 15) {
					shipInterface->yaw(15);
				 }
				else  {
					shipInterface->yaw(30.0-(right*2.0));
				}
			 }
		 }
		 else if (right < 0) {
			 if (right < -2) {
				 if (right <= -15) {
					shipInterface->yaw(-15);
				 }
				 else  {
					shipInterface->yaw(-(30.0-right*2.0));
				}
			 }
		 }
		 
		 if (up >= 0 ) {
			 if (up > 2) {
				 if (up >= 15) {
					shipInterface->pitch(15);
				 }
				 else  {
					shipInterface->pitch(30.0-up*2.0);
				}
			 }
		 }
		 else if (up < 0) {
			 if (up  < -2) {
				 if (up <= -15) {
					shipInterface->pitch(-15);
				 }
				 else  {
					shipInterface->pitch(-(30.0-up*2.0));
				}
			 }
		 }


	 }
	 else {
     
		 // the other ship is behind us
         // set the right correctly.
		  
		if (right >= 0) {
			right = -(-180 + right);
		} 
		else {
			right = -(180 + right);
		}	
		
	   if ((right >= 0 )) {
			 if (right > 1) {
				 if (right >= 15) {
					shipInterface->yaw(15);
				 }
				else  {
					shipInterface->yaw(30.0-(right*2.0));
				}
			 }
		 }
       else if ((right < 0)) {
			 if (right < -1) {
				 if (right <= -15) {
					shipInterface->yaw(-15);
				 }
				 else  {
					shipInterface->yaw(-(30-right*2));
				}
			 }
		 }
		 
		 if ((up >= 0 )){
			 if (up > 1) {
				 if (up >= 15) {
					shipInterface->pitch(15);
				 }
				 else  {
					shipInterface->pitch(30.0-up*2.0);
				}
			 }
		 }
		 else if ((up < 0)) {
			 if (up  < -1) {
				 if (up <= -15) {
					shipInterface->pitch(-15);
				 }
				 else  {
					shipInterface->pitch(-(30-up*2));
				}
			 }
		 }


	 }
}



//------------------------------------------------------------------
// void turnAwayFrom() turns the ComputerPilot away from the 
// projectile or enemy.
// again based on the code in Orbit().
//------------------------------------------------------------------

void ComputerPilot::turnAwayFrom(Point position) {

	if (shipInfo.type == 1) {
	
		Vector v = position-shipInfo.position;
	
		normalize(v);

		double alpha = v.dot(shipInfo.right);
		double beta = v.dot(shipInfo.up);
		//Now turn away from projectile
	
		// right or left?

		if (alpha > 0.0) {
			// the projectile is to our right so
			shipInterface->yaw(-1); 
			shipInterface->roll(-1);
		}
		else {
			// the projectile is to our left so
			shipInterface->yaw(1); 
			shipInterface->roll(1);
		}

		// up or down?

		if (beta > 0.0) {
			// the projectile is above us
			shipInterface->pitch(-1);
		}
		else {
			// the enemy is below us
			shipInterface->pitch(+1);
		}
	}
	else {
	
		 Vector u= (shipInfo.up);
		 Vector f= -(shipInfo.direction);
		 Vector r= u.cross(f);
		 normalize(u);
		 normalize(f);
		 normalize(r);
	
		 Point s = shipInfo.position;	         
	 
		 // Calculate the rotation plus the ships position
		  Point q(position.x - s.x, position.y - s.y, position.z - s.z);
		  
		  q = Point((r.i*q.x)+(r.j*q.y)+(r.k*q.z),
  	            (u.i*q.x)+(u.j*q.y)+(u.k*q.z),
	            (f.i*q.x)+(f.j*q.y)+(f.k*q.z)
			   );
	     
	      bool inFront = q.z < 0;

		 double right = (180/PI)*atan2(q.x,-q.z);
		 double up = (180/PI)*atan2(q.y,sqrt(q.x * q.x + q.z * q.z));
	  
	  
		 if (inFront) {


			 if (right >= 0 ) {
				shipInterface->yaw(-15);
				shipInterface->roll(-1);
			 }
			 else if (right < 0) {
				shipInterface->yaw(15);
				shipInterface->roll(1);
			 }
		 
			 if (up >= 0 ) {
				 shipInterface->pitch(-15);
			 }
			 else if (up < 0) {
				 shipInterface->pitch(15);
			 }

		 }
		 else {
     
			 // the other ship is behind us
	      // set the right correctly.
		  
			if (right >= 0) {
				right = -(-180 + right);
			} 
			else {
				right = -(180 + right);
			}	
		
			 if (right >= 0 ) {
				shipInterface->yaw(-15);
				shipInterface->roll(-1);
			 }
			 else if (right < 0) {
				shipInterface->yaw(15);
				shipInterface->roll(1);
			 
			 }
		 
			 if (up >= 0 ) {
				 shipInterface->pitch(-15);
			 }
			 else if (up < 0) {
				 shipInterface->pitch(15);
			 }
		}
	}
}


//------------------------------------------------------------------
// bool enemyIsClose looks for an enemy withing the midrange.
// returns true if it finds one, false otherwise.
// It is used by flock and pattern.
//------------------------------------------------------------------


bool ComputerPilot::enemyIsClose() {

	Ship* current = (Ship*)(shipInfo.gameState->spaceObjects);
    
	// Single-player game:
	// Look for the enemy ships and find the closest one.
	// (find the closest convoy and the closest KeckWing, to later
	// compare how far away they are!)
	
	if (this->shipInfo.mode == 1) {
		for (int i = 0; i < shipInfo.gameState->numberOfShips; i++) {
			if (shipInfo.shipId == current->id){
				current = (Ship*)current->next;
				continue;
			}
			else {
				if ( ((strcmp(current->type,"CARGOSHIP" ) == 0)||(strcmp(current->type,"KECKWING" ) == 0))
					&& (current->position.distanceTo(shipInfo.position) < innerRadius)) {
					 closeEnemyId = current->id;
					 return true;
				}
			}				
			current = (Ship*)current->next;
		}
	}	
	else {
		for (int i = 0; i < shipInfo.gameState->numberOfShips; i++) {
			if (shipInfo.shipId == current->id) {
				current = (Ship*)current->next;
				continue;
			}
			else if (current->position.distanceTo(shipInfo.position) < midRadius) {
				 closeEnemyId = current->id;
				return true;
			}
			current = (Ship*)current->next;
		}
	}
	return false;

}

//------------------------------------------------------------------
// int isBeingAttacked() returns the attacker's ship Id or 0 if 
// the pilot is not under attack.  it is used by flock and pattern.
//------------------------------------------------------------------

bool ComputerPilot::isBeingAttacked() {

	SpaceObject* current = shipInfo.gameState->spaceObjects;
   
	// skip the ships and find projectiles
	
	for (int i = 0; i < shipInfo.gameState->numberOfShips; i++)
		current = (Ship*)current->next;

	while (current != NULL) {
		if ((strcmp(current->type,"WEAPON" ) == 0)||(strcmp(current->type,"EXPLOSION" ) == 0) && 
			(current->position.distanceTo(shipInfo.position) < innerRadius))
				return true;
		current = current->next;
	}
	
	return false; 

}

//------------------------------------------------------------------
// int chooseNextState() returns the next state in the FSM to 
// transition to. 
//------------------------------------------------------------------


int ComputerPilot::chooseNextState() {
	attackerScore = 0;
	targetScore = 0;
		
	SpaceObject* current = (Ship *)(shipInfo.gameState->spaceObjects);
    
	for (int i = 0; i < shipInfo.gameState->numberOfShips; i++) {
		if (current->id == shipInfo.shipId) {
			current = (Ship*)current->next;	
			continue;
		}
		currentTargetScore = currentAttackerScore = 0;
		
		// First calculate how close the current object is to the pilot's ship, and
		// add to the current score accordingly.

		double distance = shipInfo.position.distanceTo(current->position);

		if (distance > outterRadius) {
			currentTargetScore += OUTTER_RANGE;
			currentAttackerScore += OUTTER_RANGE;
		}
		else if (distance > midRadius) {
			currentTargetScore += MIDDLE_RANGE;
			currentAttackerScore += MIDDLE_RANGE;
		}
		else { 
			currentTargetScore += INNER_RANGE;
			currentAttackerScore += (INNER_RANGE + 10);
		}
		
		// Now check if CURRENT's direction is MY position!  
				
		currentDirection = current->direction;
		currentPosition = current->position;
	
		if ((currentDirection.i == 0)&&(currentPosition.x != shipInfo.position.x)) {
			currentTargetScore += UNAWARE_TARGET;
			currentAttackerScore += NOT_IN_ATTACK_POSITION;
		}
		else if ((currentDirection.j == 0)&&(currentPosition.y != shipInfo.position.y)) {
			currentTargetScore += UNAWARE_TARGET;
			currentAttackerScore += NOT_IN_ATTACK_POSITION;
		}
		else if ((currentDirection.k == 0)&&(currentPosition.z != shipInfo.position.z)) {
			currentTargetScore += UNAWARE_TARGET;
			currentAttackerScore += NOT_IN_ATTACK_POSITION;
		}
		else {
			double a = ((shipInfo.position.x - currentPosition.x)/currentDirection.i);
			double b = ((shipInfo.position.y - currentPosition.y)/currentDirection.j);
			double c = ((shipInfo.position.z - currentPosition.z)/currentDirection.k);
			
			if ((equal(a,b)) && (equal(b,c)) && (equal(a,c))) {
				currentTargetScore += A_THREAT;
				currentAttackerScore += IN_ATTACK_POSITION;

			}
			
			if (((Ship*)current)->firing) {
				currentAttackerScore += ATTACKING;
			}
		}
		
		// check the type of ship

		if (shipInfo.mode ==1) {
			
			if ((strcmp(current->type,"EE1" ) == 0)||(strcmp(current->type,"EE2" ) == 0)|| 
				(strcmp(current->type,"EE3" ) == 0)) {
				currentTargetScore += SHIP_CAN_NOT_ATTACK;
				currentAttackerScore += NOT_A_THREAT;
			}
	        else if ((strcmp(current->type,"CARGOSHIP" ) == 0)) {
				currentTargetScore += (SHIP_CAN_NOT_ATTACK*2);
			}
			else if (strcmp(current->type,"KECKWING") == 0) {
				currentTargetScore += SHIP_CAN_ATTACK;
				currentAttackerScore += A_THREAT;

				// how are the enemy's shields?
				if (((Ship*)current)->shields > 70) {
					currentTargetScore += ENEMY_STRONG_SHIELDS;
				}
				else if (((Ship*)current)->shields > 40) {
					currentTargetScore += ENEMY_OK_SHIELDS;
				}
				else if (((Ship*)current)->shields > 20) {
					currentTargetScore += ENEMY_LOW_SHIELDS;
				}
				else {
					currentTargetScore += ENEMY_NO_SHIELDS;
				}
				
				// their health

				if (current->life > 70) {
					currentTargetScore += ENEMY_GOOD_HEALTH;
					currentAttackerScore += ENEMY_GOOD_HEALTH;
				}
				else if (current->life > 40) {
					currentAttackerScore += ENEMY_OK_HEALTH;
					currentTargetScore += ENEMY_OK_HEALTH;
				}
				else if (current->life > 20) {
					currentAttackerScore += ENEMY_LOW_HEALTH;
					currentTargetScore += ENEMY_LOW_HEALTH;
				}
				
			}
		}
		else if (shipInfo.mode == 2) {
			if ((strcmp(current->type,"EE1" ) == 0)||(strcmp(current->type,"EE2" ) == 0)|| 
				(strcmp(current->type,"EE3" ) == 0)||(strcmp(current->type,"KECKWING" ) == 0)) {
				currentTargetScore += SHIP_CAN_ATTACK;
				currentAttackerScore += A_THREAT;
		
				// how are the enemy's shields?
				
				if (((Ship*)current)->shields > 70) {
					currentTargetScore += ENEMY_STRONG_SHIELDS;
				}
				else if (((Ship*)current)->shields > 40) {
					currentTargetScore += ENEMY_OK_SHIELDS;
				}
				else if (((Ship*)current)->shields > 20) {
					currentTargetScore += ENEMY_LOW_SHIELDS;
				}
				else {
					currentTargetScore += ENEMY_NO_SHIELDS;
				}

				if (current->life > 70) {
					currentTargetScore += ENEMY_GOOD_HEALTH;
					currentAttackerScore += ENEMY_GOOD_HEALTH;
				}
				else if (current->life > 40) {
					currentAttackerScore += ENEMY_OK_HEALTH;
					currentTargetScore += ENEMY_OK_HEALTH;
				}
				else if (current->life > 20) {
					currentAttackerScore += ENEMY_LOW_HEALTH;
					currentTargetScore += ENEMY_LOW_HEALTH;
				}

			}
		}
		// Check my shields	
		
		if (shipInfo.shields > 70) {
			currentTargetScore += STRONG_SHIELDS;
			currentAttackerScore += ENOUGH_SHIELDS;
		}
		else if (shipInfo.shields > 40) {
			currentTargetScore += OK_SHIELDS;
			currentAttackerScore += GOOD_SHIELDS;
		}
		else if (shipInfo.shields > 20) {
			currentTargetScore += WEAK_SHIELDS;
			currentAttackerScore += NOT_SO_GOOD_SHIELDS;
		}
		else {
			currentTargetScore += NO_SHIELDS;
			currentAttackerScore += NO_SHIELD_PROTECTION;
		}
		
		// after checking everything, if the currentScore is greater than the 
		// targetScore, we replace it, since we've found a better target. 
	
		if (currentTargetScore > targetScore) {
			targetScore = currentTargetScore;
			target = ((Ship*)current);
			targetPosition = current->position;
			targetDirection = current->direction;
		}
		if (currentAttackerScore > attackerScore) {
			attackerScore = currentAttackerScore;
			attacker = ((Ship*)current);
			attackerPosition = current->position;
			attackerDirection = current->direction;
		}
		
		current = (Ship*)current->next;
		
	}

	// Now, since we're done going through the ships, we
	// start to look at other space objects, such as
	// explosions and projectiles.
	// For these however, we only look at their position
	// relative to ours.  If they are close, we evade.
	
	while (current != NULL) {
		
		float distance = (shipInfo.position.distanceTo(current->position));
		if (distance < innerRadius) {
			if ((strcmp(current->type,"EXPLOSION" ) == 0)||(strcmp(current->type,"WEAPON" ) == 0)||
				(strcmp(current->type,"KECKLAB" ) == 0)) {
				attackerScore += DANGER;
				attacker = ((Ship*)current);
				attackerPosition = current->position;
				attackerDirection = current->direction;
			}
					
		}
		current = current->next;
	}


	// now evaluate scores:  if the attacker score higher, then we evade it
	// otherwise, we attack.
	
	if ((attackerScore < 100)&&(targetScore < 100)) {
		if (shipInfo.mode == 1) 
			return 4;
		else
			return 3;
	}
	else if (attackerScore > targetScore) {
		return 2;
	}
	else
		return 1;

}

//------------------------------------------------------------------
//	for the cargo ships
//------------------------------------------------------------------

void ComputerPilot::checkRoute() {
	
	if ((keckLabLocation.x == 0)&&(keckLabLocation.y == 0)&&(keckLabLocation.z == 0)) {
		Ship* current = (Ship *)(shipInfo.gameState->spaceObjects);
		
		//  find the KeckLab's position
	
		while (current != NULL) {
			if (strcmp(current->type,"KECKLAB" ) == 0) {
				keckLabLocation = current->position;
				break;
			}
			current = (Ship*)current->next;
		}
	}
	turnToward(keckLabLocation);
	shipInterface->speed(30);
}


//------------------------------------------------------------------
// think simply coordinates the ComputerPilot's actions.  It gets 
// called right after the ComputerPilot is updated by ShipInterface
// and uses all the other methods in ComputerPilot to make it run.
//------------------------------------------------------------------


void ComputerPilot::think() {
		
	if (shipInfo.type != 4) {
	
		if (DoneWithLastState) 
			shipInfo.currentState = chooseNextState();
			
		switch (shipInfo.currentState) { 

			case 1:	attack();
					break;
			case 2:	evade();
					break;
			case 3: pattern();  
					break;
			case 4: flock();	
			
		}
	}
	else {
		checkRoute();
		return;
	}

}


