/**************************************************************************
*                                                                         *
* Class Name: GameControl                                                 *
*                                                                         *
* Author: Brian Birmingham                                                *
*                                                                         *
* Description: The purpose of this system is to maintain the state of the *
*              game by sending out the current GameState and retrieving a *
*              Shiptate from each of the GameStateDesinations.  It        *
*              then uses this information to create a new GameState.      *
*                                                                         *
* Revisions:  Brian Birmingham 9-22-99 Initial Version                    *
*                                                                         *
**************************************************************************/

#include "StdAfx.h"
#include <windows.h>
#include <stdlib.h>
#include <io.h>
#include <fcntl.h>
//#include <iostream>

#include "GameControl.h"

//using namespace std;

GameControl::GameControl(GameStateDestination *gameStateDestinations,
	int numberOfShips, int shipTypes[])
{
	initializeGame(gameStateDestinations, numberOfShips);

	for (int i=0; i<8; i++){
		this->shipTypes[i] = shipTypes[i];
	}
	createShipsInGameState(newState);
	storeStartingPositions();
	respawnOn = true;
}



GameControl::GameControl(GameStateDestination *gameStateDestinations,
	int numberOfShips, string buffer)
{
	if (buffer.find("KECKLAB") != string::npos){
		numberOfShips++;
		//numberOfShips = 8;
	}
	initializeGame(gameStateDestinations, numberOfShips);
	//createShipsInGameState(newState);
	readInGameStateFromFile(newState, buffer);
	storeStartingPositions();
	respawnOn = false;
}


GameControl::~GameControl()
{
	destroyShipStateList(shipStates);
	destroySpaceObjectList(newState->spaceObjects);
	destroySpaceObjectList(lastState->spaceObjects);
	delete newState;
	delete lastState;
	newState=NULL;
	lastState=NULL;
}

void GameControl::initializeGame(GameStateDestination *gsds, int nos){
	GCPROCESSINGLEVEL = 4;
	clock = 0;
	this->numberOfShips = nos;
	this->gameStateDestinations = gsds;
	createShipStateStructures();
	localShip = shipStates;
	lastState = NULL;
	newState = new GameState;
	newState->endGame = false;
	initializePlayerClocks();
	GEM.addDefeatCondition(&localShip->quit);
	for (int i=0; i<numberOfShips; i++){
		timesDied[i] = 0;
	}
	dockings = 0;
	cargoDeaths = 0;
}



void GameControl::createShipStateStructures()
{
	shipStates = new ShipState();
	ShipState *current = shipStates;
	current->id = 0;
	current->quit = false;
	for (int i=1; i<numberOfShips; i++)
	{
		current->next = new ShipState();
		current->next->id = i;
		current->next->quit = false;
		current = current->next;
	}
	current->next = NULL;
}




void GameControl::storeStartingPositions(){
	SpaceObject *current;
	current=newState->spaceObjects;
	for (int i=0; i<numberOfShips; i++){
		startingPositions[i].location.x = current->position.x;
		startingPositions[i].location.y = current->position.y;
		startingPositions[i].location.z = current->position.z;
		startingPositions[i].direction.i = current->direction.i;
		startingPositions[i].direction.j = current->direction.j;
		startingPositions[i].direction.k = current->direction.k;
		startingPositions[i].up.i = current->up.i;
		startingPositions[i].up.j = current->up.j;
		startingPositions[i].up.k = current->up.k;
		startingPositions[i].right.i = current->right.i;
		startingPositions[i].right.j = current->right.j;
		startingPositions[i].right.k = current->right.k;
		current = current->next;
	}
}




void GameControl::initializePlayerClocks(){
	for (int i=0; i<numberOfShips; i++){
		playerClocks[i].lastFireTime = 0;
		playerClocks[i].lastShieldGenTime = 0;
		playerClocks[i].lastAccelTime = 0;
	}
}




void GameControl::createShipsInGameState(GameState *gameState)
{
	double baseAngle = (PI*2)/numberOfShips;
	double currentAngle;
	gameState->numberOfShips = numberOfShips;
	gameState->startingNumShips = numberOfShips;
	gameState->spaceObjects = new Ship(Point(DISTANCEFROMCENTER,0,0), 
		Vector(-1,0,0), Vector(0,1,0), Vector(0,0,-1), "KECKWING");
	SpaceObject *currentShip = gameState->spaceObjects;
	currentShip->id = 0;
	currentShip->team = currentShip->id;
	char currentShipType[10];
	for (int i=1; i<numberOfShips; i++){
		switch(shipTypes[i]){
		case 0:	strcpy(currentShipType,"KECKWING"); break;
		case 1: strcpy(currentShipType, "EE1"); break;
		case 2: strcpy(currentShipType, "EE2"); break;
		case 3: strcpy(currentShipType, "EE3"); break;
		case 4: strcpy(currentShipType, "CARGOSHIP"); break;
		case -1: throw "numberOfShips too large based on shipTypes array";
		}
		currentAngle = baseAngle * i;
		currentShip->next = new Ship(
			Point(cos(currentAngle) * DISTANCEFROMCENTER, 0, 
			sin(currentAngle) *	DISTANCEFROMCENTER), Vector(-1,0,0),
			Vector(0,1,0), Vector(0,0,-1), currentShipType
			);
		((Ship*)currentShip->next)->yaw(-currentAngle);
		currentShip->next->id = i;
		currentShip->next->team = i;
		currentShip = currentShip->next;
	}
	lastSO = currentShip;
	currentShip->next = NULL;
}




