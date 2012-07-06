/**************************************************************************
* Name: Conversion                                                        *
*                                                                         *
* Author: Sean Ferguson                                                   *
*                                                                         *
* Description: This file is a collection of methods necessary for         *
*              converting the states and unconverting.  It is really      *
*			   a messy section of code since I didn't have much time to   *
*              clean it up.  But could be made shorter if I wanted to.    *
* Revisions:  Sean Ferguson -- Initial Version                            *
*             Sean Ferguson -- 11/8/1999 Working!!!                       *
*			  Sean Ferguson -- 11/10/99 Comments inserted and code done   *
/*************************************************************************/
#ifndef CONVERSION_H
#define CONVERSION_H

#include "StdAfx.h"
#include <afxsock.h>    
#include "GameState.h"
#include "GameStateDestination.h"
#include "ShipState.h"
#include <time.h>
#include <sys/types.h>
#include <sys/timeb.h>

#define GAMESTATE     "0"
#define SPACEOBJECT   "1"
#define SHIP          "2"
#define SHIPSTATE     "3"
#define NAME          "4"

#define SIZE          4000
//Size of gamestates to be sent over network
#define SHIPSSIZE     40
//Size of shipstates to be sent over network
#define PORT          6666
//The port number
#define MAXCLIENTS    8
//Max number of clients that can join a game
#define NAMESIZE      25
//Size of name sent across the network


inline char* encryptSpaceObjectFloat(char theMessage[20], float value) {
    char temp[20];
    char buffer[20];
    int next;

    next = sprintf(temp, "%f", value);
    if(next <=9 && next >= 0) {
        strcat(theMessage,"0");
        _itoa(next,buffer,10);
        strcat(theMessage,buffer);
    }
    else {
        _itoa(next,buffer,10);
        strcat(theMessage,buffer);
    }
    strcat(theMessage,temp);
    return theMessage;
}

inline char* encryptSpaceObjectInt(char theMessage[20], int value) {
    char temp[20];
    char buffer[20];
    int next;

    next = sprintf(temp, "%d", value);
    if(next <=9 && next >= 0) {
        strcat(theMessage,"0");
        _itoa(next,buffer,10);
        strcat(theMessage,buffer);
    }
    else {
        _itoa(next,buffer,10);
        strcat(theMessage,buffer);
    }
    strcat(theMessage,temp);
    return theMessage;
}

inline char* encryptSpaceObjectString(char theMessage[20], char* value) {
    char temp[20];
    char buffer[20];
    int next;

    next = sprintf(temp, "%s", value);
    if(next <=9 && next >= 0) {
        strcat(theMessage,"0");
        _itoa(next,buffer,10);
        strcat(theMessage,buffer);
    }
    else {
        _itoa(next,buffer,10);
        strcat(theMessage,buffer);
    }
    strcat(theMessage,temp);
    return theMessage;
}

inline encryptSpaceObject(Ship* space,char* theMessage) {
    if(strcmp(space->type,"WEAPON") != 0 ||
       strcmp(space->type,"DISRUPTOR") != 0) {
        strcat(theMessage,SHIP);
    }
    else {
        strcat(theMessage,SPACEOBJECT);
    }

    encryptSpaceObjectFloat(theMessage,space->damage);

    encryptSpaceObjectFloat(theMessage,space->direction.i);
    encryptSpaceObjectFloat(theMessage,space->direction.j);
    encryptSpaceObjectFloat(theMessage,space->direction.k);

    encryptSpaceObjectInt(theMessage,space->end);
    
    encryptSpaceObjectInt(theMessage,space->id);
    
    encryptSpaceObjectInt(theMessage,space->life);    
    
    encryptSpaceObjectInt(theMessage,space->origID);

    encryptSpaceObjectFloat(theMessage,space->position.x);
    encryptSpaceObjectFloat(theMessage,space->position.y);
    encryptSpaceObjectFloat(theMessage,space->position.z);

    encryptSpaceObjectInt(theMessage,space->radius);

    encryptSpaceObjectFloat(theMessage,space->right.i);
    encryptSpaceObjectFloat(theMessage,space->right.j);
    encryptSpaceObjectFloat(theMessage,space->right.k);

    encryptSpaceObjectInt(theMessage,space->speed);

    encryptSpaceObjectString(theMessage,space->type);
    
    encryptSpaceObjectFloat(theMessage,space->up.i);
    encryptSpaceObjectFloat(theMessage,space->up.j);
    encryptSpaceObjectFloat(theMessage,space->up.k);

    encryptSpaceObjectInt(theMessage,space->team);

    
    //Ship Objects if Necessary
    if(strcmp(space->type,"WEAPON") != 0 ||
       strcmp(space->type,"DISRUPTOR") != 0) {

        encryptSpaceObjectInt(theMessage,space->shieldHit);
        
        encryptSpaceObjectInt(theMessage,space->shields);

        encryptSpaceObjectInt(theMessage,space->kills);

        encryptSpaceObjectInt(theMessage,space->idOfLastAttacker);
        
        encryptSpaceObjectInt(theMessage,space->hullHit);

        encryptSpaceObjectInt(theMessage,space->firing);

        encryptSpaceObjectInt(theMessage,space->disruptors);
    }
}

