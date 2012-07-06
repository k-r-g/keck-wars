/**************************************************************************
*                                                                         *
* Class Name: SetupGame                                                   *
*                                                                         *
* Author: Mihail Papadopulos                                              *
*                                                                         *
* Description: This class creates the game and contains all of the        *
*              components involved or necessary to setup and              *
*              personalize the settings for each game.                    *
*                                                                         *
* Revisions: Mihail Papadopulos - 09/20/99 - Initial Version 
*             
*            Mihail Papadopulos - 10/04/99
*
*
*                                                                         *
**************************************************************************/
#ifndef SETUPGAME_H
#define SETUPGAME_H

#include "NetworkServer.h"
#include "NetworkClient.h"
#include "SetupMenuConfiguration.h"
#include "GameStateDestination.h"
#include "GameControl.h"
#include "ShipInterface.h"
#include "FlightGraphics.h"
#include <string>
#include <iostream>
#include <process.h>
#include <conio.h>
#include <windows.h>
#include <fcntl.h>
#include <io.h>


using namespace std;
class NetworkServer;
class SetupMenuConfiguration;
struct PlayerInfo;
class GameStateDestation;

#define EXIT 0
#define GO 1
#define SERVERMODE 1
#define CLIENTMODE 2



// these defines are the value returned from UI's method to use the menus.
// If UI returns EXIT, the game exits, if they return GO, the game starts.

//_CLASSDEF(setupGame)


class SetupGame {

public:




	SetupGame(); 
	// Constructor that creates the instance of SetupGame 

	~SetupGame();
	// Destructor that releases the memory and shuts down SetupGame.
	
	void setNetworkServer(NetworkServer * networkServer);

	void setup(SetupMenuConfiguration * setupMenuConfiguration);
	// Called by Main to start setting up the game.
	// Will have a pointer to UserInterface in order to communicate.
	// Will provide UserInterface with a thread to make menus.
	
	
	void singlePlayer(int missionNumber);
	// This method will be called by UI and take the number of 
	// mission selected by the single player.
	
	void singlePlayer(char* buffer);
	// This method will be called by UI and take the number of 
	// mission selected by the single player.

	void multiPlayer(int mode, char *servername, char *playername);
	// This method will be called by UI to setup Networking.

	
	int validateClient(char* playerName);
	// Will receive a message from Networking asking if player can join.
	// This method will check if a player slot is available and will 
	// update the the playerSlot array accordingly. It will return an 
	// int back to Networking notifying which player slot was allowed.

	void openPlayerSlot(int slot);
	// This method will be called by UI in order to open a player slot.

		
	void closePlayerSlot(int slot);
	// This method will be call by UI to close a player slot that has just
	// been designated. Then it passes a string of the player back to 
	// keckPlayer(String player) in Networking.

	void createComputerPilotSlot(int slot, int type);
	// This method will be called by UI to designate one slot to be AI.
	
	void go();
	// This method will start a new game. It will call a method from
	// Game Control which will begin the game.
	// Commented on 10-03-99 because this will be returned by UI

	void endGame();

	void gsdListDestroyer(GameStateDestination *current); 

	void computerPilotDestroyer();

    void joinNetworkGame(char* servername, char* playername);
	// This is a method the Network Server can call in order to notify  
	// all the players in a networked game that a new player has joined 
	// the game. It will also display the new user's information.  
	
	void createGameControl(string fileContents, int numOfShips);
	// This method will create an instance of GameControl.

	void createShipInterface();
	// This medthod will create an instance of ShipInterface.

	void createFlightGraphics();
	// This method will create an instance of FlightGraphics.

	//void createServer(void *ch);


		struct PlayerInfo {
		PlayerInfo(){
			playerType = 0;
			AIType = 1;
		}
		char* playerName;
		int playerType;
		// This delineates the int variable associated with each 
		// type of networked player. 
		// 0 and "" delineates an open player slot. 
		// 1 = local player (human).
		// 2 = human player slot.  
		// 3 = computer pilot slot.
		// 4 = closed player slot.
		// 5 = network 

		int AIType;
		// 1 = EE1
		// 2 = EE2
		// 3 = EE3
		// 4 = CARGOSHIP
	}; 
	
	PlayerInfo* playerSlot[8];

	

protected:
	GameStateDestination *gsd;
	GameControl *gameControl;
	
	// An array of all modules the game state needs to be sent to.
	// Only needed on the Server machine.
	NetworkServer *networkServer;
	NetworkClient *networkClient;
	ComputerPilot *computerPilotArray[7];	



	ShipInterface* myShip[8];  //myShip array

	// Keeps track of everything with respects to player slots.
	
	int computerPilots;
	int totalShips;
	int localShip;
	int gameMode;
	// gameMode delineates a toggle between a single player game and a 
	// multi-player game.
	int mode;
	int clientID;
	int numOfShips;

	char *servername;
	char *playername;
	void displaySplashScreen();
	// This method initializes the game and displays a splash screen
	// Creates UserInterface	

	void determineTotalShips(); 
	// This method determines how many total ships are involved in 
	// the game. It will be able to delinate the number of human ships 
	// along with the number of computer ships and the single local 
	// ship. Using simple math, it will determine the total amount of 
	// ships, by first getting the total amount of computer ships and 
	// incrementing the computerShips field. Then it will determine the 
	// total amount of human ships by taking the totalShips - local ship-
	// computerShips.In a networked game, there will always be a single 
	// local player.


	void createNetworkClient();
	// This method will create an instance of the NetworkClient.
	//void createServer(void *ch); 
	
	void createNetworkServer();
	// This method will create an instance of the NetworkServer.
	void createComputerPilot(int playerSlot, int type, ShipInterface* si);
	// This method will create an instance of ComputerPilot.

	//void createSetupMenuConfiguration();
	// This method will create an instance of SetupMenuConfiguration.
	
/*	void createUserCombatControl(ShipInterface* si);
	// This method will create an instance of User Combat Control.

*/
	void createSoundPlayer();
	// This method will create an instance of Sound Player.

};

#endif