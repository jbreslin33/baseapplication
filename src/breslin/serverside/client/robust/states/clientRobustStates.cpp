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
GlobalClientRobust* GlobalClientRobust::Instance()
{
  static GlobalClientRobust instance;
  return &instance;
}
void GlobalClientRobust::enter(ClientRobust* clientRobust)
{
}
void GlobalClientRobust::execute(ClientRobust* clientRobust)
{

}
void GlobalClientRobust::exit(ClientRobust* clientRobust)
{
}
bool GlobalClientRobust::onLetter(ClientRobust* clientRobust, Letter* letter)
{
	LogString("GlobalClientRobust::onLetter");
	Message* message = letter->mMessage;
	message->BeginReading();	
	int type = message->ReadByte();

	if (type == clientRobust->mServer->mMessageLogin)
	{
		clientRobust->mClientRobustStateMachine->changeState(Lobby::Instance());
		return true;
	}
	
	if (type == clientRobust->mServer->mMessageLogout)
	{
		clientRobust->mClientRobustStateMachine->changeState(Logged_Out::Instance());
		return true;
	}


        return false;
}


/*****************************************
*******       CLIENT STATES    ******************	
****************************************/

/*****************************************
	TEMPORARY	
****************************************/
Temporary* Temporary::Instance()
{
  static Temporary instance;
  return &instance;
}
void Temporary::enter(ClientRobust* clientRobust)
{
}
void Temporary::execute(ClientRobust* clientRobust)
{
}
void Temporary::exit(ClientRobust* clientRobust)
{
	
}
bool Temporary::onLetter(ClientRobust* clientRobust, Letter* letter)
{
	return false;	
}

/*****************************************
        AJAX_NODE       
****************************************/
Ajax_Node* Ajax_Node::Instance()
{
  static Ajax_Node instance;
  return &instance; 
} 
void Ajax_Node::enter(ClientRobust* clientRobust)
{
}       
void Ajax_Node::execute(ClientRobust* clientRobust)
{
}
void Ajax_Node::exit(ClientRobust* clientRobust)
{

}
bool Ajax_Node::onLetter(ClientRobust* clientRobust, Letter* letter)
{
	return false;	
}


/*****************************************
	Logged_Out
****************************************/
Logged_Out* Logged_Out::Instance()
{
  static Logged_Out instance;
  return &instance;
}
void Logged_Out::enter(ClientRobust* clientRobust)
{
	LogString("Logged_Out::enter");
}
void Logged_Out::execute(ClientRobust* clientRobust)
{
}
void Logged_Out::exit(ClientRobust* clientRobust)
{
}
bool Logged_Out::onLetter(ClientRobust* clientRobust, Letter* letter)
{
        return false; 
}

/*****************************************
	Lobby
****************************************/
Lobby* Lobby::Instance()
{
  static Lobby instance;
  return &instance;
}
void Lobby::enter(ClientRobust* clientRobust)
{
	LogString("Lobby::enter");
}
void Lobby::execute(ClientRobust* clientRobust)
{

}
void Lobby::exit(ClientRobust* clientRobust)
{
}
bool Lobby::onLetter(ClientRobust* clientRobust, Letter* letter)
{
	Message* message = letter->mMessage;
	message->BeginReading();	
	int type = message->ReadByte();

	if (type == clientRobust->mServer->mMessageJoinGame)
	{
		int gameID = message->ReadByte();
		//clientRobust->setGame(gameID);
		clientRobust->mClientRobustStateMachine->changeState(Game_Mode::Instance());
		return true;
	}
        return false; 
}

/*****************************************
		GAME_MODE		
****************************************/
Game_Mode* Game_Mode::Instance()
{
  static Game_Mode instance;
  return &instance;
}
void Game_Mode::enter(ClientRobust* clientRobust)
{
	LogString("Game_Mode");
	clientRobust->mInGame = true;
}
void Game_Mode::execute(ClientRobust* clientRobust)
{

}
void Game_Mode::exit(ClientRobust* clientRobust)
{
	clientRobust->mInGame = false; 
}
bool Game_Mode::onLetter(ClientRobust* clientRobust, Letter* letter)
{
        return false; 
}

/*****************************************
*******       CONTROL    ******************	
****************************************/

/*****************************************
	Human
****************************************/
Human* Human::Instance()
{
  static Human instance;
  return &instance;
}
void Human::enter(ClientRobust* clientRobust)
{
}
void Human::execute(ClientRobust* clientRobust)
{

}
void Human::exit(ClientRobust* clientRobust)
{
}
bool Human::onLetter(ClientRobust* clientRobust, Letter* letter)
{
        return false; 
}


/*****************************************
	Computer
****************************************/
Computer_Mode* Computer_Mode::Instance()
{
	static Computer_Mode instance;
	return &instance;
}
void Computer_Mode::enter(ClientRobust* clientRobust)
{
}
void Computer_Mode::execute(ClientRobust* clientRobust)
{
}
void Computer_Mode::exit(ClientRobust* clientRobust)
{
}
bool Computer_Mode::onLetter(ClientRobust* clientRobust, Letter* letter)
{
        return false; 
}


/*****************************************
*******       PERMANENCE    ******************	
****************************************/
/*****************************************
        INITIALIZE_PERMANENCE
****************************************/
Initialize_Permanence* Initialize_Permanence::Instance()
{
  static Initialize_Permanence instance;
  return &instance;
}
void Initialize_Permanence::enter(ClientRobust* clientRobust)
{
}
void Initialize_Permanence::execute(ClientRobust* clientRobust)
{
}
void Initialize_Permanence::exit(ClientRobust* clientRobust)
{
}
bool Initialize_Permanence::onLetter(ClientRobust* clientRobust, Letter* letter)
{
        return false; 
}

/*****************************************
	PERMANENT	
****************************************/
Permanent* Permanent::Instance()
{
  static Permanent instance;
  return &instance;
}
void Permanent::enter(ClientRobust* clientRobust)
{
}
void Permanent::execute(ClientRobust* clientRobust)
{
	clientRobust->mClientRobustStateMachine->changeState(Logged_Out::Instance());
}
void Permanent::exit(ClientRobust* clientRobust)
{
}
bool Permanent::onLetter(ClientRobust* clientRobust, Letter* letter)
{
        return false; 
}