inline void encryptGameState(GameState* game,char* theMessage) {
    char temp[20];
    int next;
    
    SpaceObject* space = game->spaceObjects;
    
    //GameState
    strcpy(theMessage,GAMESTATE);

    next = sprintf(temp, "%d", game->endGame);
    strcat(theMessage,temp);
    
    next = sprintf(temp, "%d", game->numberOfShips);
    strcat(theMessage,temp);

    next = sprintf(temp, "%d", game->startingNumShips);
    strcat(theMessage,temp);

    //SpaceObjects
    while(space != NULL) {
        encryptSpaceObject((Ship*)space,theMessage);
        space = space->next;
    }
    strcat(theMessage,"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");
}

inline void encryptShipState(ShipState* state,char* theMessage) {
    strcpy(theMessage,SHIPSTATE);
    
    encryptSpaceObjectInt(theMessage,state->firing);

    encryptSpaceObjectInt(theMessage,state->id);

    encryptSpaceObjectInt(theMessage,state->disruptors);

    encryptSpaceObjectInt(theMessage,state->pitch);

    encryptSpaceObjectInt(theMessage,state->quit);

    encryptSpaceObjectInt(theMessage,state->roll);

    encryptSpaceObjectInt(theMessage,state->speed);

    encryptSpaceObjectInt(theMessage,state->yaw);

    encryptSpaceObjectInt(theMessage,state->pause);
}

inline ShipState* decryptShipState(char encrypted[SHIPSSIZE], 
								   ShipState* state) {
    char decrypt[20];
    int current = 1;
    int value = 0;
    int other;

    //Firing
    lstrcpyn(decrypt,(encrypted+current),3);
    value = atoi(decrypt);
    current+=2;
    lstrcpyn(decrypt,(encrypted+current),value+1);
    other = atoi(decrypt);
    state->firing = other;
    current+=value;

    //Id
    lstrcpyn(decrypt,(encrypted+current),3);
    value = atoi(decrypt);
    current+=2;
    lstrcpyn(decrypt,(encrypted+current),value+1);
    other = atoi(decrypt);
    state->id = other;
    current+=value;

    //Disruptors
    lstrcpyn(decrypt,(encrypted+current),3);
    value = atoi(decrypt);
    current+=2;
    lstrcpyn(decrypt,(encrypted+current),value+1);
    other = atoi(decrypt);
    state->disruptors = other;
    current+=value;

    //pitch
    lstrcpyn(decrypt,(encrypted+current),3);
    value = atoi(decrypt);
    current+=2;
    lstrcpyn(decrypt,(encrypted+current),value+1);
    other = atoi(decrypt);
    state->pitch = other;
    current+=value;

    //quit
    lstrcpyn(decrypt,(encrypted+current),3);
    value = atoi(decrypt);
    current+=2;
    lstrcpyn(decrypt,(encrypted+current),value+1);
    other = atoi(decrypt);
    state->quit = other;
    current+=value;

    //roll
    lstrcpyn(decrypt,(encrypted+current),3);
    value = atoi(decrypt);
    current+=2;
    lstrcpyn(decrypt,(encrypted+current),value+1);
    other = atoi(decrypt);
    state->roll = other;
    current+=value;

    //speed
    lstrcpyn(decrypt,(encrypted+current),3);
    value = atoi(decrypt);
    current+=2;
    lstrcpyn(decrypt,(encrypted+current),value+1);
    other = atoi(decrypt);
    state->speed = other;
    current+=value;

    //yaw
    lstrcpyn(decrypt,(encrypted+current),3);
    value = atoi(decrypt);
    current+=2;
    lstrcpyn(decrypt,(encrypted+current),value+1);
    other = atoi(decrypt);
    state->yaw = other;
    current+=value;
    
    //pause
    lstrcpyn(decrypt,(encrypted+current),3);
    value = atoi(decrypt);
    current+=2;
    lstrcpyn(decrypt,(encrypted+current),value+1);
    other = atoi(decrypt);
    state->pause = other;
    current+=value;

    return state;
}