void GameControl::readInGameStateFromFile(GameState *gameState, string buffer){
	//char buffer[3000];
	//int fd = open("U:\\_KeckWars\\mission2.txt", O_RDONLY);
	//int bytesRead = read(fd, buffer, 3000);
	string stringBuffer = buffer;
	string segment;
	int startpos = 0;
	int endpos = 0;
	gameState->numberOfShips = numberOfShips;
	gameState->startingNumShips = numberOfShips;
	gameState->spaceObjects = NULL;
	for (int i=0;stringBuffer.find("*")-endpos != 1;i++){
		endpos = stringBuffer.find(";", startpos);
		segment = stringBuffer.substr(startpos, endpos-startpos+1);
		if (segment.find("KECKWING") != string::npos ||
			segment.find("EE1") != string::npos ||
			segment.find("EE2") != string::npos ||
			segment.find("EE3") != string::npos ||
			segment.find("CARGOSHIP") != string::npos){
			//cout << "Info for ship " << i << ": " << segment << "\n";
			loadShipInformation(i, gameState, segment);
			// FIX THIS TEMPORARY HACK
			//numberOfShips = i; //commenting out the hack fixes it.
			// END HACK
			//cout << "NumberOfShips set to: " << numberOfShips << "\n";
		}
		else if (segment.find("KECKLAB") != string::npos){
			//cout << "Keck Lab Present in state: " << segment << "\n";
			addKeckLab(segment);
		}
		else if (segment.find("DEFEAT") != string::npos || 
			segment.find("VICTORY") != string::npos){
			//cout << "Conditions are: " << segment << "\n";
			setVictoryOrDefeatConditions(segment);
		}
		else {
			//cout << "Invalid information found in misison file." << "\n";
			//cout << "Attempting to process next good information" << "\n";
		}
		startpos = endpos+1;
	}
}




void GameControl::loadShipInformation(int id, GameState *gameState, 
									  string segment){
	bool done = false;
	int startpos = 0;
	int endpos = 0;
	int teamnumber;
	string data;
	string type;
	Point location;
	Vector forward;
	Vector up;
	Vector right;
	char currentShipType[10];
	for (int i=0; !done; i++){
		if ( (endpos = segment.find(":", startpos)) == 
			string::npos){
			endpos = segment.find(";", startpos);
			done = true;
		};
		data = segment.substr(startpos, endpos-startpos+1);
		//cout << "    Data Item: " << data << "\n";
		switch(i){
		case 0: 
			type = data.substr(0,data.length()-1);
			break;
		case 1:
			teamnumber = atoi( (char*)(data.c_str()) );
		case 2: 
			location = extractPointFrom(data);
			//cout << "    Point Extracted: " << location.x << ", "
			//<< location.y << ", " << location.z << "\n";
			break;
		case 3: 
			forward = unit(extractVectorFrom(data));
			//cout << "    Vector Extracted: " << forward.i << ", "
			//<< forward.j << ", " << forward.k << "\n";
			break;
		case 4: 
			up = unit(extractVectorFrom(data));
			//cout << "    Vector Extracted: " << up.i << ", "
			//<< up.j << ", " << up.k << "\n";
			break;
		}
		startpos = endpos+1;
	}
	right = unit(forward.cross(up));
	if (type == "KECKWING"){
		strcpy(currentShipType, "KECKWING");
	}
	else if (type == "EE1"){
		strcpy(currentShipType, "EE1");
	}
	else if (type == "EE2"){
		strcpy(currentShipType, "EE2");
	}
	else if (type == "EE3"){
		strcpy(currentShipType, "EE3");
	}
	else if (type == "CARGOSHIP"){
		strcpy(currentShipType, "CARGOSHIP");
	}
	if (gameState->spaceObjects == NULL){
		gameState->spaceObjects = new Ship(location, forward, up, right,
			currentShipType);
		lastSO = gameState->spaceObjects;
		lastSO->id = id;
		lastSO->team = teamnumber;
	}
	else{
		lastSO->next = new Ship(location, forward, up, right, 
			currentShipType);
		lastSO = lastSO->next;
		lastSO->id = id;
		lastSO->team = teamnumber;
	}
}




