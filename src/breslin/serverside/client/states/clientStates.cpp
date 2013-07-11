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
/*
	if (letter->mMessageNumber == 1)	
	{
		LogString("got msg 1");
		client->mStateMachine->changeState(Lobby::Instance());
	}
*/
        return true;
}


