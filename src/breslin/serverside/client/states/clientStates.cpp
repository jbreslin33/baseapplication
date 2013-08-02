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
	return false;
}

/*****************************************
*******       CLIENT STATES    ******************	
****************************************/

/*****************************************
        DISCONNECTED      
****************************************/
Disconnected* Disconnected::Instance()
{
  static Disconnected instance;
  return &instance; 
} 
void Disconnected::enter(Client* client)
{
}       
void Disconnected::execute(Client* client)
{
}
void Disconnected::exit(Client* client)
{

}
bool Disconnected::onLetter(Client* client, Letter* letter)
{
	return false;	
}

/*****************************************
	CONNECTING
****************************************/
Connecting* Connecting::Instance()
{
  static Connecting instance;
  return &instance;
}
void Connecting::enter(Client* client)
{
}
void Connecting::execute(Client* client)
{
}
void Connecting::exit(Client* client)
{
}
bool Connecting::onLetter(Client* client, Letter* letter)
{
	return false;	
}

/*****************************************
	CONNECTED	
****************************************/
Connected* Connected::Instance()
{
  static Connected instance;
  return &instance;
}
void Connected::enter(Client* client)
{
}
void Connected::execute(Client* client)
{
}
void Connected::exit(Client* client)
{
}
bool Connected::onLetter(Client* client, Letter* letter)
{
	return false;	
}