void GameControl::addKeckLab(string segment){
	bool done = false;
	int startpos = 0;
	int endpos=0;
	int teamnumber;
	string data;
	Point location;
	Vector forward;
	Vector up;
	Vector right;
	Vector perpendicularConversionVector(1,0,0);
	for (int i=0; !done; i++){
		if ( (endpos = segment.find(":", startpos)) == 
			string::npos){
			endpos = segment.find(";", startpos);
			done = true;
		}
		data = segment.substr(startpos, endpos-startpos+1);
		//cout << "    Data Item: " << data << "\n";
		switch(i){
		case 0: break;
		case 1:
			teamnumber = atoi( (char*)(data.c_str()) );
		case 2:
			location = extractPointFrom(data);
			//cout << "    Point Extracted: " << location.x << ", "
			//<< location.y << ", " << location.z << "\n";
			break;
		case 3:
			up = unit(extractVectorFrom(data));
			//cout << "    Vector Extracted: " << up.i << ", "
			//<< up.j << ", " << up.k << "\n";
			break;
		}
		startpos = endpos+1;
	}
	forward = (perpendicularConversionVector -
	perpendicularConversionVector.projectionOnto(up));
	if ( vectorsAreEqual(forward, Vector(0,0,0)) ) {
		forward = Vector(0,1,0);
		//cout << "Perpendicular Conversion matches up vector\n";
	}
	else {
		forward = unit(forward);
	}
	//cout << "Forward Vector is: " << forward.i << ", "
	//	<< forward.j << ", " << forward.k << "\n";
	right = unit(forward.cross(up));
	lastSO->next = new Ship(location, forward, up, right, 
			"KECKLAB");
	lastSO = lastSO->next;
	lastSO->id = numberOfShips-1;
	lastSO->team = teamnumber;
}
/*
void GameControl::setKeckLabSS(){
	ShipState* current = shipStates;
	while(current->next != NULL){
		current = current->next;
	}
}
*/

void GameControl::setVictoryOrDefeatConditions(string segment){
	bool done = false;
	int startpos = segment.find(":")+1;
	string type = segment.substr(0, startpos-1);
	//cout << "    Type of condition is: " << type << "\n";
	int endpos = 0;
	string data;
	Point location;
	for(int i=0; !done; i++){
		if ( (endpos = segment.find("+", startpos)) == string::npos ){
			endpos = segment.find(";", startpos);
			done = true;
		}
		data = segment.substr(startpos, endpos-startpos);
			addVictoryOrDefeatCondition(data, type);
		startpos = endpos+1;
	}

}





void GameControl::addVictoryOrDefeatCondition(string segment, string type){
	int *condition;
	int metValue;
	int conditionType;
	string variantStr;
	string metValueStr;
	int eqSignPos = segment.find("=");
	variantStr = segment.substr(0, eqSignPos);
	int startpos = eqSignPos+1;
	metValueStr = segment.substr(startpos, segment.length()-startpos);

	// DEFAULTS
	condition = NULL;
	metValue = atoi(metValueStr.c_str());
	conditionType = ACCUMULATION;

	// CONFIGURE VICTORY CONDITION VARIABLES BASED ON STRING INPUT
	if (variantStr == "kills"){
		condition = &((Ship*)(newState->spaceObjects))->kills;
	}
	else if(variantStr == "playerdeaths"){
		condition = &timesDied[0];
	}
	else if(variantStr == "dockings"){
		condition = &dockings;
	}
	else if(variantStr == "cargodeaths"){
		condition = &cargoDeaths;
	}
	else if(variantStr == "remainingships"){
		condition = &numberOfShips;
		conditionType = DEPRECIATION;
	}

	if (condition == NULL){ // String read in from file is not recognized.
		return;
	}

	// SET VICTORY CONDITION USING SET VARIABLES
	if (type == "VICTORY"){
		GEM.addVictoryCondition(condition, metValue, conditionType);
	}
	else{
		GEM.addDefeatCondition(condition, metValue, conditionType);
	}
}




Point GameControl::extractPointFrom(string segment){
	int startpos = 0;
	int endpos=0;
	string data;
	double coordinates[3];
	for (int i=0; i<3; i++){
		if ( (endpos = segment.find(",", startpos)) == string::npos){
			if ( (endpos = segment.find(":", startpos)) == string::npos){
				endpos = segment.find(";", startpos);
			}
		}
		data = segment.substr(startpos, endpos-startpos);
		coordinates[i]=atoi(data.c_str());
		startpos = endpos+1;
	}
	return Point(coordinates[0],coordinates[1],coordinates[2]);
}




Vector GameControl::extractVectorFrom(string segment){
	int startpos = 0;
	int endpos=0;
	string data;
	double coordinates[3];
	for (int i=0; i<3; i++){
		if ( (endpos = segment.find(",", startpos)) == string::npos){
			if ( (endpos = segment.find(":", startpos)) == string::npos){
				endpos = segment.find(";", startpos);
			}
		}
		data = segment.substr(startpos, endpos-startpos);
		coordinates[i]=atoi(data.c_str());
		startpos = endpos+1;
	}
	return Vector(coordinates[0],coordinates[1],coordinates[2]);
}




