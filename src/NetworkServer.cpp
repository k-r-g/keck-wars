/**************************************************************************
* Class Name: NetworkServer                                               *
*                                                                         *
* Author: Sean Ferguson                                                   *
*                                                                         *
* Description: This class listens for clients to join, and when a client  *
*              joins, spawns a clientserver which will communicate with   *
*              the client for the rest of the game.  This class is a GSD  *
*              which gets updateGameState called on it, which in turns    *
*              calls it on all the clients, passing them the current game *
*              state.  Then it returns the shipstates to GameControl.     *
* Revisions:  Sean Ferguson -- Initial Version                            *
*             Sean Ferguson -- 11/8/1999 Working!!!                       *
*			  Sean Ferguson -- 11/10/99 Comments inserted and code done   *
/*************************************************************************/
#include "stdafx.h"
#include "NetworkServer.h"

NetworkServer::NetworkServer() {}

NetworkServer::NetworkServer(SetupGame* setup) {
    currentPlayer = 0;
    totalPlayers = 0;
    setupGame = setup;
    shipState = new ShipState();
    shipState->next = NULL;

    AfxSocketInit();
    Create(PORT);
    Listen();
}

NetworkServer::~NetworkServer() {
    Close();
	delete shipState;
	shipState = NULL;
	for(int i = 0;i<totalPlayers;i++) {
		delete clients[i].client;
		clients[i].client = NULL;
		clients[i].playerID = 0;
	}
}

void NetworkServer::OnClose(int nErrorCode) {
    Close();
}

ShipState* NetworkServer::updateGameState(GameState *gameState) {
    ShipState* tail;
    ShipState* temp;
    
    tail = shipState;

    if(totalPlayers == 0) {
        return NULL;
    } 
	//If there are no clients in the game, the networkserver doesnt need
	//to communicate with clients.

    encryptGameState(gameState,encryptedGameState);

    for(int i = 0;i < totalPlayers; i++) {
	    temp = clients[i].client->updateGameState(encryptedGameState);
        copyShipState(temp,tail);
        
        if(i == totalPlayers-1) {
            tail->next = NULL;
        }
		//If done with all clients, end the shipState
        else {
            if(tail->next == NULL) {
                tail->next = new ShipState();
            }
            tail = tail->next;
        }
    }
    return shipState;
}

void NetworkServer::OnAccept(int nErrorCode) {
    clients[currentPlayer].client = new ClientServer(this);

    if(!Accept(*(clients[currentPlayer].client))) {
        AfxMessageBox("Accept failed.", MB_OK);
    }

    clients[currentPlayer].playerID = 
        clients[currentPlayer].client->joinGame();

    if(clients[currentPlayer].playerID == -1) {
        clients[currentPlayer].client->Close();
        delete(clients[currentPlayer].client);
        AfxMessageBox("Client Rejected.", MB_OK);
    }
    else {
        currentPlayer++;
        totalPlayers++;
    }
}

void NetworkServer::startGame() {
    Close();
}

void NetworkServer::cancelGame() {
    Close();
}

void NetworkServer::kickPlayer(char* player) {
//Never implemented 
}