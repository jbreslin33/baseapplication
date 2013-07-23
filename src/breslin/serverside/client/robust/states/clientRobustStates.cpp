//parent
#include "clientRobustStates.h"

//log
#include "../../../tdreamsock/dreamSockLog.h"

//states
#include "../../../../fsm/stateMachine.h"

//ability
#include "../clientRobust.h"

//server
#include "../../../server/server.h"

/*****************************************
*******       GLOBAL    ******************
****************************************/
GLOBAL_CLIENT_ROBUST* GLOBAL_CLIENT_ROBUST::Instance()
{
  static GLOBAL_CLIENT_ROBUST instance;
  return &instance;
}
void GLOBAL_CLIENT_ROBUST::enter(ClientRobust* clientRobust)
{
}
void GLOBAL_CLIENT_ROBUST::execute(ClientRobust* clientRobust)
{

}
void GLOBAL_CLIENT_ROBUST::exit(ClientRobust* clientRobust)
{
}
bool GLOBAL_CLIENT_ROBUST::onLetter(ClientRobust* clientRobust, Letter* letter)
{
	//LogString("GLOBAL_CLIENT_ROBUST::onLetter");
	Message* message = letter->mMessage;
	message->BeginReading();	
	int type = message->ReadByte();

	if (type == clientRobust->mServer->mMessageLogin)
	{
		clientRobust->mClientRobustStateMachine->changeState(LOBBY::Instance());
		return true;
	}
	
	if (type == clientRobust->mServer->mMessageLogout)
	{
		clientRobust->mClientRobustStateMachine->changeState(LOGGED_OUT::Instance());
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
AJAX_NODE* AJAX_NODE::Instance()
{
  static AJAX_NODE instance;
  return &instance; 
} 
void AJAX_NODE::enter(ClientRobust* clientRobust)
{
}       
void AJAX_NODE::execute(ClientRobust* clientRobust)
{
}
void AJAX_NODE::exit(ClientRobust* clientRobust)
{

}
bool AJAX_NODE::onLetter(ClientRobust* clientRobust, Letter* letter)
{
	return false;	
}


/*****************************************
	LOGGED_OUT
****************************************/
LOGGED_OUT* LOGGED_OUT::Instance()
{
  static LOGGED_OUT instance;
  return &instance;
}
void LOGGED_OUT::enter(ClientRobust* clientRobust)
{
	//LogString("LOGGED_OUT::enter");
}
void LOGGED_OUT::execute(ClientRobust* clientRobust)
{
}
void LOGGED_OUT::exit(ClientRobust* clientRobust)
{
}
bool LOGGED_OUT::onLetter(ClientRobust* clientRobust, Letter* letter)
{
        return false; 
}

/*****************************************
	LOBBY
****************************************/
LOBBY* LOBBY::Instance()
{
  static LOBBY instance;
  return &instance;
}
void LOBBY::enter(ClientRobust* clientRobust)
{
	//LogString("LOBBY::enter");
}
void LOBBY::execute(ClientRobust* clientRobust)
{

}
void LOBBY::exit(ClientRobust* clientRobust)
{
}
bool LOBBY::onLetter(ClientRobust* clientRobust, Letter* letter)
{
	Message* message = letter->mMessage;
	message->BeginReading();	
	int type = message->ReadByte();

	if (type == clientRobust->mServer->mMessageJoinGame)
	{
		int gameID = message->ReadByte();
		//clientRobust->setGame(gameID);
		clientRobust->mClientRobustStateMachine->changeState(GAME_MODE::Instance());
		return true;
	}
        return false; 
}

/*****************************************
		GAME_MODE		
****************************************/
GAME_MODE* GAME_MODE::Instance()
{
  static GAME_MODE instance;
  return &instance;
}
void GAME_MODE::enter(ClientRobust* clientRobust)
{
	//LogString("GAME_MODE");
	clientRobust->mInGame = true;
}
void GAME_MODE::execute(ClientRobust* clientRobust)
{

}
void GAME_MODE::exit(ClientRobust* clientRobust)
{
	clientRobust->mInGame = false; 
}
bool GAME_MODE::onLetter(ClientRobust* clientRobust, Letter* letter)
{
        return false; 
}
