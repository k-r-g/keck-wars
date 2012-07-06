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
#ifndef NETWORKCLIENT_H
#define NETWORKCLIENT_H

#include "StdAfx.h"
#include <afxsock.h>
#include "GameState.h"
#include "ShipState.h"
#include "Geometry.h"
#include "Conversion.h"

class NetworkClient : public CSocket {
    public:
        NetworkClient();
        //Constructor.

        ~NetworkClient();
        //Deconstructor.

        void startGame(GameStateDestination* g);
        //Starts the game.
        
        int connectServer(char* server, char* playername);
		//Used to connect to the server.  The char* server is the name
		//of the server to connect to in either ip form or name form.
		//The playername is just the players name to be given to the 
		//server upon connection.

        virtual void OnClose(int nErrorCode);
		//Automatically called when socket is closed.

        virtual void OnReceive(int nErrorCode); 
		//Automatically called when something is to be received.
		//It receives the gamestate string, and decodes it and then
		//passes it along to the shipInterface.
		
    private:
        char name[SHIPSSIZE];
		//Name of the client that joins which is passed along to the 
		//networkserver

        ShipState* shipState;
        //The ShipState which is received from shipinterface
        
        GameState* tempGameState;
		//The GameState which is decoded from the string gamestate.  It
		//is passed along to shipinterface

        GameStateDestination* gameStateDestination;
        //updateGameState is called on this.  It is a pointer to the 
		//shipinterface
};
#endif