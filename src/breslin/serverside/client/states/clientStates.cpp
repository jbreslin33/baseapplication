//parent
#include "clientStates.h"

//log
#include "../../tdreamsock/dreamSockLog.h"

//states
#include "clientStateMachine.h"

//ability
#include "../client.h"

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
}
void Computer::execute(Client* client)
{
	//client->mClientStateMachine->changeState(Human::Instance());
	client->checkForTimeout();
}
void Computer::exit(Client* client)
{
}