inline decryptShipObject(char encrypted[SIZE], Ship* space) {
    char decrypt[20];
    int current = 1;
    int value = 0;
    int other;
    double val;


    //damage
    lstrcpyn(decrypt,(encrypted+current),3);
    value = atoi(decrypt);
    current+=2;
    lstrcpyn(decrypt,(encrypted+current),value+1);
    val = atof(decrypt);
    space->damage = val;
    current+=value;

    //direction
    lstrcpyn(decrypt,(encrypted+current),3);
    value = atoi(decrypt);
    current+=2;
    lstrcpyn(decrypt,(encrypted+current),value+1);
    val = atof(decrypt);
    space->direction.i = val;
    current+=value;

    lstrcpyn(decrypt,(encrypted+current),3);
    value = atoi(decrypt);
    current+=2;
    lstrcpyn(decrypt,(encrypted+current),value+1);
    val = atof(decrypt);
    space->direction.j = val;
    current+=value;

    lstrcpyn(decrypt,(encrypted+current),3);
    value = atoi(decrypt);
    current+=2;
    lstrcpyn(decrypt,(encrypted+current),value+1);
    val = atof(decrypt);
    space->direction.k = val;
    current+=value;

    //end
    lstrcpyn(decrypt,(encrypted+current),3);
    value = atoi(decrypt);
    current+=2;
    lstrcpyn(decrypt,(encrypted+current),value+1);
    other = atoi(decrypt);
    space->end = other;
    current+=value;

    //id
    lstrcpyn(decrypt,(encrypted+current),3);
    value = atoi(decrypt);
    current+=2;
    lstrcpyn(decrypt,(encrypted+current),value+1);
    other = atoi(decrypt);
    space->id = other;
    current+=value;
    
    //life
    lstrcpyn(decrypt,(encrypted+current),3);
    value = atoi(decrypt);
    current+=2;
    lstrcpyn(decrypt,(encrypted+current),value+1);
    other = atoi(decrypt);
    space->life = other;
    current+=value;

    //origID
    lstrcpyn(decrypt,(encrypted+current),3);
    value = atoi(decrypt);
    current+=2;
    lstrcpyn(decrypt,(encrypted+current),value+1);
    other = atoi(decrypt);
    space->origID = other;
    current+=value;

    //position
    lstrcpyn(decrypt,(encrypted+current),3);
    value = atoi(decrypt);
    current+=2;
    lstrcpyn(decrypt,(encrypted+current),value+1);
    val = atof(decrypt);
    space->position.x = val;
    current+=value;

    lstrcpyn(decrypt,(encrypted+current),3);
    value = atoi(decrypt);
    current+=2;
    lstrcpyn(decrypt,(encrypted+current),value+1);
    val = atof(decrypt);
    space->position.y = val;
    current+=value;

    lstrcpyn(decrypt,(encrypted+current),3);
    value = atoi(decrypt);
    current+=2;
    lstrcpyn(decrypt,(encrypted+current),value+1);
    val = atof(decrypt);
    space->position.z = val;
    current+=value;

    //radius
    lstrcpyn(decrypt,(encrypted+current),3);
    value = atoi(decrypt);
    current+=2;
    lstrcpyn(decrypt,(encrypted+current),value+1);
    other = atoi(decrypt);
    space->radius = other;
    current+=value;

    //right
    lstrcpyn(decrypt,(encrypted+current),3);
    value = atoi(decrypt);
    current+=2;
    lstrcpyn(decrypt,(encrypted+current),value+1);
    val = atof(decrypt);
    space->right.i = val;
    current+=value;

    lstrcpyn(decrypt,(encrypted+current),3);
    value = atoi(decrypt);
    current+=2;
    lstrcpyn(decrypt,(encrypted+current),value+1);
    val = atof(decrypt);
    space->right.j = val;
    current+=value;

    lstrcpyn(decrypt,(encrypted+current),3);
    value = atoi(decrypt);
    current+=2;
    lstrcpyn(decrypt,(encrypted+current),value+1);
    val = atof(decrypt);
    space->right.k = val;
    current+=value;

    //speed
    lstrcpyn(decrypt,(encrypted+current),3);
    value = atoi(decrypt);
    current+=2;
    lstrcpyn(decrypt,(encrypted+current),value+1);
    other = atoi(decrypt);
    space->speed = other;
    current+=value;

    //type
    lstrcpyn(decrypt,(encrypted+current),3);
    value = atoi(decrypt);
    current+=2;
    lstrcpyn(space->type,(encrypted+current),value+1);
    current+=value;

    //up
    lstrcpyn(decrypt,(encrypted+current),3);
    value = atoi(decrypt);
    current+=2;
    lstrcpyn(decrypt,(encrypted+current),value+1);
    val = atof(decrypt);
    space->up.i = val;
    current+=value;

    lstrcpyn(decrypt,(encrypted+current),3);
    value = atoi(decrypt);
    current+=2;
    lstrcpyn(decrypt,(encrypted+current),value+1);
    val = atof(decrypt);
    space->up.j = val;
    current+=value;

    lstrcpyn(decrypt,(encrypted+current),3);
    value = atoi(decrypt);
    current+=2;
    lstrcpyn(decrypt,(encrypted+current),value+1);
    val = atof(decrypt);
    space->up.k = val;
    current+=value;

    //team
    lstrcpyn(decrypt,(encrypted+current),3);
    value = atoi(decrypt);
    current+=2;
    lstrcpyn(decrypt,(encrypted+current),value+1);
    other = atoi(decrypt);
    space->team = other;
    current+=value;

    //Ship objects if necessary
    if(encrypted[0] == '2') {

        //shieldHit
        lstrcpyn(decrypt,(encrypted+current),3);
        value = atoi(decrypt);
        current+=2;
        lstrcpyn(decrypt,(encrypted+current),value+1);
        other = atoi(decrypt);
        space->shieldHit = other;
        current+=value;

        //shields
        lstrcpyn(decrypt,(encrypted+current),3);
        value = atoi(decrypt);
        current+=2;
        lstrcpyn(decrypt,(encrypted+current),value+1);
        other = atoi(decrypt);
        space->shields = other;
        current+=value;

        //kills
        lstrcpyn(decrypt,(encrypted+current),3);
        value = atoi(decrypt);
        current+=2;
        lstrcpyn(decrypt,(encrypted+current),value+1);
        other = atoi(decrypt);
        space->kills = other;
        current+=value;

        //idOfLastAttacker
        lstrcpyn(decrypt,(encrypted+current),3);
        value = atoi(decrypt);
        current+=2;
        lstrcpyn(decrypt,(encrypted+current),value+1);
        other = atoi(decrypt);
        space->idOfLastAttacker = other;
        current+=value;

        //hullHit
        lstrcpyn(decrypt,(encrypted+current),3);
        value = atoi(decrypt);
        current+=2;
        lstrcpyn(decrypt,(encrypted+current),value+1);
        other = atoi(decrypt);
        space->hullHit = other;
        current+=value;

        //firing
        lstrcpyn(decrypt,(encrypted+current),3);
        value = atoi(decrypt);
        current+=2;
        lstrcpyn(decrypt,(encrypted+current),value+1);
        other = atoi(decrypt);
        space->firing = other;
        current+=value;

        //disruptors
        lstrcpyn(decrypt,(encrypted+current),3);
        value = atoi(decrypt);
        current+=2;
        lstrcpyn(decrypt,(encrypted+current),value+1);
        other = atoi(decrypt);
        space->disruptors = other;
        current+=value;
    }

    return current;
}

