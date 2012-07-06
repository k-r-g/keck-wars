#include "StdAfx.h"
#include <afxsock.h>
#include "SetupGame.h"
#include "Conversion.h"

class SetupGame;
class ClientServer;
class NetworkServer;
/**************************************************************************
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
#ifndef NETWORKSERVER_H
#define NETWORKSERVER_H

class ClientServer : public CSocket {
    public:
        ClientServer();
		//Constructor of the ClientServer, not really used in networking

        ClientServer(NetworkServer* ns);
		//Constructor, used by Clientserver as the class that speaks with
		//the network clients

        ~ClientServer();
		//Deconstructor
        
        ShipState* updateGameState(char gameState[SIZE]);
		//NetworkServer calls this to send the new gamestate to the 
		//clients.  It is received as a string so that it can be sent over
		//the network and received by the client.

        int joinGame();
		//When a client wants to join a game, they must send over their
		//name.  joinGame then asks setupgame if the player can join.
		//An integer is returned to the client which is their id.

        virtual void OnReceive(int nErrorCode);
		//Method that is automatically called when a receive happens.
		//It receives the shipstate from the player which is saved.

        virtual void OnClose(int nErrorCode);
		//Automatically called by MFC when the connection is closed.
		//It will cleanup the code.
        
    protected:
        char name[NAMESIZE];
		//Name of the client

        char ships[SHIPSSIZE];
		//Current shipstate to be received as a string

        char id[NAMESIZE];
		//The id to be sent as a string

        int playerID;
		//The integer of the player id

        NetworkServer* networkServer;
		//The pointer to network server so that setupgame is accessible
                
        ShipState* shipState;
		//The state that is returned to NetworkServer
};

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
class NetworkServer : public GameStateDestination, public CAsyncSocket {
    public: 
        NetworkServer();
		//Default constructor
        
        NetworkServer(SetupGame* setup);
        //Constructor, will initialize the networking.  
        
        ~NetworkServer();
        //Deconstructor, closes all networking.

        ShipState* updateGameState(GameState *gameState);
        //From the GameStateDestination, tells me to send out the Game
		//State.  Calls updateGamState on the ClientServers

        virtual void OnClose(int nErrorCode);
		//Automatically called when the socket is closed

        virtual void OnAccept(int nErrorCode);
		//Automaticaly called when a connection is attempted.  It creates
		//the clientserver for the client
        
        void startGame();
        //Starts the game.

        void cancelGame();
        //Ends the game and cleans up all open sockets.

        void kickPlayer(char* player);
        //Setupgame can kick a player, which it has to notify me about.
		//Then the Client is notified and they are removed from the 
		//game.

        SetupGame* setupGame;
		//Pointer to setupgame to be used by the clientserver

    private:
        char encryptedGameState[SIZE];
		//The gamestate converted to a string

        struct clientServer {
            ClientServer* client;
            int playerID;
	    };
		//This struct is where the clientserver goes.  It is initialized
		//when a client joins game.

        clientServer clients[8];
		//The array of clients

        int currentPlayer,totalPlayers;
		//Stores how many players are in game
        
        ShipState* shipState;
		//The shipstate which is given back to update gamestate
};
#endif