/**************************************************************************
*                                                                         *
* Class Name: NetworkClient                                               *
*                                                                         *
* Author: Sean Ferguson                                                   *
*                                                                         *
* Description: This class is the client side of the networking code.  It  *
*              will send player information to the server and receive game*
*              state from the server.  Some of this methods will probably *
*              be removed depending on how complicated it gets.           *
*                                                                         *
* Revisions:  Sean Ferguson -- Initial Version                            *
*             Sean Ferguson -- 10/3/1999                                  *
*             Sean Ferguson -- 11/8/1999 Working!!!                       *
*			  Sean Ferguson -- 11/10/99 Comments inserted and code done   *
/*************************************************************************/
#include "StdAfx.h"
#include "NetworkClient.h"

NetworkClient::NetworkClient() {
}

NetworkClient::~NetworkClient() {
    Close();
}

void NetworkClient::startGame(GameStateDestination* g) {
    gameStateDestination=g;
}

int NetworkClient::connectServer(char* server, char* playername) {
    int playerID;

    if(!AfxSocketInit()) {
        AfxMessageBox("Error on AfxSocketInit.", MB_OK);
        return -1;
    }
    
    if(!Create()) {
        AfxMessageBox("Error on creation of socket.", MB_OK);
        return -1;
    }
    
    if(!Connect(server,PORT)) {
      int x = GetLastError();
      char buff[200];
      sprintf(buff, "Error %d, on connection.", x);
      AfxMessageBox(buff , MB_OK);
      return -1;
    }

    strcpy((name),playername);

    Send(name,NAMESIZE);
    Receive(name,NAMESIZE);
	//Sends the name to the server and receives the clients id

    playerID = atoi(name);
    return playerID;
}

void NetworkClient::OnClose(int nErrorCode) {
    Close();
}

void NetworkClient::OnReceive(int nErrorCode) {
    Ship* tempShip;
    ShipState* state;
    char encryptedGameState[SIZE];
    char encryptedShipState[SHIPSSIZE];
    int receivedData;

    receivedData = Receive(encryptedGameState,SIZE);
    
    if(receivedData != SIZE && receivedData != -1) {
    //    AfxMessageBox("NetworkClient did not receive all data.  :(" , MB_OK);        
    }
    else if(receivedData == -1) {
    //    AfxMessageBox("NetworkClient hopes the game has ended  :(" , MB_OK);        
    }
    else if(encryptedGameState[0] != '0' ) {
    //    AfxMessageBox("NetworkClient got bad data.  :(" , MB_OK);        
    }
	//These ifs ensure that the client gets valid data, and if invalid,
	//ignores them.
	else {
		tempGameState = decryptGameState(encryptedGameState);
		state = gameStateDestination->updateGameState(tempGameState);
		encryptShipState(state,encryptedShipState);
		Send(encryptedShipState,SHIPSSIZE);
	}
}


