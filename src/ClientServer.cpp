/**************************************************************************
*                                                                         *
* Class Name: ClientServer                                                *
*                                                                         *
* Author: Sean Ferguson                                                   *
*                                                                         *
* Description: This class is the server side for communiction with the    *
*              client code.  GameControl calls updateGameState on the     *
*              NetworkServer which in turn calls updateGameState on this  *
*              class.  This class sends the current gamestate to the      *
*              client, and receives the shipstate from the client, which  *
*              then gets returned to NetworkServer which returns it to    *
*              GameControl                                                *
* Revisions:  Sean Ferguson -- Initial Version                            *
*             Sean Ferguson -- 11/8/1999 Working!!!                       *
*			  Sean Ferguson -- 11/10/99 Comments inserted and code done   *
/*************************************************************************/
#include "StdAfx.h"
#include "NetworkServer.h"

ClientServer::ClientServer() {}

ClientServer::ClientServer(NetworkServer* ns) {
    networkServer = ns;
    shipState = new ShipState();
    shipState->next = NULL;
}

ClientServer::~ClientServer() {
    Close();
	delete shipState;
	shipState = NULL;
}

ShipState* ClientServer::updateGameState(char* gameState) {
    Send(gameState,SIZE);
    return shipState;
}

int ClientServer::joinGame() {
    int playerID = 0;    

    Receive(name,NAMESIZE);
    playerID = networkServer->setupGame->validateClient(name);
    _itoa(playerID,id,10);
    Send(id,NAMESIZE);

    shipState->id = playerID;
    return playerID;
}

void ClientServer::OnReceive(int nErrorCode) {
    int receivedData;

    receivedData = Receive(ships,SHIPSSIZE);

    if(receivedData != SHIPSSIZE && receivedData != -1) {
        //AfxMessageBox("ClientServer did not receive all data.  :(" , MB_OK);        
    }
    else if(ships[0] != '3') {
        //AfxMessageBox("ClientServer received the wrong stuff.  :(" , MB_OK);     
    }
	//Both of these ifs are used to ignore invalid data
	else {
		shipState = decryptShipState(ships,shipState);
		shipState->next = NULL;
	}
}

void ClientServer::OnClose(int nErrorCode) {
    delete shipState;
	shipState = NULL;
    Close();
}



