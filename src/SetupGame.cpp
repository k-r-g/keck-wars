/**************************************************************************
* Class Name: SetupGame                                                   *
*                                                                         *
* Author: Mihail Papadopulos                                              *
*                                                                         *
*                                                                         *
* Description: This class creates the game and contains all of the        *
*              components involved or necessary to setup and              *
*              personalize the settings for each game.                    *
*                                                                         *
* Revisions: Mihail Papadopulos - 10/28/99 - Initial Version              *
*                                                                         *
**************************************************************************/
#include "stdafx.h"
#include "SetupGame.h"
#include "GameControl.h"
#include <stdlib.h>
#include <iostream>
using namespace std;

SetupGame *thisSetupGame;
GameControl* thisGameControl;

// Constructor that creates the instance of SetupGame 
SetupGame::SetupGame(){
	networkServer = NULL;
	computerPilots = 0;
	totalShips = 0;
	localShip = 0;
	gameMode = 0;
	numOfShips = 1;
	for (int i = 0; i < 8; i++)	{
		playerSlot[i] = new PlayerInfo();
	}
	// initialized for SetupMenuConfiguration purposes
	playerSlot[0]->playerName = "Player 1"; 
	playerSlot[1]->playerName = "Player 2"; 
	playerSlot[2]->playerName = "Player 3"; 
	playerSlot[3]->playerName = "Player 4"; 
	playerSlot[4]->playerName = "Player 5"; 
	playerSlot[5]->playerName = "Player 6"; 
	playerSlot[6]->playerName = "Player 7"; 
	playerSlot[7]->playerName = "Player 8"; 

	for (i = 0; i < 7; i++)	{
		computerPilotArray[i] = NULL;
		
	}
}
	
// Destructor that releases the memory and shuts down SetupGame.
SetupGame::~SetupGame(){}

// Called by Main to start setting up the game.
// Will have a pointer to UserInterface in order to communicate.
// Will provide UserInterface with a thread to make menus.
void SetupGame::setup(SetupMenuConfiguration * setupMenuConfiguration){}

	
// This method will be called by UI and take the number of 
// mission selected by the single player.	
void SetupGame::singlePlayer(int missionNumber){

	gameMode = 1;
	int fd = 0;
	int bytesRead = 0;
	char buffer[3000];

	if (missionNumber == 1) {
		fd = open("U:\\_KeckWars\\mission1.txt", O_RDONLY);
	}
	else if (missionNumber == 2) {
		fd = open("U:\\_KeckWars\\mission2.txt", O_RDONLY);
	}
	else if (missionNumber == 3) {
		fd = open("U:\\_KeckWars\\mission3.txt", O_RDONLY);
	}
	
	bytesRead = read(fd, buffer, 3000);
	string stringBuffer = buffer;
	int startPos = 0;
	int endPos = 0;
	int currentPos = 0;
	int bytesToRead = 0;
	string myString = "";
	
	for (int j = 1; j < 8; j++) {
		closePlayerSlot(j);
	}

	for (int i = 1; myString != "VICTORY" && myString != "KECKLAB" && i <8; i++) {	
		currentPos = stringBuffer.find(":", currentPos);
		startPos = currentPos + 1;
		currentPos = stringBuffer.find(";", startPos);
		currentPos += 1;
		endPos = stringBuffer.find(":", currentPos);
		bytesToRead = endPos - currentPos;
		myString = stringBuffer.substr(currentPos, bytesToRead);

		if  (myString == "EE1") {
			createComputerPilotSlot(i, 1);
				}
		else if (myString == "EE2") {
			createComputerPilotSlot(i, 2);			
		}
		else if (myString == "EE3") {
			createComputerPilotSlot(i, 3);			
		}
		else if (myString == "CARGOSHIP"){
			createComputerPilotSlot(i, 4);			
		}
		
			
	}
	createShipInterface();   // Experiments
	createFlightGraphics();	 // "
	createGameControl(stringBuffer, numOfShips);     // "


}
	

// This method takes in the buffer which is passed by SetupMenuConfiguration
// and parses the mission file accordingly.
void SetupGame::singlePlayer(char* buffer){

	gameMode = 1;

	string stringBuffer = buffer;
	int startPos = 0;
	int endPos = 0;
	int currentPos = 0;
	int bytesToRead = 0;
	string myString = "";
	
	for (int j = 1; j < 8; j++) {
		closePlayerSlot(j);
	}

	for (int i = 1; myString != "VICTORY" && myString != "KECKLAB" && i <8; i++) {	
		currentPos = stringBuffer.find(":", currentPos);
		startPos = currentPos + 1;
		currentPos = stringBuffer.find(";", startPos);
		currentPos += 1;
		endPos = stringBuffer.find(":", currentPos);
		bytesToRead = endPos - currentPos;
		myString = stringBuffer.substr(currentPos, bytesToRead);

		if  (myString == "EE1") {
			createComputerPilotSlot(i, 1);
				}
		else if (myString == "EE2") {
			createComputerPilotSlot(i, 2);			
		}
		else if (myString == "EE3") {
			createComputerPilotSlot(i, 3);			
		}

		else if (myString == "CARGOSHIP"){
			createComputerPilotSlot(i, 4);			
		}
		
			
	}
	createShipInterface();   // Experiments
	createFlightGraphics();	 // "
	createGameControl(stringBuffer, numOfShips);     // "


}
	


