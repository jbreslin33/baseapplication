//parent
#include "clientStates.h"

//log
#include "../../tdreamsock/dreamSockLog.h"

//states
#include "../../../fsm/stateMachine.h"

//ability
#include "../client.h"


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
bool GlobalClient::onMessage(Client* client, const Telegram& msg)
{
        return true;
}


/*****************************************
*******       GAME CONTROL    ******************	
****************************************/
/*****************************************
	Logged_In
****************************************/
Logged_In* Logged_In::Instance()
{
  static Logged_In instance;
  return &instance;
}
void Logged_In::enter(Client* client)
{
}
void Logged_In::execute(Client* client)
{

}
void Logged_In::exit(Client* client)
{
}
bool Logged_In::onMessage(Client* client, const Telegram& msg)
{
	return true;
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
bool Logged_Out::onMessage(Client* client, const Telegram& msg)
{
	return true;
}


/*****************************************
*******       GAME CONTROL    ******************	
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
bool Human::onMessage(Client* client, const Telegram& msg)
{
	return true;
}

/*****************************************
	Computer
****************************************/
Computer* Computer::Instance()
{
	static Computer instance;
	return &instance;
}
void Computer::enter(Client* client)
{
LogString("enter computer");
}
void Computer::execute(Client* client)
{
	//client->mClientStateMachine->changeState(Human::Instance());
	client->checkForTimeout();
}
void Computer::exit(Client* client)
{
}
bool Computer::onMessage(Client* client, const Telegram& msg)
{
	return true;
}