inline GameState* decryptGameState(char encrypted[SIZE]) {
    GameState* game = new GameState();
    
    Ship* ship = new Ship();
  
    game->spaceObjects = (SpaceObject*)ship;

    char decrypt[20];
    int current = 1;
    int value = 0;

    //GameState

    //endGame
    lstrcpyn(decrypt,(encrypted+current),2);
    bool endGame = atoi(decrypt);
    game->endGame = endGame;
    current++;

    //numberOfShips
    lstrcpyn(decrypt,(encrypted+current),2);
    value = atoi(decrypt);
    game->numberOfShips = value;
    current++;

    //startingNumShips
    lstrcpyn(decrypt,(encrypted+current),2);
    value = atoi(decrypt);
    game->startingNumShips = value;
    current++;

    while(encrypted[current] != 'X') {
        value = decryptShipObject((encrypted+current),ship);
        current+= value;
        if(encrypted[current] == 'X') {
            ship->next = NULL;
            break;
        }
        else {
            ship->next = new Ship();
            ship = (Ship*)ship->next;
        }
        if(current > SIZE) {
            AfxMessageBox("We went to big in coversion of string to gamestate" , MB_OK);  
        }
    }
    return game;
}

inline void destroyShipStateList(ShipState* current) {
	if (current->next != NULL){
		destroyShipStateList(current->next); 
		// FIX: try to make tail recursive (may be impossible)
	}
	delete current;
	current = NULL;
}

