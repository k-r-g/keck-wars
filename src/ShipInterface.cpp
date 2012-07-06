#include "StdAfx.h"
#include "ShipInterface.h"
#include "FlightGraphics.h"
#include <iostream.h>

#define SWEETCHERRYPI 3.141592



void ShipInterface::startFire()
{
  theShip->firing = true;
}

void ShipInterface::stopFire()
{
  theShip->firing = false;
}

void ShipInterface::pitch(int movement)
{
  theShip->pitch = movement;
}

void ShipInterface::roll(int movement)
{
  theShip->roll = movement;
}

void ShipInterface::speed(int actualSpeed)
{
  theShip->speed = actualSpeed;
}

void ShipInterface::yaw(int movement)
{
  theShip->yaw = movement;
}

void ShipInterface::quit()
{
  theShip->quit = true;
}

void ShipInterface::isComputerPilotSI(ComputerPilot* cp) {
	currentAIPlayer = cp;
}

void UltimateRadarListDestroyer(Radar* deadRadar) {
	if (deadRadar != NULL) {
		if(deadRadar->next != NULL) {
			UltimateRadarListDestroyer(deadRadar->next);
		}
		delete deadRadar;
		deadRadar = NULL;
	}
}

ShipState* ShipInterface::updateGameState(GameState* gameState)
{
  if (isAIPilot)
  {
	 currentAIPlayer->update(gameState);
	 // call update in Computer Pilot
  }
  else
  {
	  //**************************
	// Begin "Combat User Control" 
	theShip->firing = getFireVal();
	theShip->yaw = getYawVal();
	theShip->pitch = getPitchVal();
	theShip->disruptors = getDisruptorVal();
	theShip->roll = getRollVal();
	theShip->pause = getPauseVal();
	theShip->speed = getAccelerateVal();
	theShip->quit = getQuitVal();
	// End "Combat User Control" 
	  //**************************

  	
	SpaceObject* currentShip = gameState->spaceObjects; 
	

	for (int i = 0; i < gameState->numberOfShips; i++)
	{
	  if (currentShip != NULL)
	  {
	    if (currentShip->id == externalID)
		{
	      if (((Ship*)currentShip)->shieldHit)
			currentSound->soundEvent(SHIELDHIT);
	      else if (((Ship*)currentShip)->hullHit)
            currentSound->soundEvent(HULLHIT);
          else if (((Ship*)currentShip)->firing)
            currentSound->soundEvent(WEAPONFIRED);		  
         
		  // Create Front radar
		 Radar* radarFrontList = new Radar();
	
		 Radar* radarFrontPointer = radarFrontList;
	
		 int radarFrontCount = 0;

		 //  Create Rear radar
		 Radar* radarRearList = new Radar();
	
		 Radar* radarRearPointer = radarRearList;
	
		 int radarRearCount = 0;

  	
		 SpaceObject* currentPointer = gameState->spaceObjects;
	
	     for (int j = 0; j < gameState->numberOfShips; j++)
		 {
	       if (currentPointer != NULL)
		   {
		     if ((!((strcmp(currentPointer->type, "WEAPON") == 0) || (strcmp(currentPointer->type, "EXPLOSION") == 0))) && currentPointer->id != externalID)
			 {
			   // found a ship - calculate radar

			   	 
				 
			   Vector u= (currentShip->up);
			   Vector f= -(currentShip->direction);
			   Vector r= u.cross(f);
			   normalize(u);
			   normalize(f);
			   normalize(r);
			   
			   Point p = currentPointer->position;
			   Point s = currentShip->position;	         
			   
			   // Calculate the rotation plus the ships position
			   Point q(p.x - s.x, p.y - s.y, p.z - s.z);
			   q = Point((r.i*q.x)+(r.j*q.y)+(r.k*q.z),
  	   	                 (u.i*q.x)+(u.j*q.y)+(u.k*q.z),
	   				     (f.i*q.x)+(f.j*q.y)+(f.k*q.z));
			
	           double right = (180/SWEETCHERRYPI)*atan2(q.x,-q.z);
	           double up = (180/SWEETCHERRYPI)*atan2(q.y,sqrt(q.x * q.x + q.z * q.z));
			   
			   //
			   // to know if the ship is in the front I need to check if Z<0.
			   //  
 			   bool inFront = q.z < 0;

			   	   
			   if (inFront == TRUE)
			   {
				 if (radarFrontCount != 0)
				 {
				   radarFrontPointer->next = new Radar();
				   radarFrontPointer = radarFrontPointer->next;
				 }
				 radarFrontCount++;
		         radarFrontPointer->rightAngle = right;
			     radarFrontPointer->upAngle = up;
			     radarFrontPointer->shipID = currentPointer->id;
			     radarFrontPointer->type = currentPointer->type;
				 radarFrontPointer->team = currentPointer->team;
				 radarFrontPointer->next = NULL;
			   }
			   //else if Z > 0
			   else if (inFront != TRUE)
			   {
				 if (radarRearCount != 0)
				 {
				   radarRearPointer->next = new Radar();
				   radarRearPointer = radarRearPointer->next;
				 }
				 radarRearCount++;
				 if (right >= 0)
				     radarRearPointer->rightAngle = -(-180 + right);
				 else radarRearPointer->rightAngle =-(180 + right);

			     
		         //radarRearPointer->rightAngle = right;
			     radarRearPointer->upAngle = up;
			     radarRearPointer->shipID = currentPointer->id;
			     radarRearPointer->type = currentPointer->type;
				 radarRearPointer->team = currentPointer->team;
				 radarRearPointer->next = NULL;
			   }
			   // else out of range of radar
			 }
			 // else not a ship - skip it
		   }
		   if (currentPointer != NULL && currentPointer->next != NULL)
             currentPointer = currentPointer->next;  //move to next ship
		 }

		 if (radarFrontCount == 0)
		   radarFrontList = NULL;

		 if (radarRearCount == 0)
		   radarRearList = NULL;
         
		 // pass gameState, id and radar to Flight Graphics 
		 updateFlightGraphics(*gameState, externalID, radarFrontList, radarRearList);
		
		 // delete radar objects 

		UltimateRadarListDestroyer(radarFrontList);
		UltimateRadarListDestroyer(radarRearList);
		 
		  break;
		}
	    else
		{
	      currentShip = currentShip->next;
		}
	  }
    }
	
  }
 
  theShip->next = NULL;
  theShip->id = externalID;
  return theShip;
   // return the current Ship State object
}