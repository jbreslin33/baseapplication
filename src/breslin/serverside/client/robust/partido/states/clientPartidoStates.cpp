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

//shapePartido
#include "../../../../shape/partido/shapePartido.h"

//question
#include "../../../../question/question.h"

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
                GAME_PARTIDO_MODE               
****************************************/
Game_Partido_Mode* Game_Partido_Mode::Instance()
{
  static Game_Partido_Mode instance;
  return &instance;
}
void Game_Partido_Mode::enter(ClientPartido* clientPartido)
{
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
/***************************************
       	Battle
****************************************/
CLIENT_PARTIDO_BATTLE* CLIENT_PARTIDO_BATTLE::Instance()
{
  static CLIENT_PARTIDO_BATTLE instance;
  return &instance;
}
void CLIENT_PARTIDO_BATTLE::enter(ClientPartido* clientPartido)
{
}
void CLIENT_PARTIDO_BATTLE::execute(ClientPartido* clientPartido)
{
}
void CLIENT_PARTIDO_BATTLE::exit(ClientPartido* clientPartido)
{
}
bool CLIENT_PARTIDO_BATTLE::onLetter(ClientPartido* clientPartido, Letter* letter)
{
        return false;
}


