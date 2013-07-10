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
*******       CLIENT STATES    ******************	
****************************************/

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
bool Lobby::onMessage(Client* client, const Telegram& msg)
{
	return true;
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
bool Game_Mode::onMessage(Client* client, const Telegram& msg)
{
	return true;
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


/*****************************************
*******       PERMANENCE    ******************	
****************************************/

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

}
void Permanent::exit(Client* client)
{
}
bool Permanent::onMessage(Client* client, const Telegram& msg)
{
	return true;
}

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
bool Temporary::onMessage(Client* client, const Telegram& msg)
{
	return true;
}