void GameControl::destroyShipStateList(ShipState* current)
{
	if (current->next != NULL)
	{
		destroyShipStateList(current->next); 
		// FIX: try to make tail recursive (may be impossible)
	}
	delete current;
	current = NULL;
}






void GameControl::destroySpaceObjectList(SpaceObject* current)
{
	if (current->next != NULL)
	{
		destroySpaceObjectList(current->next); 
		// FIX: try to make tail recursive (may be impossible)
	}
	delete current;
	current = NULL;
}






void GameControl::startGame()
{
	sendGameState();
	while (GEM.gameEndingStatus() == RUNNING)
	{
		Sleep(50);
		if (GCPROCESSINGLEVEL >= 1){
			updateShipAttitudes();
		}
		if (GCPROCESSINGLEVEL >= 2){
			updateShipSpeeds();
			updateShipPositions();
		}
		if (GCPROCESSINGLEVEL >= 3){
			updateSpaceObjects();
		}
		if (GCPROCESSINGLEVEL >= 4){
			detectCollisions();
		}
		processQuits();
		sendGameState();
	}
	for(int i=clock+ENDDELAY; clock < i;){
		Sleep(50);
		if (GCPROCESSINGLEVEL >= 1){
			updateShipAttitudes();
		}
		if (GCPROCESSINGLEVEL >= 2){
			updateShipSpeeds();
			updateShipPositions();
		}
		if (GCPROCESSINGLEVEL >= 3){
			updateSpaceObjects();
		}
		if (GCPROCESSINGLEVEL >= 4){
			detectCollisions();
		}
		processQuits();
		sendGameState();
	}
	newState->endGame = true;
	sendGameState();
}





void GameControl::updateShipAttitudes()
{
	Ship* currentShip = (Ship *)newState->spaceObjects;
	ShipState * currentSS = shipStates;
	for(int i=0; i<numberOfShips; i++)
	{
		if (strcmp(currentShip->type, "EXPLOSION") != 0){
			updateShipAttitude(currentShip, currentSS);
		}
		currentShip = (Ship *)currentShip->next;
		currentSS = currentSS->next;
	}
}





void GameControl::updateShipSpeeds()
{
	Ship* currentShip = (Ship *)newState->spaceObjects;
	ShipState * currentSS = shipStates;
	for(int i=0; i<numberOfShips; i++)
	{
		if (currentShip == NULL || currentSS == NULL){
			throw "Pointer NULL in updateShipSpeeds()";
		}
		if (currentShip->id != currentSS->id){
			throw "ShipState id != Ship id in updateShipSpeeds()";
		}
		if (strcmp(currentShip->type, "EXPLOSION") != 0){
			updateShipSpeed(currentShip, currentSS->speed);
		}
		currentShip = (Ship *)currentShip->next;
		currentSS = currentSS->next;
	}
}







void GameControl::updateShipPositions()
{
	Ship* currentShip = (Ship *)newState->spaceObjects;
	for(int i=0; i<numberOfShips; i++)
	{
		if (currentShip == NULL){
			throw "Pointer NULL in updateShipPositions()";
		}
		currentShip->position += (currentShip->direction * 
			(double)currentShip->speed * 0.5);
		currentShip = (Ship *)currentShip->next;
	}
}