// This method will be called by UI to setup Networking.
void SetupGame::multiPlayer(int mode, char *servername, char *playername){
	
	for (int i = 0; i < 8; i++)	{
		playerSlot[i] = new PlayerInfo();
	}
	// initialized for SetupMenuConfiguration purposes
	playerSlot[0]->playerName = "Player 1"; 
	playerSlot[1]->playerName = "Player 2"; 
	playerSlot[2]->playerName = "Player 3"; 
	playerSlot[3]->playerName = "Player 4"; 
	playerSlot[4]->playerName = "Player 5"; 
	playerSlot[5]->playerName = "Player 6"; 
	playerSlot[6]->playerName = "Player 7"; 
	playerSlot[7]->playerName = "Player 8"; 

	gameMode = 2;
	this->mode = mode;

	
	//Here SMC called with SERVERMODE, NULL, NULL
	if (mode == SERVERMODE) {
		if (networkServer == NULL) {
			createNetworkServer();
		}

	// these parameters should be passed in by SetupMenu
	}

	else if (mode == CLIENTMODE) {
		this->servername = servername;
		this->playername = playername;
		createNetworkClient();
		joinNetworkGame(servername, playername);
		if (clientID != -1) {
			go();
		}
	}
	else {
		throw "This is invalid mode pass into multi-player()";
	}
}
	

// Will receive a message from Networking asking if player can join.
// This method will check if a player slot is available and will 
// update the the playerSlot array accordingly. It will return a 
// boolean back to Networking notifying if the player was allowed.	
int SetupGame::validateClient(char* playerName){
	
	for (int i = 1; i < 8; i++) {
		if (playerSlot[i]->playerType == 0) {
			playerSlot[i]->playerName = playerName;
			playerSlot[i]->playerType = 2;
			numOfShips++;   //************************************
			return i;
			printf("%i\n", i);
			
		}
	}
	return -1;
}

// This method will be called by UI in order to open a player slot.
void SetupGame::openPlayerSlot(int slot){
	
	if (playerSlot[slot]->playerType == 2) {
		networkServer->kickPlayer(playerSlot[slot]->playerName);
		numOfShips--;
	}
	playerSlot[slot]->playerType = 0;
	
}


// This method will be call by UI to close a player slot that has just
// been designated. Then it passes a string of the player back to 
// keckPlayer(String player) in Networking.		
void SetupGame::closePlayerSlot(int slot){

	if (playerSlot[slot]->playerType == 2) {
		networkServer->kickPlayer(playerSlot[slot]->playerName);
		numOfShips--;
//		playerSlot[slot]->playerType == 1;   // Comment this for WHY?
											 // **** Don't need this!!! ****
	}
	playerSlot[slot]->playerType = 4;	
}


// This method will be called by UI to designate one slot to be AI.
void SetupGame::createComputerPilotSlot(int slot, int type){

	if (playerSlot[slot]->playerType == 2) {
		networkServer->kickPlayer(playerSlot[slot]->playerName);
		playerSlot[slot]->playerType = 3;	
		playerSlot[slot]->AIType = type;
	}
	else {
		playerSlot[slot]->playerType = 3;	
		playerSlot[slot]->AIType = type;
	} 
	

}

// This method will start a new game. It will call a method from
// Game Control which will begin the game.
// Commented on 10-03-99 because this will be returned by UI	
void SetupGame::go() {
	
    if (mode == SERVERMODE) {
		networkServer->startGame();
		Sleep(1000);
		createShipInterface();
		createFlightGraphics();
		createGameControl("", numOfShips);
	}
	
	// if client
	if (mode == CLIENTMODE) { 
		gsd = new ShipInterface(clientID);
		gsd->next = NULL;
		createFlightGraphics();
		networkClient->startGame(gsd);
	}
}

//********************************************

void SetupGame::endGame() {
	//_endthread();
	//delete gameControl;
	//gameControl = NULL;

	computerPilots = 0;
	totalShips = 0;
	localShip = 0;
	gameMode = 0;
	numOfShips = 1;

	for (int i = 0; i < 8; i++)	{
		playerSlot[i]->playerType = 0;
		playerSlot[i]->playerName = NULL;
		playerSlot[i]->AIType = 1;
	}

	if (mode == SERVERMODE) {
	
		gsd->next = gsd->next->next;
		delete networkServer;
		gsdListDestroyer(gsd);
		networkServer = NULL;
		
		delete gameControl;
		gameControl = NULL;	

		computerPilotDestroyer();
	}

	else if (mode == CLIENTMODE) { 
		delete networkClient;
		networkClient = NULL;
	}

	else {
		gsd->next = gsd->next->next;
		gsdListDestroyer(gsd);
		
		delete gameControl;
		gameControl = NULL;	


		computerPilotDestroyer();			
//		delete computerPilot;
//		computerPilot = NULL;
	
	}
}
//*******************************************