inline void destroySpaceObjectList(SpaceObject* current) {
	if (current->next != NULL) {
		destroySpaceObjectList(current->next); 
		// FIX: try to make tail recursive (may be impossible)
	}
	delete current;
	current = NULL;
}

inline void copyShipState(ShipState* current,ShipState* ship) {
	ship->firing = current->firing;
	ship->pitch = current->pitch;
	ship->quit = current->quit;
	ship->roll = current->roll;
	ship->speed = current->speed;
	ship->yaw = current->yaw;
    ship->id = current->id;
    ship->next = NULL;
}

inline void copyShipObject(Ship* current,Ship* newShip) {
    newShip->damage = current->damage;
    newShip->direction = current->direction;
    newShip->end = current->end;
    newShip->firing = current->firing;
    newShip->hullHit = current->hullHit;
    newShip->id = current->id;
    newShip->idOfLastAttacker = current->idOfLastAttacker;
    newShip->kills = current->kills;
    newShip->life = current->life;
    newShip->next = current->next;
    newShip->origID = current->origID;
    newShip->position = current->position;
    newShip->radius = current->radius;
    newShip->right = current->right;
    newShip->shieldHit = current->shieldHit;
    newShip->shields = current->shields;
    newShip->speed = current->speed;
    strcpy(newShip->type, current->type);
    newShip->up = current->up;
}

inline void copyGameState(GameState* current, GameState* newGameState) {
    newGameState->endGame = current->endGame;
    newGameState->numberOfShips = current->numberOfShips;
    newGameState->startingNumShips = current->startingNumShips;
    newGameState->spaceObjects = current->spaceObjects;
}


inline char* timer() {
   struct _timeb timebuffer;
   char *timeline = (char*)malloc(100);
   char* output = (char*)malloc(100);

   _ftime( &timebuffer );
   timeline = ctime( & ( timebuffer.time ) );
   sprintf(output, "The time is %.19s.%hu\n", timeline, timebuffer.millitm);
   return output;
}

#endif
