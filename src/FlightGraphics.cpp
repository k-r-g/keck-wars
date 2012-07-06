/**************************************************************************
*                                                                         *
* Name:         FlightGraphics.cpp                                        *
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
#include "StdAfx.h"
#include <process.h>
#include <stdlib.h>
#include <winuser.h>
#include "FlightGraphics.h"
#include "CameraShip.h"
#include "ee1.h"
#include "ee2.h"
#include "ee3.h"
#include "cargoship.h"
#include "keckstation.h"
#include "keckwing.h"

// When defining the orthographic projection for 2-D drawing of the cockpit
// this is the virtual "grid" I work with, independent of the screen
// resolution and so keeping things visible on the screen in different
// resolutions
#define ORTHOWIDTH 320
#define ORTHOHEIGHT 240


// Diplay list handles:
GLint ee1;
GLint ee2;
GLint ee3;
GLint cargoShip;
GLint keckStation;
GLint keckWing;
GLint stars;

int theWindow;
// Handle to the window opened by GLUT

int messageNumber = 0;
// An ID number for each message that is displayed in the cockpit, to
// facilitate clearing old messages

bool setNumShips = false;
// Starting number of ships, for targeting purposes

bool continueLookingForSelf = true;
// Flag to see if necessary to continue looking through the game state
// for the player's ship to determine Ship info about the player's ship


const double angle = 0.05;  
// The angle grain that the camera turns when in loose camera mode

const double deltaSpeed = 5.0; 
// The accelearation grain that the camera accelerates by in loose 
// camera mode

static bool looseCamera = false;
// Whether in loose camera mode or not

static bool enableMouse = false;
// Whether mouse control is enabled

char writeBuffer[64];
// The text to be written to the screen

char currentMessage[64];
// The message sent from GameControl to appear on the screen

char gameBuf[20];
// The string passed into GLUT Game Mode to set the screen resolution
// during the game

static GLfloat frontRadarGrid[37][37][4];
static GLfloat  rearRadarGrid[37][37][4];
// The radar matrices storing the radar information to be displayed

CameraShip cameraShip(Point(-1000, 0, 0));
// The separate little ship class used to control the camera while in
// loose camera mode

int WindowWidth = 1024;
int WindowHeight = 768;
// Initialized to the default window starting size, but updated with
// window resizing to dynamically format positioning of cockpit info
// on the screen

// Mouse struct to store information about the cursor's position
struct
{
	int left, right, up, down;
	int x, y;
	int flipx;
	int flipy;
} mouse;


// Mouse position variables:
int oldx;
int oldy;
int mouse_x, mouse_y;
int last_mouse_x, last_mouse_y;


int getPitchVal()
{
	return (pitchVal);// * getRateState());
}


int getYawVal()
{
	return (yawVal);// * getRateState());
}


int getRollVal()
{
	return (rollVal);// * getRateState());
}


int getAccelerateVal()
{
	return accelerateVal;
}


bool getFireVal()
{
	return weapons[CHIPS];
}


bool getDisruptorVal()
{
	return weapons[DISRUPTOR];
}


bool getQuitVal()
{
	return quitVal;
}


bool getPauseVal()
{
	bool tempPause = pauseVal;
	pauseVal = false;
	return tempPause;
}


void randomizeStar(Vector* star)
{
	star->i = rand() % 50;
	if (star->i == 0)
		star->i = rand() % 50;
	star->j = rand() % 50;
	if (star->j == 0)
		star->j = rand() % 50;
	star->k = rand() % 50;
	if (star->k == 0)
		star->k = rand() % 50;
}


GLint GenStars()
{
	Vector* currentStar = new Vector();

	GLint lid=glGenLists(8);
	glNewList(lid, GL_COMPILE);
		glPointSize(1);  // Make stars 1 pixel in size
		glColor4f(0.9, 0.9, 0.9, 0.0);
	    glBegin (GL_POINTS);
			for (int i = 0; i<1000; i++)
			{
				// Give stars a range of brightness
				if (i < 20)
					glColor4f(1.0, 1.0, 1.0, 0.0);
				else if (i < 50)
					glColor4f(0.9, 0.9, 0.9, 0.0);
				else if (i < 100)
					glColor4f(0.8, 0.8, 0.8, 0.0);
				else if (i < 400)
					glColor4f(0.7, 0.7, 0.7, 0.0);
				else if (i < 600)
					glColor4f(0.6, 0.6, 0.6, 0.0);
				else if (i < 900)
					glColor4f(0.5, 0.5, 0.5, 0.0);
				else 
					glColor4f(0.4, 0.4, 0.4, 0.0);

				// Force a star to be drawn in each of the eight "octants" of 3-D space
				randomizeStar(currentStar);
				glVertex4d ( currentStar->i,  currentStar->j,  currentStar->k, 0.01);

				randomizeStar(currentStar);
				glVertex4d ( currentStar->i,  currentStar->j, -currentStar->k, 0.01);

				randomizeStar(currentStar);
				glVertex4d ( currentStar->i, -currentStar->j,  currentStar->k, 0.01);

				randomizeStar(currentStar);
				glVertex4d ( currentStar->i, -currentStar->j, -currentStar->k, 0.01);

				randomizeStar(currentStar);
				glVertex4d (-currentStar->i,  currentStar->j,  currentStar->k, 0.01);

				randomizeStar(currentStar);
				glVertex4d (-currentStar->i,  currentStar->j, -currentStar->k, 0.01);

				randomizeStar(currentStar);
				glVertex4d (-currentStar->i, -currentStar->j,  currentStar->k, 0.01);

				randomizeStar(currentStar);
				glVertex4d (-currentStar->i, -currentStar->j, -currentStar->k, 0.01);
			}
			delete currentStar;
		glEnd ();
	glEndList();
	return lid;
}


int getRateState()
{
	if (GetKeyState(VK_CONTROL) < 0) 
	{
		return 2;
	}
	else if (GetKeyState(VK_SHIFT) < 0)
	{
		return 4;
	}
	else return 15;
}


void key(unsigned char key, int, int)
{
	if (timeToQuit)
	{
		glutDestroyWindow(theWindow); 
		displaySpaceObjects = NULL; 
		setDisplay = false; 
		quitVal = false; 
		timeToQuit = false;
		sprintf (currentMessage, "");

		weaponChoice = CHIPS;  // Set default weapon to CHIPS
		targetedShip = -1;
		numTargets = 0;
		targetShields = 0;
		targetHull = 0;
		targetSpeed = 0;
		targetType = "";
		targetDistance = 0.0;
		setDisplay = false;

		playerPosition = (0.0, 0.0, 0.0);     
		playerForward;     
		playerUp;          
		playerRight;       
		playerID = 0;
		playerSpeed = 0;
		playerShields = 0;
		playerHull = 0;
		playerFrags = 0;
		playerTeam = 0;

		frontRadarList = NULL; 
		rearRadarList = NULL;

		pitchVal =0;
		yawVal =0;
		rollVal =0;
		accelerateVal =0;
		pauseVal = false;

		_endthread();
	}
	switch(key) {
		case  13: accelerateVal = targetSpeed; break;
		case '+': accelerateVal++; break;
		case '=': accelerateVal++; break;
		case '-': accelerateVal--; break;
		case '/': accelerateVal = 0; break;

		case '`': accelerateVal = 0; break;
		case '1': accelerateVal = 10; break;
		case '2': accelerateVal = 20; break;
		case '3': accelerateVal = 30; break;
		case '4': accelerateVal = 40; break;
		case '5': accelerateVal = 50; break;
		case '6': accelerateVal = 60; break;
		case '7': accelerateVal = 70; break;
		case '8': accelerateVal = 80; break;
		case '9': accelerateVal = 90; break;
		case '0': accelerateVal = 100; break;

		case  8 : accelerateVal = 100; break;
		case '\\': accelerateVal = 0;  break;
		case '[': accelerateVal = 33; break;
		case ']': accelerateVal = 66; break;

		case '.': rollVal = -1 * getRateState(); break;
		case ',': rollVal =  1 * getRateState(); break;

		case 'y': nextWeapon(); break;
		case 't': nextTarget(); break;


		case ' ': weapons[weaponChoice] = true; break;
		case 'q': quitVal = true; break;
		
		case 'l': looseCamera = !looseCamera; break;
		case 'm': enableMouse = !enableMouse; break;

		case 'f': cameraShip.setSpeed(cameraShip.getSpeed() + deltaSpeed); break;
		case 'v': cameraShip.setSpeed(cameraShip.getSpeed() - deltaSpeed); break;
		case 'r': cameraShip.setSpeed(0); break;
		case 'a': cameraShip.roll(angle); break;
		case 'd': cameraShip.roll(-angle); break;
		case 'z': cameraShip.yaw(angle); break;
		case 'c': cameraShip.yaw(-angle); break;
		case 'w': cameraShip.pitch(-angle); break;
		case 'x': cameraShip.pitch(angle);  break;
	}
}


void keyUp(unsigned char key, int, int)
{
	switch(key) {
		case ' ': weapons[weaponChoice] = false; break;
		case ',': rollVal = 0; break;
		case '.': rollVal = 0; break;
		case '+': ; break;
		case '-': ; break;
		case 'p': pauseVal = !pauseVal;
	}
}


void specialKey(int key, int, int)
{
	switch (key) {
		case GLUT_KEY_LEFT:      yawVal = -1 * getRateState(); break;
		case GLUT_KEY_RIGHT:     yawVal =  1 * getRateState(); break;
		case GLUT_KEY_UP:      pitchVal =  1 * getRateState(); break;
		case GLUT_KEY_DOWN:    pitchVal = -1 * getRateState(); break;
	}
}


void specialKeyUp(int key, int, int)
{
	switch (key) {
		case GLUT_KEY_LEFT:      if (yawVal <  0) yawVal = 0; break;
		case GLUT_KEY_RIGHT:     if (yawVal >= 0) yawVal = 0; break;
		case GLUT_KEY_UP:        if (pitchVal >= 0) pitchVal = 0; break;
		case GLUT_KEY_DOWN:      if (pitchVal <  0) pitchVal = 0; break;
	}
}

static void passiveMouse (int x, int y)
{
	// Don't bother if position hasn't changed
	if ( (x == oldx) && (y == oldy) ) return;

	if (!enableMouse) return;

	mouse.x = x;
	mouse.y = y;
}


static void activeMouse (int x, int y)
{
	// Don't bother if position hasn't changed
	if ( (x == oldx) && (y == oldy) ) return;

	if (!enableMouse) return;
	
	mouse.x = x;
	mouse.y = y;
}


static void mouseFire(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN)
		weapons[weaponChoice] = true;
	else if (state == GLUT_UP)
		weapons[weaponChoice] = false;
}


void moveMouse()
{
	if (!enableMouse) return;

	if (mouse.x > oldx) mouse.right = mouse.x - oldx;
	if (mouse.x < oldx) mouse.left  = oldx - mouse.x;
	if (mouse.y > oldy) mouse.up    = mouse.y - oldy;
	if (mouse.y < oldy) mouse.down  = oldy - mouse.y;

	if (mouse.flipx)
	{
		if (mouse.left ) yawVal = -0.5 * (double) mouse.left;
		if (mouse.right) yawVal =  0.5 * (double) mouse.right;
	}
	else
	{
		if (mouse.left ) yawVal = -0.5 * (double) mouse.left;
		if (mouse.right) yawVal =  0.5 * (double) mouse.right;
	}

	if (mouse.flipy)
	{
		if (mouse.up   ) pitchVal = -0.5 * (double) mouse.up;
		if (mouse.down ) pitchVal =  0.5 * (double) mouse.down;
	}
	else
	{
		if (mouse.up   ) pitchVal = -0.5 * (double) mouse.up;
		if (mouse.down ) pitchVal =  0.5 * (double) mouse.down;
	}
	mouse.left  = 0;
	mouse.right = 0;
	mouse.up    = 0;
	mouse.down  = 0;

	oldx = WindowWidth / 2;
	oldy = WindowHeight/ 2;
	if (!quitVal)
		glutWarpPointer (oldx, oldy);
	mouse.x = oldx;
	mouse.y = oldy;
}


void createList(char* shipName, float size, int shipID, bool target)
{
	if (target && (strcmp(shipName, "EXPLOSION") != 0))
	{
		glColor4d(0.5, 0.5, 0.0, 0.0); 
		GLfloat ship_specular_material[] = {0.5, 0.5, 0.0, 1.0};
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, ship_specular_material);
		GLfloat ship_material[] = {0.5, 0.5, 0.0, 1.0};
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, ship_material);
		glPushMatrix();
		glutWireCube(size);
		glPopMatrix();
	}
	if (strcmp(shipName, "KECKWING") == 0)
	{
		glColor4d(1.0, 0.18, 0.07, 0.0); 
		GLfloat ship_specular_material[] = {1.0, 0.18, 0.07, 1.0};
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, ship_specular_material);
		GLfloat ship_material[] = {1.0, 0.18, 0.07, 1.0};
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, ship_material);
		glScaled((GLdouble)size, (GLdouble)size, (GLdouble)size);
		glRotatef(-90.0, 0.0, 1.0, 0.0);
		glCallList(keckWing);
	}
	else if (strcmp(shipName, "EE1") == 0)
	{
		glColor4d(0.05, 1.0, 0.0, 0.0);
		GLfloat ship_specular_material[] = {0.05, 1.0, 0.0, 1.0};
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, ship_specular_material);
		GLfloat ship_material[] = {0.05, 1.0, 0.0, 1.0};
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, ship_material);
		glScaled((GLdouble)size, (GLdouble)size, (GLdouble)size);
		glCallList(ee1);
	}
	else if (strcmp(shipName, "EE2") == 0)
	{
		glColor4d(0.008, 0.29, 0.79, 0.0);
		GLfloat ship_specular_material[] = {0.008, 0.29, 0.79, 1.0};
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, ship_specular_material);
		GLfloat ship_material[] = {0.008, 0.29, 0.79, 1.0};
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, ship_material);
		glScaled((GLdouble)size, (GLdouble)size, (GLdouble)size);
		glCallList(ee2);
	}
	else if (strcmp(shipName, "EE3") == 0)
	{
		glColor4d(1.0, 0.0, 0.56, 0.0);
		GLfloat ship_specular_material[] = {1.0, 0.0, 0.56, 1.0};
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, ship_specular_material);
		GLfloat ship_material[] = {1.0, 0.0, 0.56, 1.0};
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, ship_material);
		glScaled((GLdouble)size, (GLdouble)size, (GLdouble)size);
		glCallList(ee3);
	}
	else if (strcmp(shipName, "CARGOSHIP") == 0)
	{
		glColor4d(1.0, 0.78, 0.0, 0.0);
		GLfloat ship_specular_material[] = {1.0, 0.78, 0.0, 1.0};
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, ship_specular_material);
		GLfloat ship_material[] = {1.0, 0.78, 0.0, 1.0};
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, ship_material);
		glScaled((GLdouble)size, (GLdouble)size, (GLdouble)size);
		glRotatef(-90.0, 0.0, 1.0, 0.0);
		glCallList(cargoShip);
	}
	else if (strcmp(shipName, "EXPLOSION") == 0)
	{
		glColor4d(1.0, 0.42, 0.113, 0.0);
		GLfloat ship_specular_material[] = {1.0, 0.42, 0.113, 1.0};
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, ship_specular_material);
		GLfloat ship_material[] = {1.0, 0.42, 0.113, 1.0};
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, ship_material);
		glutSolidSphere((GLdouble)size, 10, 10);
	}
	else if (strcmp(shipName, "WEAPON") == 0)
	{
		glColor4d(1.0, 0.0, 0.0, 0.0);
		GLfloat ship_specular_material[] = {1.0, 0.0, 0.0, 1.0};
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, ship_specular_material);
		GLfloat ship_material[] = {1.0, 0.0, 0.0, 1.0};
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, ship_material);
		glutSolidCone(0.1*(GLdouble)size, 0.3*(GLdouble)size, 10, 10);
		glRotatef(180.0, 0.0, 1.0, 0.0);
		glutSolidCone(0.1*(GLdouble)size, 6*(GLdouble)size, 10, 10);

	}
	else if (strcmp(shipName, "DISRUPTOR") == 0)
	{
		glColor4d(1.0, 1.0, 0.0, 0.0);
		GLfloat ship_specular_material[] = {1.0, 1.0, 0.0, 1.0};
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, ship_specular_material);
		GLfloat ship_material[] = {1.0, 1.0, 0.0, 1.0};
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, ship_material);
		glRotatef(180.0, 0.0, 1.0, 0.0);
		glScaled((GLdouble)size*0.1, (GLdouble)size*0.1, (GLdouble)size*0.1);
		glutWireDodecahedron();
	}
	else if (strcmp(shipName, "KECKLAB") == 0)
	{
		glColor4d(0.0, 0.0, 1.0, 0.0);
		GLfloat ship_specular_material[] = {0.0, 0.0, 1.0, 1.0};
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, ship_specular_material);
		GLfloat ship_material[] = {0.0, 0.0, 1.0, 1.0};
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, ship_material);
		glScaled((GLdouble)size, (GLdouble)size, (GLdouble)size);
		glRotatef(-90.0, 0.0, 1.0, 0.0);
		glCallList(keckStation);
	}
	else // Who knows what it is?  Draw a gray sphere instead.
	{
		glColor4d(0.7, 0.7, 0.7, 0.0);
		GLfloat ship_specular_material[] = {0.7, 0.7, 0.7, 1.0};
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, ship_specular_material);
		GLfloat ship_material[] = {0.7, 0.7, 0.7, 1.0};
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, ship_material);
		glutWireSphere(5.0, 10, 10);
	}
}


void updateRadar()
{
	int v = 0;
	int h = 0;

	// Make empty radar spots a faded blue...
	for (int m=0; m<37; m++)
	{
		for (int n=0; n<37; n++)
		{
			frontRadarGrid[m][n][0] = 0.1;
			frontRadarGrid[m][n][1] = 0.1;
			frontRadarGrid[m][n][2] = 0.2;
			frontRadarGrid[m][n][3] = 0.0;

			rearRadarGrid[m][n][0] = 0.1;
			rearRadarGrid[m][n][1] = 0.1;
			rearRadarGrid[m][n][2] = 0.2;
			rearRadarGrid[m][n][3] = 0.0;
		}
	}

	// Put faint gray crosshairs over the radar screens
	for (m=0; m<37; m++)
	{
		frontRadarGrid[m][18][0] = 0.2;
		frontRadarGrid[m][18][1] = 0.2;
		frontRadarGrid[m][18][2] = 0.2;
		frontRadarGrid[m][18][3] = 0.0;

		frontRadarGrid[18][m][0] = 0.2;
		frontRadarGrid[18][m][1] = 0.2;
		frontRadarGrid[18][m][2] = 0.2;
		frontRadarGrid[18][m][3] = 0.0;

		rearRadarGrid[m][18][0] = 0.2;
		rearRadarGrid[m][18][1] = 0.2;
		rearRadarGrid[m][18][2] = 0.2;
		rearRadarGrid[m][18][3] = 0.0;

		rearRadarGrid[18][m][0] = 0.2;
		rearRadarGrid[18][m][1] = 0.2;
		rearRadarGrid[18][m][2] = 0.2;
		rearRadarGrid[18][m][3] = 0.0;
	}

	// First the front radar screen...
	while(frontRadarList != NULL)
	{
		if (frontRadarList->upAngle > -2.5 && frontRadarList->upAngle <= 2.5)
			v = 18;
		else if (frontRadarList->upAngle > 2.5 && frontRadarList->upAngle <= 7.5)
			v = 17;
		else if (frontRadarList->upAngle > 7.5 && frontRadarList->upAngle <= 12.5)
			v = 16;
		else if (frontRadarList->upAngle > 12.5 && frontRadarList->upAngle <= 17.5)
			v = 15;
		else if (frontRadarList->upAngle > 17.5 && frontRadarList->upAngle <= 22.5)
			v = 14;
		else if (frontRadarList->upAngle > 22.5 && frontRadarList->upAngle <= 27.5)
			v = 13;
		else if (frontRadarList->upAngle > 27.5 && frontRadarList->upAngle <= 32.5)
			v = 12;
		else if (frontRadarList->upAngle > 32.5 && frontRadarList->upAngle <= 37.5)
			v = 11;
		else if (frontRadarList->upAngle > 37.5 && frontRadarList->upAngle <= 42.5)
			v = 10;
		else if (frontRadarList->upAngle > 42.5 && frontRadarList->upAngle <= 47.5)
			v =  9;
		else if (frontRadarList->upAngle > 47.5 && frontRadarList->upAngle <= 52.5)
			v =  8;
		else if (frontRadarList->upAngle > 52.5 && frontRadarList->upAngle <= 57.5)
			v =  7;
		else if (frontRadarList->upAngle > 57.5 && frontRadarList->upAngle <= 62.5)
			v =  6;
		else if (frontRadarList->upAngle > 62.5 && frontRadarList->upAngle <= 67.5)
			v =  5;
		else if (frontRadarList->upAngle > 67.5 && frontRadarList->upAngle <= 72.5)
			v =  4;
		else if (frontRadarList->upAngle > 72.5 && frontRadarList->upAngle <= 77.5)
			v =  3;
		else if (frontRadarList->upAngle > 77.5 && frontRadarList->upAngle <= 82.5)
			v =  2;
		else if (frontRadarList->upAngle > 82.5 && frontRadarList->upAngle <= 87.5)
			v =  1;
		else if (frontRadarList->upAngle > 87.5)
			v =  0;

		else if (frontRadarList->upAngle <= -2.5 && frontRadarList->upAngle > -7.5)
			v = 19;
		else if (frontRadarList->upAngle <= -7.5 && frontRadarList->upAngle > -12.5)
			v = 20;
		else if (frontRadarList->upAngle <= -12.5 && frontRadarList->upAngle > -17.5)
			v = 21;
		else if (frontRadarList->upAngle <= -17.5 && frontRadarList->upAngle > -22.5)
			v = 22;
		else if (frontRadarList->upAngle <= -22.5 && frontRadarList->upAngle > -27.5)
			v = 23;
		else if (frontRadarList->upAngle <= -27.5 && frontRadarList->upAngle > -32.5)
			v = 24;
		else if (frontRadarList->upAngle <= -32.5 && frontRadarList->upAngle > -37.5)
			v = 25;
		else if (frontRadarList->upAngle <= -37.5 && frontRadarList->upAngle > -42.5)
			v = 26;
		else if (frontRadarList->upAngle <= -42.5 && frontRadarList->upAngle > -47.5)
			v = 27;
		else if (frontRadarList->upAngle <= -47.5 && frontRadarList->upAngle > -52.5)
			v = 28;
		else if (frontRadarList->upAngle <= -52.5 && frontRadarList->upAngle > -57.5)
			v = 29;
		else if (frontRadarList->upAngle <= -57.5 && frontRadarList->upAngle > -62.5)
			v = 30;
		else if (frontRadarList->upAngle <= -62.5 && frontRadarList->upAngle > -67.5)
			v = 31;
		else if (frontRadarList->upAngle <= -67.5 && frontRadarList->upAngle > -72.5)
			v = 32;
		else if (frontRadarList->upAngle <= -72.5 && frontRadarList->upAngle > -77.5)
			v = 33;
		else if (frontRadarList->upAngle <= -77.5 && frontRadarList->upAngle > -82.5)
			v = 34;
		else if (frontRadarList->upAngle <= -82.5 && frontRadarList->upAngle > -87.5)
			v = 35;
		else if (frontRadarList->upAngle <= -87.5)
			v = 36;

		if (frontRadarList->rightAngle > -2.5 && frontRadarList->rightAngle <= 2.5)
			h = 18;
		else if (frontRadarList->rightAngle > 2.5 && frontRadarList->rightAngle <= 7.5)
			h = 19;
		else if (frontRadarList->rightAngle > 7.5 && frontRadarList->rightAngle <= 12.5)
			h = 20;
		else if (frontRadarList->rightAngle > 12.5 && frontRadarList->rightAngle <= 17.5)
			h = 21;
		else if (frontRadarList->rightAngle > 17.5 && frontRadarList->rightAngle <= 22.5)
			h = 22;
		else if (frontRadarList->rightAngle > 22.5 && frontRadarList->rightAngle <= 27.5)
			h = 23;
		else if (frontRadarList->rightAngle > 27.5 && frontRadarList->rightAngle <= 32.5)
			h = 24;
		else if (frontRadarList->rightAngle > 32.5 && frontRadarList->rightAngle <= 37.5)
			h = 25;
		else if (frontRadarList->rightAngle > 37.5 && frontRadarList->rightAngle <= 42.5)
			h = 26;
		else if (frontRadarList->rightAngle > 42.5 && frontRadarList->rightAngle <= 47.5)
			h = 27;
		else if (frontRadarList->rightAngle > 47.5 && frontRadarList->rightAngle <= 52.5)
			h = 28;
		else if (frontRadarList->rightAngle > 52.5 && frontRadarList->rightAngle <= 57.5)
			h = 29;
		else if (frontRadarList->rightAngle > 57.5 && frontRadarList->rightAngle <= 62.5)
			h = 30;
		else if (frontRadarList->rightAngle > 62.5 && frontRadarList->rightAngle <= 67.5)
			h = 31;
		else if (frontRadarList->rightAngle > 67.5 && frontRadarList->rightAngle <= 72.5)
			h = 32;
		else if (frontRadarList->rightAngle > 72.5 && frontRadarList->rightAngle <= 77.5)
			h = 33;
		else if (frontRadarList->rightAngle > 77.5 && frontRadarList->rightAngle <= 82.5)
			h = 33;
		else if (frontRadarList->rightAngle > 82.5 && frontRadarList->rightAngle <= 87.5)
			h = 35;
		else if (frontRadarList->rightAngle > 87.5)
			h = 36;

		else if (frontRadarList->rightAngle <= -2.5 && frontRadarList->rightAngle > -7.5)
			h = 17;
		else if (frontRadarList->rightAngle <= -7.5 && frontRadarList->rightAngle > -12.5)
			h = 16;
		else if (frontRadarList->rightAngle <= -12.5 && frontRadarList->rightAngle > -17.5)
			h = 15;
		else if (frontRadarList->rightAngle <= -17.5 && frontRadarList->rightAngle > -22.5)
			h = 14;
		else if (frontRadarList->rightAngle <= -22.5 && frontRadarList->rightAngle > -27.5)
			h = 13;
		else if (frontRadarList->rightAngle <= -27.5 && frontRadarList->rightAngle > -32.5)
			h = 12;
		else if (frontRadarList->rightAngle <= -32.5 && frontRadarList->rightAngle > -37.5)
			h = 11;
		else if (frontRadarList->rightAngle <= -37.5 && frontRadarList->rightAngle > -42.5)
			h = 10;
		else if (frontRadarList->rightAngle <= -42.5 && frontRadarList->rightAngle > -47.5)
			h =  9;
		else if (frontRadarList->rightAngle <= -47.5 && frontRadarList->rightAngle > -52.5)
			h =  8;
		else if (frontRadarList->rightAngle <= -52.5 && frontRadarList->rightAngle > -57.5)
			h =  7;
		else if (frontRadarList->rightAngle <= -57.5 && frontRadarList->rightAngle > -62.5)
			h =  6;
		else if (frontRadarList->rightAngle <= -62.5 && frontRadarList->rightAngle > -67.5)
			h =  5;
		else if (frontRadarList->rightAngle <= -67.5 && frontRadarList->rightAngle > -72.5)
			h =  4;
		else if (frontRadarList->rightAngle <= -72.5 && frontRadarList->rightAngle > -77.5)
			h =  3;
		else if (frontRadarList->rightAngle <= -77.5 && frontRadarList->rightAngle > -82.5)
			h =  2;
		else if (frontRadarList->rightAngle <= -82.5 && frontRadarList->rightAngle > -87.5)
			h =  1;
		else if (frontRadarList->rightAngle <= -87.5)
			h =  0;

		if (frontRadarList->shipID == targetedShip)
		{
			frontRadarGrid[v][h][0] = 1.0;
			frontRadarGrid[v][h][1] = 1.0;
			frontRadarGrid[v][h][2] = 0.0;
			frontRadarGrid[v][h][3] = 0.0;
		}
		else if (frontRadarList->team == playerTeam)
		{
			frontRadarGrid[v][h][0] = 0.0;
			frontRadarGrid[v][h][1] = 1.0;
			frontRadarGrid[v][h][2] = 0.0;
			frontRadarGrid[v][h][3] = 0.0;
		}
		else
		{
			frontRadarGrid[v][h][0] = 1.0;
			frontRadarGrid[v][h][1] = 0.0;
			frontRadarGrid[v][h][2] = 0.0;
			frontRadarGrid[v][h][3] = 0.0;
		}
		frontRadarList = frontRadarList->next;
	}

	// Now the rear radar screen...
	while(rearRadarList != NULL)
	{
		if (rearRadarList->upAngle > -2.5 && rearRadarList->upAngle <= 2.5)
			v = 18;
		else if (rearRadarList->upAngle > 2.5 && rearRadarList->upAngle <= 7.5)
			v = 17;
		else if (rearRadarList->upAngle > 7.5 && rearRadarList->upAngle <= 12.5)
			v = 16;
		else if (rearRadarList->upAngle > 12.5 && rearRadarList->upAngle <= 17.5)
			v = 15;
		else if (rearRadarList->upAngle > 17.5 && rearRadarList->upAngle <= 22.5)
			v = 14;
		else if (rearRadarList->upAngle > 22.5 && rearRadarList->upAngle <= 27.5)
			v = 13;
		else if (rearRadarList->upAngle > 27.5 && rearRadarList->upAngle <= 32.5)
			v = 12;
		else if (rearRadarList->upAngle > 32.5 && rearRadarList->upAngle <= 37.5)
			v = 11;
		else if (rearRadarList->upAngle > 37.5 && rearRadarList->upAngle <= 42.5)
			v = 10;
		else if (rearRadarList->upAngle > 42.5 && rearRadarList->upAngle <= 47.5)
			v =  9;
		else if (rearRadarList->upAngle > 47.5 && rearRadarList->upAngle <= 52.5)
			v =  8;
		else if (rearRadarList->upAngle > 52.5 && rearRadarList->upAngle <= 57.5)
			v =  7;
		else if (rearRadarList->upAngle > 57.5 && rearRadarList->upAngle <= 62.5)
			v =  6;
		else if (rearRadarList->upAngle > 62.5 && rearRadarList->upAngle <= 67.5)
			v =  5;
		else if (rearRadarList->upAngle > 67.5 && rearRadarList->upAngle <= 72.5)
			v =  4;
		else if (rearRadarList->upAngle > 72.5 && rearRadarList->upAngle <= 77.5)
			v =  3;
		else if (rearRadarList->upAngle > 77.5 && rearRadarList->upAngle <= 82.5)
			v =  2;
		else if (rearRadarList->upAngle > 82.5 && rearRadarList->upAngle <= 87.5)
			v =  1;
		else if (rearRadarList->upAngle > 87.5)
			v =  0;

		else if (rearRadarList->upAngle <= -2.5 && rearRadarList->upAngle > -7.5)
			v = 19;
		else if (rearRadarList->upAngle <= -7.5 && rearRadarList->upAngle > -12.5)
			v = 20;
		else if (rearRadarList->upAngle <= -12.5 && rearRadarList->upAngle > -17.5)
			v = 21;
		else if (rearRadarList->upAngle <= -17.5 && rearRadarList->upAngle > -22.5)
			v = 22;
		else if (rearRadarList->upAngle <= -22.5 && rearRadarList->upAngle > -27.5)
			v = 23;
		else if (rearRadarList->upAngle <= -27.5 && rearRadarList->upAngle > -32.5)
			v = 24;
		else if (rearRadarList->upAngle <= -32.5 && rearRadarList->upAngle > -37.5)
			v = 25;
		else if (rearRadarList->upAngle <= -37.5 && rearRadarList->upAngle > -42.5)
			v = 26;
		else if (rearRadarList->upAngle <= -42.5 && rearRadarList->upAngle > -47.5)
			v = 27;
		else if (rearRadarList->upAngle <= -47.5 && rearRadarList->upAngle > -52.5)
			v = 28;
		else if (rearRadarList->upAngle <= -52.5 && rearRadarList->upAngle > -57.5)
			v = 29;
		else if (rearRadarList->upAngle <= -57.5 && rearRadarList->upAngle > -62.5)
			v = 30;
		else if (rearRadarList->upAngle <= -62.5 && rearRadarList->upAngle > -67.5)
			v = 31;
		else if (rearRadarList->upAngle <= -67.5 && rearRadarList->upAngle > -72.5)
			v = 32;
		else if (rearRadarList->upAngle <= -72.5 && rearRadarList->upAngle > -77.5)
			v = 33;
		else if (rearRadarList->upAngle <= -77.5 && rearRadarList->upAngle > -82.5)
			v = 34;
		else if (rearRadarList->upAngle <= -82.5 && rearRadarList->upAngle > -87.5)
			v = 35;
		else if (rearRadarList->upAngle <= -87.5)
			v = 36;

		if (rearRadarList->rightAngle > -2.5 && rearRadarList->rightAngle <= 2.5)
			h = 18;
		else if (rearRadarList->rightAngle > 2.5 && rearRadarList->rightAngle <= 7.5)
			h = 17;
		else if (rearRadarList->rightAngle > 7.5 && rearRadarList->rightAngle <= 12.5)
			h = 16;
		else if (rearRadarList->rightAngle > 12.5 && rearRadarList->rightAngle <= 17.5)
			h = 15;
		else if (rearRadarList->rightAngle > 17.5 && rearRadarList->rightAngle <= 22.5)
			h = 14;
		else if (rearRadarList->rightAngle > 22.5 && rearRadarList->rightAngle <= 27.5)
			h = 13;
		else if (rearRadarList->rightAngle > 27.5 && rearRadarList->rightAngle <= 32.5)
			h = 12;
		else if (rearRadarList->rightAngle > 32.5 && rearRadarList->rightAngle <= 37.5)
			h = 11;
		else if (rearRadarList->rightAngle > 37.5 && rearRadarList->rightAngle <= 42.5)
			h = 10;
		else if (rearRadarList->rightAngle > 42.5 && rearRadarList->rightAngle <= 47.5)
			h =  9;
		else if (rearRadarList->rightAngle > 47.5 && rearRadarList->rightAngle <= 52.5)
			h =  8;
		else if (rearRadarList->rightAngle > 52.5 && rearRadarList->rightAngle <= 57.5)
			h =  7;
		else if (rearRadarList->rightAngle > 57.5 && rearRadarList->rightAngle <= 62.5)
			h =  6;
		else if (rearRadarList->rightAngle > 62.5 && rearRadarList->rightAngle <= 67.5)
			h =  5;
		else if (rearRadarList->rightAngle > 67.5 && rearRadarList->rightAngle <= 72.5)
			h =  4;
		else if (rearRadarList->rightAngle > 72.5 && rearRadarList->rightAngle <= 77.5)
			h =  3;
		else if (rearRadarList->rightAngle > 77.5 && rearRadarList->rightAngle <= 82.5)
			h =  2;
		else if (rearRadarList->rightAngle > 82.5 && rearRadarList->rightAngle <= 87.5)
			h =  1;
		else if (rearRadarList->rightAngle > 87.5)
			h =  0;

		else if (rearRadarList->rightAngle <= -2.5 && rearRadarList->rightAngle > -7.5)
			h = 19;
		else if (rearRadarList->rightAngle <= -7.5 && rearRadarList->rightAngle > -12.5)
			h = 20;
		else if (rearRadarList->rightAngle <= -12.5 && rearRadarList->rightAngle > -17.5)
			h = 21;
		else if (rearRadarList->rightAngle <= -17.5 && rearRadarList->rightAngle > -22.5)
			h = 22;
		else if (rearRadarList->rightAngle <= -22.5 && rearRadarList->rightAngle > -27.5)
			h = 23;
		else if (rearRadarList->rightAngle <= -27.5 && rearRadarList->rightAngle > -32.5)
			h = 24;
		else if (rearRadarList->rightAngle <= -32.5 && rearRadarList->rightAngle > -37.5)
			h = 25;
		else if (rearRadarList->rightAngle <= -37.5 && rearRadarList->rightAngle > -42.5)
			h = 26;
		else if (rearRadarList->rightAngle <= -42.5 && rearRadarList->rightAngle > -47.5)
			h = 27;
		else if (rearRadarList->rightAngle <= -47.5 && rearRadarList->rightAngle > -52.5)
			h = 28;
		else if (rearRadarList->rightAngle <= -52.5 && rearRadarList->rightAngle > -57.5)
			h = 29;
		else if (rearRadarList->rightAngle <= -57.5 && rearRadarList->rightAngle > -62.5)
			h = 30;
		else if (rearRadarList->rightAngle <= -62.5 && rearRadarList->rightAngle > -67.5)
			h = 31;
		else if (rearRadarList->rightAngle <= -67.5 && rearRadarList->rightAngle > -72.5)
			h = 32;
		else if (rearRadarList->rightAngle <= -72.5 && rearRadarList->rightAngle > -77.5)
			h = 33;
		else if (rearRadarList->rightAngle <= -77.5 && rearRadarList->rightAngle > -82.5)
			h = 34;
		else if (rearRadarList->rightAngle <= -82.5 && rearRadarList->rightAngle > -87.5)
			h = 35;
		else if (rearRadarList->rightAngle <= -87.5)
			h = 36;

		if (rearRadarList->shipID == targetedShip)
		{
			rearRadarGrid[v][h][0] = 1.0;
			rearRadarGrid[v][h][1] = 1.0;
			rearRadarGrid[v][h][2] = 0.0;
			rearRadarGrid[v][h][3] = 0.0;
		}
		else if (rearRadarList->team == playerTeam)
		{
			rearRadarGrid[v][h][0] = 0.0;
			rearRadarGrid[v][h][1] = 1.0;
			rearRadarGrid[v][h][2] = 0.0;
			rearRadarGrid[v][h][3] = 0.0;
		}
		else
		{
			rearRadarGrid[v][h][0] = 1.0;
			rearRadarGrid[v][h][1] = 0.0;
			rearRadarGrid[v][h][2] = 0.0;
			rearRadarGrid[v][h][3] = 0.0;
		}
		rearRadarList = rearRadarList->next;
	}
}


void drawRadar()
{
	glBegin(GL_POINTS);
		for (int i=0; i<37; i++)
		{
			for (int j=0; j<37; j++)
			{
				glColor4fv(frontRadarGrid[i][j]);
				glVertex2i(j, (ORTHOHEIGHT)-i);

				glColor4fv(rearRadarGrid[i][j]);
				glVertex2i((ORTHOWIDTH)-j, (ORTHOHEIGHT)-i);
			}
		}
	glEnd();
}


void nextTarget()
{
	int i;
	if ((targetedShip < (numTargets - 1))) // || (targetedShip == playerID))
	{
		targetedShip++;
		for (i = 0; i<numTargets; i++)
		{
			if (playerID == targetedShip) targetedShip++;
			else if (targetingList[targetedShip] == -1)	targetedShip++;
			else
				return;
		}
	}
	else
	{
		targetedShip = 0;
		for (i = 0; i<numTargets; i++)
		{
			if (playerID == targetedShip) targetedShip++;
			else if (targetingList[targetedShip] == -1)	targetedShip++;
			else
				return;
		}
	}
}


void nextWeapon()
{
	weapons[weaponChoice] = false;
	if (weaponChoice < (NUMWEAPONS - 1))
		weaponChoice++;
	else
		weaponChoice = 0;

	// Write new weapon choice
	if (weaponChoice == CHIPS)
		sprintf (currentMessage, "CHIPS selected");
	else if (weaponChoice == DISRUPTOR)
		sprintf (currentMessage, "SALT selected");
	else
		sprintf (currentMessage, "Error selecting next weapon");
	glutTimerFunc(2000, clearMessage, messageNumber);
	messageNumber++;
}


void clearMessage(int value)
{
	if (value >= messageNumber-1)
		sprintf (currentMessage, "");
}


void bitmapPrint (void *font, char *theString)
{
	int len, i;

	len = strlen (theString);
	for (i=0; i<len; i++)
	{
		glutBitmapCharacter (font, theString[i]);
	}
}


void drawCockpit()
{
    // Set up viewing matrix
	glMatrixMode (GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glMatrixMode (GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	gluOrtho2D(0, ORTHOWIDTH, 0, ORTHOHEIGHT);

	// Disable three-D stuff
	glDisable (GL_DEPTH_TEST);
	//glDisable (GL_CULL_FACE);
	glDisable (GL_LIGHTING);
	glPointSize((((WindowWidth+WindowHeight)/2)/((ORTHOWIDTH+ORTHOHEIGHT)/2))*2);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glDisable(GL_POINT_SMOOTH);
	drawRadar();
	glEnable(GL_POINT_SMOOTH);

	// Display crosshairs
	glColor3d (1.0, 1.0, 1.0);
	glRasterPos2i ((ORTHOWIDTH-3)/2, (ORTHOHEIGHT-3)/2);
	sprintf (writeBuffer, "+");
	bitmapPrint (GLUT_BITMAP_TIMES_ROMAN_24, writeBuffer);

	// Write speed
	glColor3d (0.0, 0.9, 0.0);
	glRasterPos2i (2, 2);
	sprintf (writeBuffer, "SPEED:");
	bitmapPrint (GLUT_BITMAP_TIMES_ROMAN_24, writeBuffer);
	glRasterPos2i (40, 2);
	sprintf (writeBuffer, "%d", playerSpeed);
	bitmapPrint (GLUT_BITMAP_TIMES_ROMAN_24, writeBuffer);

	// Write shields
	if (playerShields < 33)
		glColor3d (0.9, 0.0, 0.0);
	else if (playerShields < 66)
		glColor3d (0.9, 0.9, 0.2);
	else
		glColor3d (0.0, 0.9, 0.0);

	glRasterPos2i (2, 10);
	sprintf (writeBuffer, "SHIELD:");
	bitmapPrint (GLUT_BITMAP_TIMES_ROMAN_24, writeBuffer);
	glRasterPos2i (40, 10);
	sprintf (writeBuffer, "%d", playerShields);
	bitmapPrint (GLUT_BITMAP_TIMES_ROMAN_24, writeBuffer);

	// Write hull
	if (playerHull < 33)
		glColor3d (0.9, 0.0, 0.0);
	else if (playerHull < 66)
		glColor3d (0.9, 0.9, 0.2);
	else
		glColor3d (0.0, 0.9, 0.0);

	glRasterPos2i (2, 18);
	sprintf (writeBuffer, "HULL:");
	bitmapPrint (GLUT_BITMAP_TIMES_ROMAN_24, writeBuffer);
	glRasterPos2i (40, 18);
	sprintf (writeBuffer, "%d", playerHull);
	bitmapPrint (GLUT_BITMAP_TIMES_ROMAN_24, writeBuffer);

	// Write frag count
	glColor3d (0.0, 0.9, 0.0);
	glRasterPos2i (2, 26);
	sprintf (writeBuffer, "KILLS:");
	bitmapPrint (GLUT_BITMAP_TIMES_ROMAN_24, writeBuffer);
	glRasterPos2i (40, 26);
	sprintf (writeBuffer, "%d", playerFrags);
	bitmapPrint (GLUT_BITMAP_TIMES_ROMAN_24, writeBuffer);

	// Write message
		glColor3d (0.0, 0.9, 0.0);
	glRasterPos2i (ORTHOWIDTH/4, 5);
	sprintf (writeBuffer, "%s", currentMessage);
	bitmapPrint (GLUT_BITMAP_TIMES_ROMAN_24, writeBuffer);

	// Write target info
	glColor3d (0.0, 0.9, 0.0);
	glRasterPos2i (266, 52);
	sprintf (writeBuffer, "TARGET: %s #%d", targetType, targetedShip);
	bitmapPrint (GLUT_BITMAP_TIMES_ROMAN_10, writeBuffer);

	if (targetShields < 33)
		glColor3d (0.9, 0.0, 0.0);
	else if (targetShields < 66)
		glColor3d (0.9, 0.9, 0.2);
	else
		glColor3d (0.0, 0.9, 0.0);
	glRasterPos2i (266, 1);
	sprintf (writeBuffer, "SHIELD: %d", targetShields);
	bitmapPrint (GLUT_BITMAP_TIMES_ROMAN_10, writeBuffer);

	if (targetHull < 33)
		glColor3d (0.9, 0.0, 0.0);
	else if (targetHull < 66)
		glColor3d (0.9, 0.9, 0.2);
	else
		glColor3d (0.0, 0.9, 0.0);
	glRasterPos2i (266, 4);
	sprintf (writeBuffer, "HULL: %d", targetHull);
	bitmapPrint (GLUT_BITMAP_TIMES_ROMAN_10, writeBuffer);

	glColor3d (0.0, 0.9, 0.0);
	glRasterPos2i (300, 1);
	sprintf (writeBuffer, "SPEED: %d", targetSpeed);
	bitmapPrint (GLUT_BITMAP_TIMES_ROMAN_10, writeBuffer);

	glColor3d (0.0, 0.9, 0.0);
	glRasterPos2i (300, 4);
	sprintf (writeBuffer, "DIST: %d", targetDistance);
	bitmapPrint (GLUT_BITMAP_TIMES_ROMAN_10, writeBuffer);

	glMatrixMode (GL_PROJECTION);
	glPopMatrix();

	glMatrixMode (GL_MODELVIEW);
	glPopMatrix();

	// Re-enable three-D stuff
	glEnable (GL_DEPTH_TEST);
	//glEnable (GL_CULL_FACE);
	glEnable (GL_LIGHTING);
}


void display()
{
	if(setDisplay)
	{
		continueLookingForSelf = true;
		SpaceObject* findObject = displaySpaceObjects;
		while(findObject != NULL && continueLookingForSelf)
		{
				if (findObject->id == playerID)
				{
					playerPosition = findObject->position;
					playerForward  = findObject->direction;
					playerUp       = findObject->up;
					playerRight    = findObject->right;
					playerSpeed    = findObject->speed;
					playerShields  = ((Ship*)findObject)->shields;
					if (playerShields < 0) playerShields = 0;
					playerHull     = findObject->life;
					if (playerHull < 0) playerHull = 0;
					playerFrags    = ((Ship*)findObject)->kills;
					playerTeam     = findObject->team;
					//currentMessage  = ((Ship*)findObject)->message;

					continueLookingForSelf = false;
				}
				findObject = findObject->next;
		}

		moveCamera();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glColor3ub(180, 180, 180 );
		glDisable(GL_LIGHTING);
		glDisable(GL_DEPTH_TEST);
		//glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
		glPushMatrix();
		glTranslatef(playerPosition.x, playerPosition.y, playerPosition.z);
		glCallList(stars);
		glPopMatrix();

		// Set up viewing matrix
		glMatrixMode (GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
		glMatrixMode (GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();

		glColor3d (0.1, 0.1, 0.2);
		glOrtho (0.0, 320.0, 0.0, 240.0, -1.0, 1.0);
		glBegin(GL_QUADS);
			glVertex2f(320.0, 0.0);
			glVertex2f(320.0, 55.0);
			glVertex2f(265.0, 55.0);
			glVertex2f(265.0, 0.0);
		glEnd();
		glBegin(GL_QUADS);
			glVertex2f(0.0, 0.0);
			glVertex2f(0.0, 35.0);
			glVertex2f(55.0, 35.0);
			glVertex2f(55.0, 0.0);
		glEnd();

		glMatrixMode (GL_PROJECTION);
		glPopMatrix();
		glMatrixMode (GL_MODELVIEW);
		glPopMatrix();

		glEnable(GL_DEPTH_TEST);
		glDisable(GL_TEXTURE_2D);
		glEnable(GL_LIGHTING);

		SpaceObject* curObject = displaySpaceObjects;

		while(curObject != NULL)
		{	
			if (curObject->id == playerID)
			{
				if (looseCamera || (strcmp(curObject->type, "EXPLOSION") == 0))
				{
					glPushMatrix();
					glTranslatef(curObject->position.x, curObject->position.y, curObject->position.z);

					double m[16] = {
						curObject->right.i, curObject->right.j, curObject->right.k, 0,
						curObject->up.i, curObject->up.j, curObject->up.k, 0,
						curObject->direction.i, curObject->direction.j, curObject->direction.k, 0,
						0, 0, 0, 1
					};
					glMultMatrixd(m);
					createList(curObject->type, curObject->radius, curObject->id, false);
					glPopMatrix();
				}
				curObject = curObject->next;
			}
			else
			{
				if (curObject->id == targetedShip)
				{
					if ((strcmp(curObject->type, "EXPLOSION") == 0) || (targetingList[curObject->id] == -1))
					{
						targetingList[targetedShip] = -1;
						nextTarget();
					}
					else
					{
						targetingList[targetedShip] = 1;
						targetShields = ((Ship*)curObject)->shields;
						if (targetShields < 0) targetShields = 0;
						targetHull    = curObject->life;
						if (targetHull < 0) targetHull = 0;
						targetSpeed   = curObject->speed;
						targetType    = curObject->type;
						targetDistance = ((int)playerPosition.distanceTo(curObject->position)) / 10;
					}
					
					// Draw targeted ship on screen
					glPushMatrix();

					Point targetImagePos(playerPosition + (3*(unit(playerForward)) - 1.3*(unit(playerUp)) + 1.9*(unit(playerRight))));
					glTranslatef(targetImagePos.x, targetImagePos.y, targetImagePos.z);

					double m[16] = {
						curObject->right.i, curObject->right.j, curObject->right.k, 0,
						curObject->up.i, curObject->up.j, curObject->up.k, 0,
						curObject->direction.i, curObject->direction.j, curObject->direction.k, 0,
						0, 0, 0, 1
					};
					glMultMatrixd(m);
	
					createList(curObject->type, 0.4, curObject->id, false);
					glPopMatrix();
				}
				
				glPushMatrix();
				glTranslatef(curObject->position.x, curObject->position.y, curObject->position.z);

				double m[16] = {
					curObject->right.i, curObject->right.j, curObject->right.k, 0,
					curObject->up.i, curObject->up.j, curObject->up.k, 0,
					curObject->direction.i, curObject->direction.j, curObject->direction.k, 0,
					0, 0, 0, 1
				};
				glMultMatrixd(m);
				
				createList(curObject->type, curObject->radius, curObject->id, (curObject->id == targetedShip));
				glPopMatrix();
				curObject = curObject->next;
			}
		}
		drawCockpit();
		glFlush();
		glutSwapBuffers();
		setDisplay = false;
	}
	glutPostRedisplay();
}


void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	WindowWidth = w;
	WindowHeight = h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)w/(GLfloat)h, 1.0, 100000.0);
}


void moveCamera()
{
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();

	if (looseCamera)
	{
		Point at(cameraShip.getPosition() + cameraShip.getDirection());
		gluLookAt(cameraShip.getPosition().x, cameraShip.getPosition().y, cameraShip.getPosition().z, 
				  at.x, at.y, at.z, 
				  cameraShip.getVertical().i, cameraShip.getVertical().j, cameraShip.getVertical().k);
	}
	else
	{
		Point at(playerPosition + playerForward);
		gluLookAt(playerPosition.x, playerPosition.y, playerPosition.z, at.x, at.y, at.z, playerUp.i, playerUp.j, playerUp.k);
	}
	if (looseCamera) cameraShip.fly();
}


void initFlightGraphics() {
    char ch = 'A';
	_beginthread( internalInit, 0, (void *) (ch++) );
}


void internalInit(void *ch) {

	for (int i = 0; i<MAXTARGETS; i++)
	{
		targetingList[targetedShip] = 0;
	}
	
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(80, 80);
	glutInitWindowSize(WindowWidth, WindowHeight);

	sprintf(gameBuf, "1024x768:16");
	glutGameModeString(gameBuf);
    theWindow = glutEnterGameMode();

	//theWindow = glutCreateWindow("Yeeeeeehaaaaaa!");

	playerPosition=Point(0.0,0.0,0.0);
	playerForward=Vector(1.0,0.0,0.0);
	playerUp=Vector(0.0,1.0,0.0);
	playerRight=Vector(0.0,0.0,1.0);

	glutKeyboardFunc(key);
	glutKeyboardUpFunc(keyUp);
	glutSpecialFunc(specialKey);
	glutSpecialUpFunc(specialKeyUp);

	glutPassiveMotionFunc(passiveMouse);
	glutMotionFunc(activeMouse);
	glutMouseFunc(mouseFire);
	oldx = WindowWidth / 2;
	oldy = WindowHeight/ 2;
	glutWarpPointer (oldx, oldy);
	mouse.x = oldx;
	mouse.y = oldy;

	glutReshapeFunc(reshape);
	glutIdleFunc(moveMouse);
	glutDisplayFunc(display);
	glEnable(GL_POINT_SMOOTH);

	GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0};
	glShadeModel(GL_SMOOTH);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	GLfloat ambient_intensity[] = {0.6, 0.6, 0.6, 0.0};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient_intensity);
	//glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_FALSE);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	stars = GenStars();
	ee1 = GenEE1List();
	ee2 = GenEE2List();
	ee3 = GenEE3List();
	cargoShip = GenCargoShip();
	keckStation = GenKeckStation();
	keckWing = GenKeckWing();
	glutSetCursor(GLUT_CURSOR_NONE);
	glutMainLoop();
}


void updateFlightGraphics(GameState newDisplayState, int ID, Radar *newFrontRadar, Radar *newRearRadar)
{
	if (newDisplayState.endGame) 
	{
		timeToQuit = true;
		sprintf (currentMessage, "GAME OVER -- Press any key to continue");
	}
	else
	{
		displaySpaceObjects = newDisplayState.spaceObjects;
		playerID = ID;
		if (!setNumShips)
			numTargets = newDisplayState.startingNumShips; // numberOfShips;
		if (targetedShip == -1)
			nextTarget();

		frontRadarList = newFrontRadar;
		rearRadarList = newRearRadar;
		updateRadar();
		setDisplay = true;
	}
}