void SetupGame::gsdListDestroyer(GameStateDestination *current) {
	if (current->next != NULL) {
		gsdListDestroyer(current->next);
	}
	delete current;
	current = NULL;

}


void SetupGame::computerPilotDestroyer() {
	for (int i = 0; i < 7; i++)	{
		if (computerPilotArray[i] != NULL) {
			delete computerPilotArray[i];;
			computerPilotArray[i] = NULL;
		}
	}


}
// Then fill up the array in createComputerPilot








// This is a method the Network Server can call in order to notify  
// all the players in a networked game that a new player has joined 
// the game. It will also display the new user's information.  
void SetupGame::joinNetworkGame(char* servername, char* playername) {
	clientID = networkClient->connectServer(servername, playername);
}

void SetupGame::determineTotalShips(){}
	// This method determines how many total ships are involved in 
	// the game. It will be able to delinate the number of human ships 
	// along with the number of computer ships and the single local 
	// ship. Using simple math, it will determine the total amount of 
	// ships, by first getting the total amount of computer ships and 
	// incrementing the computerShips field. Then it will determine the 
	// total amount of human ships by taking the totalShips - local ship-
	// computerShips.In a networked game, there will always be a single 
	// local player.

///////////////////////////////////////
void SetupGame::setNetworkServer(NetworkServer * networkServer) {
	this->networkServer = networkServer;
}


void createGameControlThread(void* dummy) {
    thisGameControl->startGame();
	thisGameControl = NULL;
//********************    
	//thisGameControl->destroyGSDList(gsd);
	//delete thisGameControl;
	//thisGameControl = NULL;
	thisSetupGame->endGame();
//
}
//**********************

// This method will create an instance of GameControl.
void SetupGame::createGameControl(string fileContents, int numOfShips) {
	if (gameMode == 1) {
		gameControl = new GameControl(gsd, numOfShips, fileContents);
	}	
	else if (gameMode == 2) {
		int shipTypes[8];
		shipTypes[0] = 0;
		for (int i=1; i<8; i++)
		{
			if (playerSlot[i]->playerType == 3){
				shipTypes[i] = playerSlot[i]->AIType;
			}
			else if (playerSlot[i]->playerType == 2){
				shipTypes[i] = 0;
			}
			else {
				shipTypes[i] = -1;
			}
		}
		gameControl = new GameControl(gsd, numOfShips, shipTypes);
	} 
	
	else {
		throw "gameMode invalid in createGameControl()";
	}
	
	thisGameControl = gameControl;
    thisSetupGame = this;
    _beginthread(createGameControlThread,0,NULL);
}

// This method will create an instance of the NetworkClient.
void SetupGame::createNetworkClient(){
	networkClient = new NetworkClient();
}

// This method will create an instance of the NetworkServer.
void SetupGame::createNetworkServer(){
	networkServer = new NetworkServer(this);
}

// This method will create an instance of ShipInterface.
void SetupGame::createShipInterface(){
	GameStateDestination *tempGSD;
	myShip[0] = new ShipInterface(0);
	gsd = myShip[0];

	if (gameMode == 1) {
		tempGSD = gsd;
	}
	else {
		gsd->next = networkServer;
		tempGSD = gsd->next;
	}
	for (int i = 1; i < 8; i++) {
		// if human player
		
		/*if  (playerSlot[i]->playerType == 2) {
			myShip[i] = new ShipInterface(i);
			tempGSD->next = myShip[i];
			//createUserCombatControl(myShip[i]);
			createSoundPlayer();
			tempGSD = tempGSD->next;
			numOfShips ++;
		} 

		*/
		// if computer pilot player	
		if  (playerSlot[i]->playerType == 3) {
			myShip[i] = new ShipInterface(i);
			myShip[i]->setAIPlayer(true);
		    tempGSD->next = myShip[i];
			//	PlayerInfo* playerSlot[8];
			createComputerPilot(i, playerSlot[i]->AIType , myShip[i]);
			tempGSD = tempGSD->next;
			numOfShips++;
		}
	} // ends for 
	tempGSD->next = NULL;
} // ends createShipInterface


// This method will create an instance of ComputerPilot.
void SetupGame::createComputerPilot(int playerSlot, int type, ShipInterface* si){
		computerPilotArray[playerSlot] = new ComputerPilot(playerSlot, type, gameMode, si );
		si->isComputerPilotSI(computerPilotArray[playerSlot]); 
}

// This method will create an instance of FlightGraphics.
void SetupGame::createFlightGraphics(){
	initFlightGraphics();
}