void GameControl::updateSpaceObjects()
{
	// Firing code
	SpaceObject *currentSO = newState->spaceObjects;
	for (ShipState *currentShipState = shipStates; currentShipState !=
		NULL; currentShipState = currentShipState->next){
		// CHIPS
		if(currentShipState->firing == true && 
			playerClocks[currentSO->id].lastFireTime + SHOTDELAY < clock &&
			strcmp(currentSO->type, "EXPLOSION") != 0){

			lastSO->next = new SpaceObject(currentSO->position,
				currentSO->direction, currentSO->up,
				currentSO->right, "WEAPON", currentSO->id);

			lastSO = lastSO->next;
			lastSO->next = NULL;
			if (currentSO->id >= 0 && currentSO->id < 
				newState->startingNumShips){

				((Ship*)currentSO)->firing = true;
				playerClocks[currentSO->id].lastFireTime = clock;
			}
		}
		else if (currentSO->id >= 0 && currentSO->id < 
			newState->startingNumShips){

			((Ship*)currentSO)->firing = false;
		}
		// DISRUPTOR
		if(currentShipState->disruptors == true && 
			playerClocks[currentSO->id].lastFireTime + 
			DISRUPTORDELAY < clock &&
 			strcmp(currentSO->type, "EXPLOSION") != 0){

			lastSO->next = new SpaceObject(currentSO->position,
				currentSO->direction, currentSO->up,
				currentSO->right, "DISRUPTOR", currentSO->id);

			lastSO = lastSO->next;
			lastSO->next = NULL;
			if (currentSO->id >= 0 && currentSO->id < 
				newState->startingNumShips){

				((Ship*)currentSO)->disruptors = true;
				playerClocks[currentSO->id].lastFireTime = clock;
			}
		}
		else if (currentSO->id >= 0 && currentSO->id < 
			newState->startingNumShips){

			((Ship*)currentSO)->disruptors = false;
		}
		currentSO = currentSO->next;
	}
	// Object Movement Code
	while(currentSO != NULL){
		if(strcmp(currentSO->type,"WEAPON") == 0 || 
			strcmp(currentSO->type,"DISRUPTOR") == 0){
			updateWeaponPosition(currentSO);
		}
		else if (strcmp(currentSO->type, "KECKLAB") == 0){
			((Ship*)(currentSO))->yaw(SHIPTURNFACTOR/2);
		}
		currentSO = currentSO->next;
	}
	// Ship Explosion / Shield Regen Code
	currentSO = newState->spaceObjects;
	for (int i=0; i<newState->numberOfShips; i++){
		regenShields((Ship*)currentSO);
		convertExplosionToFromShip((Ship*)currentSO);
		currentSO = currentSO->next;
	}
	//regenShields((Ship*)currentSO);
	//convertExplosionToFromShip((Ship*)currentSO);
	// Object Removal Code
	currentSO = newState->spaceObjects;
	while (currentSO->next != NULL){
		if (currentSO->next->life <= 0){
			if (strcmp(currentSO->next->type, "WEAPON") == 0 ||
				strcmp(currentSO->next->type, "DISRUPTOR") == 0){
				if (currentSO->next == lastSO){
					lastSO = currentSO;
				}
				SpaceObject *temp = currentSO->next;
				currentSO->next = currentSO->next->next;
				delete temp;
			}
			else if(strcmp(currentSO->next->type, "EXPLOSION") == 0 && 
				currentSO->next->damage <= 0 && !respawnOn){

				destroyShip(currentSO->next->id);
			}
			else{
				currentSO = currentSO->next;
			}
		}
		else{
			currentSO = currentSO->next;
		}
	}
}




void GameControl::regenShields(Ship* ship){
	int maxShieldsForShip;
	if(playerClocks[ship->id].lastShieldGenTime + SHIELDGENDELAY < clock){
		ship->shields += SHIELDGENAMOUNT;
		if (strcmp(ship->type,"KECKWING") == 0){
			maxShieldsForShip = STARTINGKECKWINGSHIELDS;
		}
		else if (strcmp(ship->type,"EE1") == 0){
			maxShieldsForShip = STARTINGENEMYONESHIELDS;
		}
		else if (strcmp(ship->type,"EE2") == 0){
			maxShieldsForShip = STARTINGENEMYTWOSHIELDS;
		}
		else if (strcmp(ship->type,"EE3") == 0){
			maxShieldsForShip = STARTINGENEMYTHREESHIELDS;
		}
		else if (strcmp(ship->type,"CARGOSHIP") == 0){
			maxShieldsForShip = STARTINGCARGOSHIPSHIELDS;
		}
		if (ship->shields > maxShieldsForShip){
			ship->shields = maxShieldsForShip;
		}
		playerClocks[ship->id].lastShieldGenTime = clock;
	}
}




void GameControl::convertExplosionToFromShip(Ship* ship)
{
	if (ship->life <= 0 && strcmp(ship->type,"EXPLOSION") != 0){
		if (strcmp(ship->type,"KECKWING") == 0){
			ship->life = DEADKECKWINGLIFE; // junk for the display
			ship->shields = -1; //junk for the display
		}
		else if (strcmp(ship->type,"EE1") == 0){
			ship->life = DEADENEMYONELIFE;
			ship->shields = -1; //junk for the display
		}
		else if (strcmp(ship->type,"EE2") == 0){
			ship->life = DEADENEMYTWOLIFE;
			ship->shields = -1; //junk for the display
		}
		else if (strcmp(ship->type,"EE3") == 0){
			ship->life = DEADENEMYTHREELIFE;
			ship->shields = -1; //junk for the display
		}
		else if (strcmp(ship->type,"CARGOSHIP") == 0){
			ship->life = DEADCARGOSHIPLIFE;
			ship->shields = -1; //junk for the display
			cargoDeaths++;
		}
		timesDied[ship->id]++;
		grantKillTo(ship->idOfLastAttacker, ship->id);
		strcpy(ship->type, "EXPLOSION");
		ship->damage = ship->damage / 3;
	}
	if (ship->damage <= 0){
		if(respawnOn){
			switch(ship->life){
			case DEADKECKWINGLIFE:
				strcpy(ship->type, "KECKWING");
				ship->shields = STARTINGKECKWINGSHIELDS;
				break;
			case DEADENEMYONELIFE:
				strcpy(ship->type, "EE1");
				ship->shields = STARTINGENEMYONESHIELDS;
				break;
			case DEADENEMYTWOLIFE:
				strcpy(ship->type, "EE2");
				ship->shields = STARTINGENEMYTWOSHIELDS;
				break;
			case DEADENEMYTHREELIFE:
				strcpy(ship->type, "EE3");
				ship->shields = STARTINGENEMYTHREESHIELDS;
				break;
			case DEADCARGOSHIPLIFE:
				strcpy(ship->type, "CARGOSHIP");
				ship->shields = STARTINGCARGOSHIPSHIELDS;
			default:
				//throw "explosion not converted to ship: type not found\n";
				break;
			}
			ship->life = STARTINGSHIPLIFE;
			ship->radius = SHIPRADIUS;
			ship->damage = SHIPDAMAGE;
			ship->position.x = startingPositions[ship->id].location.x;
			ship->position.y = startingPositions[ship->id].location.y;
			ship->position.z = startingPositions[ship->id].location.z;
			ship->direction.i = startingPositions[ship->id].direction.i;
			ship->direction.j = startingPositions[ship->id].direction.j;
			ship->direction.k = startingPositions[ship->id].direction.k;
			ship->up.i = startingPositions[ship->id].up.i;
			ship->up.j = startingPositions[ship->id].up.j;
			ship->up.k = startingPositions[ship->id].up.k;
			ship->right.i = startingPositions[ship->id].right.i;
			ship->right.j = startingPositions[ship->id].right.j;
			ship->right.k = startingPositions[ship->id].right.k;
			ship->speed = 0;
		}
	}
	if (strcmp(ship->type,"EXPLOSION") == 0){
		updateExplosion(ship);
	}
}




