//parent
#include "clientStableStates.h"

//log
#include "../../../tdreamsock/dreamSockLog.h"

//states
#include "../../../../fsm/stateMachine.h"

//ability
#include "../clientStable.h"

//server
#include "../../../server/server.h"

/*****************************************
*******       GLOBAL    ******************
****************************************/
GlobalClientStable* GlobalClientStable::Instance()
{
  static GlobalClientStable instance;
  return &instance;
}
void GlobalClientStable::enter(ClientStable* clientStable)
{
}
void GlobalClientStable::execute(ClientStable* clientStable)
{

}
void GlobalClientStable::exit(ClientStable* clientStable)
{
}
bool GlobalClientStable::onLetter(ClientStable* clientStable, Letter* letter)
{
/*
	if (letter->mMessageNumber == 1)	
	{
		LogString("got msg 1");
		clientStable->mStateMachine->changeState(Lobby::Instance());
	}
*/
        return true;
}
