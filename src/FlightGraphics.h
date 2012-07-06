/**************************************************************************
*                                                                         *
* Name:         FlightGraphics.h                                          *
*                                                                         *
* Author:		Keith Gustafson                                           *
*                                                                         *
* Description:  Does all drawing to the local player's screen.  Uses the  *
*				GameState passed in by ShipInterface through              *
*				updateFlightGraphics() to draw all objects in space,      *
*				extract information to be displayed on the cockpit, and   *
*				display the information on the cockpit.  Uses radar	      *
*				information passed in by ShipInterface to draw the radar  *
*				screens.                                                  *
*                                                                         *
*				When initFlightGraphics is called, GLUT is initialized and*
*				FlightGraphics becomes ready to receive GameState updates *
*				and display the game.                                     *
*                                                                         *
*				When updateFlightGraphics is called, the display function *
*				runs and draws everything.                                *
*                                                                         *
*				The GLUT keyboard functions are used to get user input.	  *
*				ShipInterface calls functions to get the control values,  *
*				and passes these on to GameControl in a ShipState.        *
*                                                                         *
*				FlightGraphics stores a pointer to a GameState, pointers  *
*				to the two	radar screens that contains a database of     *
*				space object models.                                      *
*                                                                         *
**************************************************************************/
#ifndef FlightGraphics_h
#define FlightGraphics_h

#include "GameState.h"
#include <GL/glut.h>
#include <stdio.h>
#define NUMWEAPONS 2
#define CHIPS      0
#define DISRUPTOR  1
#define MAXTARGETS 50

// Weapon choice fields
static int weaponChoice = CHIPS;  // Set default weapon to CHIPS
static bool weapons[NUMWEAPONS];  // Create the array of weapons

// Targeting box values
static int targetingList[MAXTARGETS];
static int targetedShip = -1;
static int numTargets = 0;
static int targetShields = 0;
static int targetHull = 0;
static int targetSpeed = 0;
static char* targetType;
static int targetDistance = 0.0;

// List of space objects to display
static SpaceObject* displaySpaceObjects;										

// Semaphore for GameControl to know when display is done using 
// displaySpaceObjects
static int setDisplay = false;

// When a GameState comes in with the endgame field true, sets this
// flag so that FlightGraphics can shut itself down
static bool timeToQuit = false;

// Radar information about a ship to display it on radar screen
struct Radar{
	double upAngle; //verticalDegrees;
	double rightAngle; //horizontalDegrees;
	int shipID;
	char* type;
	int   team;
	Radar *next;
};
static Radar *frontRadarList;
static Radar *rearRadarList;

// Player's ship information
static Point  playerPosition;     
static Vector playerForward;     
static Vector playerUp;          
static Vector playerRight;       
static int    playerID = 0;
static int    playerSpeed = 0;
static int    playerShields = 0;
static int    playerHull = 0;
static int    playerFrags = 0;
static int    playerTeam = 0;

// Player's ship control values
static int  pitchVal =0;
static int  yawVal =0;
static int  rollVal =0;
static int  accelerateVal =0;
static bool quitVal = false;
static bool pauseVal = false;

// Functions called by ShipInterface to get player's ship controls
extern int  getPitchVal();
extern int  getYawVal();
extern int  getRollVal();
extern int  getAccelerateVal();
extern bool getFireVal();
extern bool getDisruptorVal();
extern bool getQuitVal();
extern bool getPauseVal();

void randomizeStar(Vector* star);
// Randomizes a given vector to generate a new star position

GLint GenStars();
// Generates the star display list

int getRateState();
// Gets the turn-rate value depending on the state of the shift and
// control keys

void key(unsigned char key, int, int);
// Handles key downs

void keyUp(unsigned char key, int, int);
// Handles key ups

void specialKey(int key, int, int);
// Handles "special" (i.e. arrow keys) key downs

void specialKeyUp(int key, int, int);
// Handles "special" (i.e. arrow keys) key ups

static void passiveMouse (int x, int y);
// Handles mouse movements when the mouse button is not down

static void activeMouse (int x, int y);
// Handles mouse movements when the mouse button is down

static void mouseFire(int button, int state, int x, int y);
// Handles mouse clicks to fire

void moveMouse();
// Uses mouse information from passiveMouse() and activeMouse() to
// update player's ship control information appropriately

void createList(char* shipName, float size, int shipID, bool target);
// Draws the specified ship at the specified size, and if it is the
// current target,
// also draws a yellow box around it.

void updateRadar();
// Updates the radar value matrices with the latest radar information
// from ShipInterface

void drawRadar();
// Using the radar matrices updated by updateRadar(), draws the radar
// screens.  Called in drawCockpit()

void nextTarget();
// Selects the next valid target

void nextWeapon();
// Selects the next valid weapon

void clearMessage(int value);
// Clears the message displayed on the HUD

void bitmapPrint (void *font, char *theString);
// Print bitmap text to GLUT window

void drawCockpit();
// Draws everything seen in the cockpit, including radar screens, 
// ship status, and the targeting box.

void display();
// The GLUT display function, called whenever the screen needs to be
// re-displayed

void reshape(int w, int h);
// The GLUT reshape function, handles reshaping of the window when in
// window-mode

void moveCamera();
// Moves the players camera depending on whether in cockpit or loose
// camera mode

extern void initFlightGraphics();
// Called by SetupGame to get FlightGraphics ready to display

void internalInit(void *ch);
// The Flight Graphics initialization function called by 
// initFlightGraphics() on a new thread so that the GLUT Main Loop 
// doesn't monopolize the game's thread.

extern void updateFlightGraphics(GameState newDisplayState, int ID, 
								 Radar *newFrontRadar, 
								 Radar *newRearRadar);
// Called by ShipInterface to pass in new GameState and radar 
// information

#endif