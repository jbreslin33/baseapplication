//parent
#include "clientStates.h"

//log
#include "../../tdreamsock/dreamSockLog.h"

//states
#include "../../../fsm/stateMachine.h"

//ability
#include "../client.h"

//server
#include "../../server/server.h"

/*****************************************
*******       GLOBAL    ******************
****************************************/
GlobalClient* GlobalClient::Instance()
{
  static GlobalClient instance;
  return &instance;
}
void GlobalClient::enter(Client* client)
{
}
void GlobalClient::execute(Client* client)
{

}
void GlobalClient::exit(Client* client)
{
}
bool GlobalClient::onLetter(Client* client, Letter* letter)
{
	Message* message = letter->mMessage;
	message->BeginReading();	
	int type = message->ReadByte();

	if (type == client->mServer->mMessageLogin)
	{
		client->mStateMachine->changeState(Lobby::Instance());
		return true;
	}
	
	if (type == client->mServer->mMessageLogout)
	{
		client->mStateMachine->changeState(Logged_Out::Instance());
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
void Temporary::enter(Client* client)
{
}
void Temporary::execute(Client* client)
{
}
void Temporary::exit(Client* client)
{
	
}
bool Temporary::onLetter(Client* client, Letter* letter)
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
void Ajax_Node::enter(Client* client)
{
}       
void Ajax_Node::execute(Client* client)
{
}
void Ajax_Node::exit(Client* client)
{

}
bool Ajax_Node::onLetter(Client* client, Letter* letter)
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
void Logged_Out::enter(Client* client)
{
}
void Logged_Out::execute(Client* client)
{

}
void Logged_Out::exit(Client* client)
{
}
bool Logged_Out::onLetter(Client* client, Letter* letter)
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
void Lobby::enter(Client* client)
{
}
void Lobby::execute(Client* client)
{

}
void Lobby::exit(Client* client)
{
}
bool Lobby::onLetter(Client* client, Letter* letter)
{
	Message* message = letter->mMessage;
	message->BeginReading();	
	int type = message->ReadByte();

	if (type == client->mServer->mMessageJoinGame)
	{
		int gameID = message->ReadByte();
		client->setGame(gameID);
		client->mStateMachine->changeState(Game_Mode::Instance());
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
void Game_Mode::enter(Client* client)
{
}
void Game_Mode::execute(Client* client)
{

}
void Game_Mode::exit(Client* client)
{
}
bool Game_Mode::onLetter(Client* client, Letter* letter)
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
void Human::enter(Client* client)
{
}
void Human::execute(Client* client)
{

}
void Human::exit(Client* client)
{
}
bool Human::onLetter(Client* client, Letter* letter)
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
void Computer_Mode::enter(Client* client)
{
}
void Computer_Mode::execute(Client* client)
{
}
void Computer_Mode::exit(Client* client)
{
}
bool Computer_Mode::onLetter(Client* client, Letter* letter)
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
void Initialize_Permanence::enter(Client* client)
{
}
void Initialize_Permanence::execute(Client* client)
{
}
void Initialize_Permanence::exit(Client* client)
{
}
bool Initialize_Permanence::onLetter(Client* client, Letter* letter)
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
void Permanent::enter(Client* client)
{
}
void Permanent::execute(Client* client)
{
	client->mStateMachine->changeState(Logged_Out::Instance());
}
void Permanent::exit(Client* client)
{
}
bool Permanent::onLetter(Client* client, Letter* letter)
{
        return false; 
}

