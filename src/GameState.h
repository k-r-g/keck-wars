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
#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "geometry.h"
class Vector;
class Plane;
class Point;
class Ray;

#define PI 3.1415926535897932384626433832795

#define STARTINGKECKWINGSHIELDS 100
#define STARTINGENEMYONESHIELDS 80
#define STARTINGENEMYTWOSHIELDS 100
#define STARTINGENEMYTHREESHIELDS 120
#define STARTINGCARGOSHIPSHIELDS 200
#define STARTINGKECKLABSHIELDS 1000

#define STARTINGSHIPLIFE 100
#define SHIPDAMAGE 20
#define SHIPRADIUS 100
#define CARGOSHIPRADIUS 250
#define SHIPTURNFACTOR 0.005
#define MAXSHIPTURNMULTIPLIER 15

#define MAXKECKWINGSPEED 10000
#define MAXENEMYONESPEED 80
#define MAXENEMYTWOSPEED 100
#define MAXENEMYTHREESPEED 120
#define MAXCARGOSHIPSPEED 30

#define KECKLABDAMAGE 20
#define KECKLABSPEED 0
#define KECKLABLIFE 100000
#define KECKLABRADIUS 1000

#define WEAPONDAMAGE 10
#define WEAPONSPEED 250
#define WEAPONLIFE 30
#define WEAPONRADIUS 20
#define DISRUPTORDAMAGE -1
#define DISRUPTORRADIUS 20

#define ENDDELAY 40
#define SHOTDELAY 5
#define DISRUPTORDELAY 20
#define SHIELDGENDELAY 15
#define SHIELDGENAMOUNT 1
#define ACCELDELAY 10

class SpaceObject{
public:

	SpaceObject(){
		next = NULL;
		this->end = false;
		this->id = -1;
		this->team = -1;
		strcpy(this->type,"");
	}

	SpaceObject(SpaceObject* obj){
		this->id = obj->id;
		this->origID = obj->origID;
		this->position.x = obj->position.x;
		this->position.y = obj->position.y;
		this->position.z = obj->position.z;
		this->direction.i = obj->direction.i;
		this->direction.j = obj->direction.j;
		this->direction.k = obj->direction.k;
		this->right.i = obj->right.i;
		this->right.j = obj->right.j;
		this->right.k = obj->right.k;
		this->up.i = obj->up.i;
		this->up.j = obj->up.j;
		this->up.k = obj->up.k;
		this->end = obj->end;
		this->life = obj->life;
		this->damage = obj->damage;
		this->radius = obj->radius;
		this->speed = obj->speed;
		this->team = obj->team;
		//this->type = obj->type;
		//this->type = (char*)( malloc(strlen(obj->type)) );
		strcpy(this->type, obj->type);

		this->next = NULL;
	}

	SpaceObject(Point position, Vector direction, Vector up, Vector right,
		char* type, int origID)
	{
		this->id = -1;
		this->origID = origID;
		this->position.x = position.x;
		this->position.y = position.y;
		this->position.z = position.z;
		this->direction.i = direction.i;
		this->direction.j = direction.j;
		this->direction.k = direction.k;
		this->up.i = up.i;
		this->up.j = up.j;
		this->up.k = up.k;
		this->right.i = right.i;
		this->right.j = right.j;
		this->right.k = right.k;
		strcpy(this->type,type);
		this->end = false;
		this->team = -1;
		if (strcmp(type,"WEAPON") == 0){
			speed = WEAPONSPEED;
			life = WEAPONLIFE;
			damage = WEAPONDAMAGE;
			radius = WEAPONRADIUS;
		}
		if (strcmp(type,"DISRUPTOR") == 0){
			speed = WEAPONSPEED;
			life = WEAPONLIFE;
			damage = DISRUPTORDAMAGE;
			radius = DISRUPTORRADIUS;
		}
		next = NULL;
	}


	int id;
	// for players, matches ShipState.id
	
	int origID;
	// Used for weapon projectiles only. Indicates which ship the shot
	// originated from.  Ships have a -1 origID.

	char type[10];
	// defines the type of the  object in space.  Possible options are:
	// KECKWING
	// EE1
	// EE2
	// EE3
	// CARGOSHIP
	// EXPLOSION
	// WEAPON
	// DISRUPTOR
	// KECKLAB

	Point position;
	// 3-D coordinates

	Vector direction;
	// The direction the object is facing

	Vector up;
	// The direction that is directly up from the object.

	Vector right;
	// The direction that is directly to the right of the object.

	int life;
	// how much damage the object can take before it is destroyed.

	float damage;
	// how much damage the object deals to objects it hits.

	int speed;
	// how fast the object is moving.

	int radius;
	// collision detection is modeled using spheres, and this indicates
	// how "big" the object is.

	SpaceObject *next;
	// The next SpaceObject in the list.

	bool end;
	int team;
};

class Ship : public SpaceObject{
public:
	Ship()
	{
		this->position = Point(0,0,0);
		this->direction = Vector(1,0,0);
		this->up = Vector(0,1,0);
		this->right = Vector(0,0,1);
		strcpy(this->type,"KECKWING");
		strcpy(this->message, "");
		this->life = STARTINGSHIPLIFE;
		this->shields = STARTINGKECKWINGSHIELDS;
		this->shieldHit = false;
		this->hullHit = false;
		this->damage = SHIPDAMAGE;
		this->radius = SHIPRADIUS;
		this->kills = 0;
		this->origID = -1;
		this->idOfLastAttacker = -1;
		this->end = false;
		this->team = -1;
        next = NULL;
	}
	
