//parent
#include "clientPartidoStates.h"

//log
#include "../../../tdreamsock/dreamSockLog.h"

//states
#include "../../../../fsm/stateMachine.h"

//ability
#include "../clientPartido.h"

//server
#include "../../../server/server.h"

/*****************************************
*******       GLOBAL    ******************
****************************************/
GlobalClientPartido* GlobalClientPartido::Instance()
{
  static GlobalClientPartido instance;
  return &instance;
}
void GlobalClientPartido::enter(ClientPartido* clientPartido)
{
}
void GlobalClientPartido::execute(ClientPartido* clientPartido)
{

}
void GlobalClientPartido::exit(ClientPartido* clientPartido)
{
}
bool GlobalClientPartido::onLetter(ClientPartido* clientPartido, Letter* letter)
{
	LogString("GlobalClientPartido::onLetter");
	Message* message = letter->mMessage;
	message->BeginReading();	
	int type = message->ReadByte();

	if (type == clientPartido->mServer->mMessageLogin)
	{
		clientPartido->mClientPartidoStateMachine->changeState(Lobby::Instance());
		return true;
	}
	
	if (type == clientPartido->mServer->mMessageLogout)
	{
		clientPartido->mClientPartidoStateMachine->changeState(Logged_Out::Instance());
		return true;
	}


        return false;
}


/*****************************************
*******       CLIENT STATES    ******************	
****************************************/

/*****************************************
        AJAX_NODE       
****************************************/
/*
Ajax_Node* Ajax_Node::Instance()
{
  static Ajax_Node instance;
  return &instance; 
} 
void Ajax_Node::enter(ClientPartido* clientPartido)
{
}       
void Ajax_Node::execute(ClientPartido* clientPartido)
{
}
void Ajax_Node::exit(ClientPartido* clientPartido)
{

}
bool Ajax_Node::onLetter(ClientPartido* clientPartido, Letter* letter)
{
	return false;	
}

*/
/*****************************************
	Logged_Out
****************************************/
/*
Logged_Out* Logged_Out::Instance()
{
  static Logged_Out instance;
  return &instance;
}
void Logged_Out::enter(ClientPartido* clientPartido)
{
	LogString("Logged_Out::enter");
}
void Logged_Out::execute(ClientPartido* clientPartido)
{
}
void Logged_Out::exit(ClientPartido* clientPartido)
{
}
bool Logged_Out::onLetter(ClientPartido* clientPartido, Letter* letter)
{
        return false; 
}
*/
/*****************************************
	Lobby
****************************************/
/*
Lobby* Lobby::Instance()
{
  static Lobby instance;
  return &instance;
}
void Lobby::enter(ClientPartido* clientPartido)
{
	LogString("Lobby::enter");
}
void Lobby::execute(ClientPartido* clientPartido)
{

}
void Lobby::exit(ClientPartido* clientPartido)
{
}
bool Lobby::onLetter(ClientPartido* clientPartido, Letter* letter)
{
	Message* message = letter->mMessage;
	message->BeginReading();	
	int type = message->ReadByte();

	if (type == clientPartido->mServer->mMessageJoinGame)
	{
		int gameID = message->ReadByte();
		//clientPartido->setGame(gameID);
		clientPartido->mClientPartidoStateMachine->changeState(Game_Mode::Instance());
		return true;
	}
        return false; 
}
*/
/*****************************************
		GAME_MODE		
****************************************/
/*
Game_Mode* Game_Mode::Instance()
{
  static Game_Mode instance;
  return &instance;
}
void Game_Mode::enter(ClientPartido* clientPartido)
{
	LogString("Game_Mode");
	clientPartido->mInGame = true;
}
void Game_Mode::execute(ClientPartido* clientPartido)
{

}
void Game_Mode::exit(ClientPartido* clientPartido)
{
	clientPartido->mInGame = false; 
}
bool Game_Mode::onLetter(ClientPartido* clientPartido, Letter* letter)
{
        return false; 
}
*/
