//parent
#include "clientStates.h"

//log
#include "../../tdreamsock/dreamSockLog.h"

//states
#include "clientStateMachine.h"

//ability
#include "../client.h"

/*****************************************
	Human_Client
****************************************/
Human_Client* Human_Client::Instance()
{
  static Human_Client instance;
  return &instance;
}
void Human_Client::enter(Client* client)
{
}
void Human_Client::execute(Client* client)
{

}
void Human_Client::exit(Client* client)
{
}

/*****************************************
	Computer_Client
****************************************/
Computer_Client* Computer_Client::Instance()
{
	static Computer_Client instance;
	return &instance;
}
void Computer_Client::enter(Client* client)
{
}
void Computer_Client::execute(Client* client)
{
	//client->mClientStateMachine->changeState(Human_Client::Instance());
	client->checkForTimeout();
}
void Computer_Client::exit(Client* client)
{
}