void GameControl::updatePauseState(){
	ShipState *currentSS = shipStates;
	while(currentSS != NULL){
		if (currentSS->pause == true){
			if (GCPROCESSINGLEVEL == 4){
				GCPROCESSINGLEVEL = 0;
			}
			else{
				GCPROCESSINGLEVEL = 4;
			}
			break;
		}
		currentSS = currentSS->next;
	}
}




void GameControl::processQuits()
{
	ShipState *currentSS = shipStates;
	ShipState *tempSS;
	Ship *currentShip = (Ship*)newState->spaceObjects;
	Ship *tempShip;
	while(currentSS->next != NULL){
		if (currentSS->next->quit == true){
			if (currentShip->next == lastSO){
				lastSO = currentShip;
			}
			tempSS = currentSS->next->next;
			tempShip = (Ship*)(currentShip->next->next);
			delete currentSS->next;
			delete currentShip->next;
			currentSS->next = tempSS;
			currentShip->next = tempShip;
			numberOfShips--;
		}
		else{
			currentSS = currentSS->next;
			currentShip = (Ship*)currentShip->next;
		}
	}
	newState->numberOfShips = numberOfShips;
}




void GameControl::destroyShip(int shipID){
	ShipState *currentSS = shipStates;
	ShipState *tempSS;
	Ship *currentShip = (Ship*)newState->spaceObjects;
	Ship *tempShip;
	while(currentSS->next != NULL){
		if (currentSS->next->id == shipID){
			if (currentShip->next == lastSO){
				lastSO = currentShip;
			}
			tempSS = currentSS->next->next;
			tempShip = (Ship*)(currentShip->next->next);
			delete currentSS->next;
			delete currentShip->next;
			currentSS->next = tempSS;
			currentShip->next = tempShip;
			numberOfShips--;
		}
		else{
			currentSS = currentSS->next;
			currentShip = (Ship*)currentShip->next;
		}
	}
	newState->numberOfShips = numberOfShips;
}



void GameControl::sendGameState()
{
	ShipState *currentSS;
	ShipState *returnedSS;

	GameState *temp = new GameState(newState);
	GameState *killme = lastState;
	lastState = temp;
	
	for (GameStateDestination *currentGSD = gameStateDestinations
		; currentGSD != NULL; currentGSD = currentGSD->next)
	{
		currentSS = returnedSS = currentGSD->updateGameState(lastState);
		while(currentSS != NULL)
		{
			copyShipStateInformationFrom(currentSS);
			currentSS = currentSS->next;
		}
		returnedSS = NULL;
	}
	clock++;
	updatePauseState();

	while (setDisplay){
		if (killme != NULL && setDisplay == false){
			destroySpaceObjectList(killme->spaceObjects);
			delete killme;
		}
	}
}








void GameControl::copyShipStateInformationFrom(ShipState* current)
{
	ShipState* localCurrent = shipStates;
	while(localCurrent != NULL && localCurrent->id != current->id){
		localCurrent = localCurrent->next;
	}
	if (localCurrent != NULL){
		localCurrent->firing = current->firing;
		localCurrent->disruptors = current->disruptors;
		localCurrent->pitch = current->pitch;
		localCurrent->pause = current->pause;
		localCurrent->quit = current->quit;
		localCurrent->roll = current->roll;
		localCurrent->speed = current->speed;
		localCurrent->yaw = current->yaw;
	}
}






