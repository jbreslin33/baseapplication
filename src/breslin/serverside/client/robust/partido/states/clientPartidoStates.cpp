/***
these states are always on...as their is always a gamePartido..and these clients are in it. it really should handle the mechanics of quiz... 

*/
//parent
#include "clientPartidoStates.h"

//log
#include "../../../../tdreamsock/dreamSockLog.h"

//states
#include "../../../../../fsm/stateMachine.h"

//ability
#include "../clientPartido.h"

//server
#include "../../../../server/partido/serverPartido.h"

/*****************************************
*******       GLOBAL    ******************
****************************************/
GlobalClientPartido* GlobalClientPartido::Instance()
{
  static GlobalClientPartido instance;
  return &instance;
}
void GlobalClientPartido::enter(ClientPartido* clientPartido)
{
}
void GlobalClientPartido::execute(ClientPartido* clientPartido)
{

}
void GlobalClientPartido::exit(ClientPartido* clientPartido)
{
}
bool GlobalClientPartido::onLetter(ClientPartido* clientPartido, Letter* letter)
{
        return false;
}


/*****************************************
*******       CLIENT PARTIDO STATES    ******************       
****************************************/

/*****************************************
        WAITING FOR ANSWER       
****************************************/
Waiting_For_Answer* Waiting_For_Answer::Instance()
{
  static Waiting_For_Answer instance;
  return &instance; 
} 
void Waiting_For_Answer::enter(ClientPartido* clientPartido)
{
        LogString("WAITING_FOR_ANSWER::enter");
}       
void Waiting_For_Answer::execute(ClientPartido* clientPartido)
{
}
void Waiting_For_Answer::exit(ClientPartido* clientPartido)
{

}
bool Waiting_For_Answer::onLetter(ClientPartido* clientPartido, Letter* letter)
{
        return false;   
}

/*****************************************
        Sending_Question
****************************************/
Sending_Question* Sending_Question::Instance()
{
  static Sending_Question instance;
  return &instance;
}
void Sending_Question::enter(ClientPartido* clientPartido)
{
        LogString("Sending_Question::enter");
}
void Sending_Question::execute(ClientPartido* clientPartido)
{
}
void Sending_Question::exit(ClientPartido* clientPartido)
{
}
bool Sending_Question::onLetter(ClientPartido* clientPartido, Letter* letter)
{
        return false; 
}
/*****************************************
                GAME_PARTIDO_MODE               
****************************************/
Game_Partido_Mode* Game_Partido_Mode::Instance()
{
  static Game_Partido_Mode instance;
  return &instance;
}
void Game_Partido_Mode::enter(ClientPartido* clientPartido)
{
        LogString("Game_Partido_Mode::enter");
}
void Game_Partido_Mode::execute(ClientPartido* clientPartido)
{
}
void Game_Partido_Mode::exit(ClientPartido* clientPartido)
{
}
bool Game_Partido_Mode::onLetter(ClientPartido* clientPartido, Letter* letter)
{
        return false; 
}