	Ship(Ship* obj){
		//SpaceObject((SpaceObject *)(obj));
		this->id = obj->id;
		this->origID = obj->origID;
		this->position.x = obj->position.x;
		this->position.y = obj->position.y;
		this->position.z = obj->position.z;
		this->direction.i = obj->direction.i;
		this->direction.j = obj->direction.j;
		this->direction.k = obj->direction.k;
		this->right.i = obj->right.i;
		this->right.j = obj->right.j;
		this->right.k = obj->right.k;
		this->up.i = obj->up.i;
		this->up.j = obj->up.j;
		this->up.k = obj->up.k;
		this->end = obj->end;
		this->life = obj->life;
		this->damage = obj->damage;
		this->radius = obj->radius;
		this->speed = obj->speed;
		this->team = obj->team;

		//this->type = (char*)( malloc(strlen(obj->type)) );
		strcpy(this->type, obj->type);

		this->shields = obj->shields;
		this->kills = obj->kills;
		this->idOfLastAttacker = obj->idOfLastAttacker;
		this->firing = obj->firing;
		this->disruptors = obj->disruptors;
		this->shieldHit = obj->shieldHit;
		this->hullHit = obj->hullHit;
		strcpy(this->message, obj->message);
		this->next = NULL;
	}

	Ship(Point position, Vector direction, Vector up, Vector right,
		char* type)
	{
		this->position.x = position.x;
		this->position.y = position.y;
		this->position.z = position.z;
		this->direction.i = direction.i;
		this->direction.j = direction.j;
		this->direction.k = direction.k;
		this->up.i = up.i;
		this->up.j = up.j;
		this->up.k = up.k;
		this->right.i = right.i;
		this->right.j = right.j;
		this->right.k = right.k;
		strcpy(this->type, type);
		this->end = false;
		this->team = -1;
        damage = SHIPDAMAGE;
		radius = SHIPRADIUS;
		life = STARTINGSHIPLIFE;
		speed = 0;
		if (strcmp(type,"KECKWING") == 0){
			shields = STARTINGKECKWINGSHIELDS;
		}
		else if (strcmp(type,"EE1") == 0){
			shields = STARTINGENEMYONESHIELDS;
		}
		else if (strcmp(type,"EE2") == 0){
			shields = STARTINGENEMYTWOSHIELDS;
		}
		else if (strcmp(type,"EE3") == 0){
			shields = STARTINGENEMYTHREESHIELDS;
		}
		else if (strcmp(type,"CARGOSHIP") == 0){
			shields = STARTINGCARGOSHIPSHIELDS;
			radius = CARGOSHIPRADIUS;
		}
		else if (strcmp(type,"KECKLAB") == 0){
			shields = STARTINGKECKLABSHIELDS;
			speed = KECKLABSPEED;
			life = KECKLABLIFE;
			damage = KECKLABDAMAGE;
			radius = KECKLABRADIUS;
		}
		firing = false;
		shieldHit = false;
		hullHit = false;
		kills = 0;
		origID = -1;
		idOfLastAttacker = -1;
		next = NULL;
	}

	inline void Ship::pitch(double angle)
	{
		direction = unit(direction * cos(angle) + up * sin(angle));
		up = right.cross(direction);
	}

	inline void Ship::roll(double angle)
	{
		right = unit(right * cos(angle) + up * sin(angle));
		up = right.cross(direction);
	}

	inline void Ship::yaw(double angle)
	{
		right = unit(right * cos(angle) + direction * sin(angle));
		direction = up.cross(right);
	}

	int shields;
	int kills;
	int idOfLastAttacker;
	bool firing;
	bool disruptors;
	bool shieldHit;
	bool hullHit;
    char message[64];
};

struct GameState{
	GameState(){}
	GameState(GameState* copy){
		numberOfShips = copy->numberOfShips;
		startingNumShips = copy->startingNumShips;
		endGame = copy->endGame;
		spaceObjects = NULL;
		SpaceObject* current = NULL;
		SpaceObject* currentCopy = copy->spaceObjects;
		for (int i=0; i<numberOfShips; i++){
			if (spaceObjects == NULL){
				spaceObjects = new Ship((Ship*)(currentCopy));
				current = spaceObjects;
			}
			else{
				 current->next = new Ship((Ship*)(currentCopy->next));
				 current = current->next;
				 currentCopy = currentCopy->next;
			}
		}
		while(currentCopy->next != NULL){
			 current->next = new SpaceObject(currentCopy->next);
			 current = current->next;
			 currentCopy = currentCopy->next;
		}
		current->next = NULL;
	}
	int numberOfShips, startingNumShips;
	// The number of ships that exist in the SpaceObjects array.  This
	// number is also the index of the first non-Ship SpaceObject.
	// Ship[] ships;
	SpaceObject *spaceObjects;
	// The first objects in this array are the ships.  
    bool endGame;
};

#endif