void GameControl::updateShipAttitude(Ship* ship, ShipState* shipState)
{
		if (shipState == NULL){
			throw "shipState NULL in updateShipAttitude()";
		}
		if(ship == NULL){
			throw "ship NULL in updateShipAttitude()";
		}
		if (ship->id != shipState->id){
			throw "ShipState id != id in updateShipAttitute()";
		}
		// YAW
		if (shipState->yaw < 0){
			if (shipState->yaw < -MAXSHIPTURNMULTIPLIER){
				ship->yaw(SHIPTURNFACTOR * MAXSHIPTURNMULTIPLIER);
			}
			else{
				ship->yaw(SHIPTURNFACTOR * abs(shipState->yaw));
			}
		}
		else if (shipState->yaw > 0){
			if (shipState->yaw > MAXSHIPTURNMULTIPLIER){
				ship->yaw(-SHIPTURNFACTOR * MAXSHIPTURNMULTIPLIER);
			}
			else{
				ship->yaw(-SHIPTURNFACTOR * abs(shipState->yaw));
			}
		}
		// PITCH
		if (shipState->pitch < 0){
			if (shipState->pitch < -MAXSHIPTURNMULTIPLIER){
				ship->pitch(SHIPTURNFACTOR * MAXSHIPTURNMULTIPLIER);
			}
			else{
				ship->pitch(SHIPTURNFACTOR * abs(shipState->pitch));
			}
		}
		else if (shipState->pitch > 0){
			if (shipState->pitch > MAXSHIPTURNMULTIPLIER){
				ship->pitch(-SHIPTURNFACTOR * MAXSHIPTURNMULTIPLIER);
			}
			else{
				ship->pitch(-SHIPTURNFACTOR * abs(shipState->pitch));
			}
		}
		// ROLL
		if (shipState->roll < 0){
			if (shipState->roll < -MAXSHIPTURNMULTIPLIER){
				ship->roll(-SHIPTURNFACTOR * MAXSHIPTURNMULTIPLIER);
			}
			else{
				ship->roll(-SHIPTURNFACTOR * abs(shipState->roll));
			}
		}
		else if (shipState->roll > 0){
			if (shipState->roll > MAXSHIPTURNMULTIPLIER){
				ship->roll(SHIPTURNFACTOR * MAXSHIPTURNMULTIPLIER);
			}
			else{
				ship->roll(SHIPTURNFACTOR * abs(shipState->roll));
			}
		}
}





void GameControl::updateShipSpeed(Ship* ship, int desiredSpeed)
{
	if (desiredSpeed > ship->speed + 10){
		ship->speed += 1;
	}
	else if (desiredSpeed > ship->speed){
		if (playerClocks[ship->id].lastAccelTime + ACCELDELAY < clock){
			ship->speed ++;
			playerClocks[ship->id].lastAccelTime = clock;
		}
	}
	if (desiredSpeed < ship->speed - 10){
		ship->speed -= 1;
	}
	else if (desiredSpeed < ship->speed){
		if (playerClocks[ship->id].lastAccelTime + ACCELDELAY < clock){
			ship->speed --;
			playerClocks[ship->id].lastAccelTime = clock;
		}
	}
	if (ship->speed < 0){
		ship->speed = 0;
	}
	if (strcmp(ship->type, "KECKWING") == 0){
		if (ship->speed > MAXKECKWINGSPEED){
			ship->speed = MAXKECKWINGSPEED;
		}
	}
	else if (strcmp(ship->type, "EE1") == 0){
		if (ship->speed > MAXENEMYONESPEED){
			ship->speed = MAXENEMYONESPEED;
		}
	}
	else if (strcmp(ship->type, "EE2") == 0){
		if (ship->speed > MAXENEMYTWOSPEED){
			ship->speed = MAXENEMYTWOSPEED;
		}
	}
	else if (strcmp(ship->type, "EE3") == 0){
		if (ship->speed > MAXENEMYTHREESPEED){
			ship->speed = MAXENEMYTHREESPEED;
		}
	}
	else if (strcmp(ship->type, "CARGOSHIP") == 0){
		if (ship->speed > MAXCARGOSHIPSPEED){
			ship->speed = MAXCARGOSHIPSPEED;
		}
	}
	else if (strcmp(ship->type, "KECKLAB") == 0){
		ship->speed = 0;
	}
	else if (strcmp(ship->type, "EXPLOSION") == 0){
		;
	}
	else{
		throw "Invalid ship type found in updateShipSpeeds()";
	}
}







void GameControl::updateWeaponPosition(SpaceObject* weapon)
{
	weapon->life --;
	weapon->position += (weapon->direction * (double)weapon->speed * 0.5);
}





void GameControl::updateExplosion(SpaceObject* explosion)
{
	explosion->radius += 5;
	explosion->damage -= .3;
}




