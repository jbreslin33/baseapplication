//parent
#include "clientPartidoStates.h"

//log
#include "../../../../tdreamsock/dreamSockLog.h"

//states
#include "../../../../../fsm/stateMachine.h"

//ability
#include "../clientPartido.h"


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