void GameControl::dockCargoShip(int id)
{
	ShipState *currentSS = shipStates;
	ShipState *tempSS;
	Ship *currentShip = (Ship*)newState->spaceObjects;
	Ship *tempShip;
	//GameStateDestination *currentGSD = gameStateDestinations;
	//GameStateDestination *tempGSD;
	while(currentShip->next != NULL){
		if (currentShip->next->id == id){
			if (currentShip->next == lastSO){
				lastSO = currentShip;
			}
			tempSS = currentSS->next->next;
			//tempGSD = currentGSD->next->next;
			tempShip = (Ship*)(currentShip->next->next);
			delete currentSS->next;
			//delete currentGSD->next;
			delete currentShip->next;
			currentSS->next = tempSS;
			//currentGSD->next = tempGSD;
			currentShip->next = tempShip;
			dockings++;
			numberOfShips--;
		}
		else{
			currentSS = currentSS->next;
			//currentGSD = currentGSD->next;
			currentShip = (Ship*)currentShip->next;
		}
	}
	newState->numberOfShips = numberOfShips;
}




void GameControl::detectCollisions()
{
	Ship *current = ((Ship*)newState->spaceObjects);
	for (int i=0;i<numberOfShips;i++){
		current->shieldHit = false;
		current->hullHit = false;
	}
	for (SpaceObject *first = newState->spaceObjects; first != 
		NULL; first = first->next){
		for (SpaceObject *second = first->next; second
			!= NULL; second = second->next){
			if (isCollisionBetween(first, second)){

				if (strcmp(first->type,"CARGOSHIP")==0 &&
					strcmp(second->type,"KECKLAB")==0){
					dockCargoShip(first->id);
					continue;
				}// END DOCKING CHECK

				if(strcmp(first->type,"EXPLOSION") != 0){
					//apply damage to first
					if (first->id < newState->startingNumShips && 
						first->id >= 0 && second->damage == -1){

						((Ship*)first)->shields = 0;
						((Ship*)first)->shieldHit = true;
					}
					else if(first->id < newState->startingNumShips && 
						first->id >= 0 &&
						((Ship*)first)->shields	> second->damage){

						((Ship*)first)->shields -= second->damage;
						((Ship*)first)->shieldHit = true;
					}
					else if(first->id < newState->startingNumShips && 
						first->id >= 0 &&
						((Ship*)first)->shields > 0){

						first->life -= ((second->damage - 
							((Ship*)first)->shields)*3);
						((Ship*)first)->shields = 0;
						((Ship*)first)->hullHit = true;
					}
					else{
						first->life -= (second->damage *3);
					}
				}//END FIRST TYPE NOT EXPLOSION

				if(strcmp(second->type,"EXPLOSION") != 0){
					//apply damage to second
					if (second->id < newState->startingNumShips && 
						second->id >= 0 && first->damage == -1){

						((Ship*)second)->shields = 0;
						((Ship*)second)->shieldHit = true;
					}
					if(second->id < newState->startingNumShips && 
						second->id >= 0 &&
						((Ship*)second)->shields > first->damage){

						((Ship*)second)->shields -= first->damage;
						((Ship*)second)->shieldHit = true;
					}
					else if(second->id < newState->startingNumShips && 
						second->id >= 0 &&
						((Ship*)second)->shields > 0){

						second->life -= ((first->damage - 
							((Ship*)second)->shields)*3);
						((Ship*)second)->shields = 0;
						((Ship*)second)->hullHit = true;
					}
					else{
						second->life -= (first->damage *3);
					}
				}// END SECOND TYPE NOT EXPLOSION
				if (first->id >=0 && first->id < 
					newState->startingNumShips){

					((Ship*)first)->idOfLastAttacker = second->origID;
				}
				if (second->id >=0 && second->id < 
					newState->startingNumShips){

					((Ship*)second)->idOfLastAttacker = first->origID;
				}
			}// END IF COLLISION IS DETECTED
		}// END INNER FOR LOOP
	}//END OUTER FOR LOOP
}







bool GameControl::isCollisionBetween(SpaceObject *first,
									 SpaceObject *second)
{
	if (first->id == second->id){
		return false;
	}
	Vector temp = (first->position - second->position);
	int radiusSum = (first->radius + second->radius);
	return ( (temp.dot(temp)) < (radiusSum*radiusSum) );
}




void GameControl::grantKillTo(int attackerID, int deadID){
	Ship* attacker = NULL;
	Ship* deadShip = NULL;
	int numfound = 0;
	for (Ship *current = (Ship*)(newState->spaceObjects); current != 
		NULL; current = (Ship*)(current->next)){
		if(current->id == attackerID){
			attacker = current;
			numfound++;
		}
		if(current->id == deadID){
			deadShip = current;
			numfound++;
		}
		if(current->id < 0 || current->id >= newState->startingNumShips ||
			numfound == 2){
			break;
		}
	}
	if (numfound == 2 && attacker != NULL && deadShip != NULL){
		if (attacker->team != deadShip->team){
			attacker->kills++;
		}
	}
}



bool GameControl::vectorsAreEqual(Vector v, Vector u){
	return (equal(v.i, u.i, 0.00001) &&
		equal(v.i, u.i, 0.00001) &&
		equal(v.i, u.i, 0.00001) );
}