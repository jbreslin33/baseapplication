//parent
#include "shapePartidoStates.h"

//log
#include "../../../tdreamsock/dreamSockLog.h"

//states
#include "../../../../fsm/stateMachine.h"

//ability
#include "../shapePartido.h"

//server
#include "../../../server/server.h"

/*****************************************
*******       GLOBAL    ******************
****************************************/
GLOBAL_SHAPE_PARTIDO* GLOBAL_SHAPE_PARTIDO::Instance()
{
  static GLOBAL_SHAPE_PARTIDO instance;
  return &instance;
}
void GLOBAL_SHAPE_PARTIDO::enter(ShapePartido* shapePartido)
{
}
void GLOBAL_SHAPE_PARTIDO::execute(ShapePartido* shapePartido)
{

}
void GLOBAL_SHAPE_PARTIDO::exit(ShapePartido* shapePartido)
{
}
bool GLOBAL_SHAPE_PARTIDO::onLetter(ShapePartido* shapePartido, Letter* letter)
{
        return false;
}


/*****************************************
*******       CLIENT STATES    ******************	
****************************************/

/*****************************************
        AJAX_NODE       
****************************************/
BATTLE_SHAPE_PARTIDO* BATTLE_SHAPE_PARTIDO::Instance()
{
  static BATTLE_SHAPE_PARTIDO instance;
  return &instance; 
} 
void BATTLE_SHAPE_PARTIDO::enter(ShapePartido* shapePartido)
{
}       
void BATTLE_SHAPE_PARTIDO::execute(ShapePartido* shapePartido)
{
}
void BATTLE_SHAPE_PARTIDO::exit(ShapePartido* shapePartido)
{

}
bool BATTLE_SHAPE_PARTIDO::onLetter(ShapePartido* shapePartido, Letter* letter)
{
	return false;	
}


/*****************************************
	GAME_SHAPE_PARTIDO
****************************************/
GAME_SHAPE_PARTIDO* GAME_SHAPE_PARTIDO::Instance()
{
  static GAME_SHAPE_PARTIDO instance;
  return &instance;
}
void GAME_SHAPE_PARTIDO::enter(ShapePartido* shapePartido)
{
}
void GAME_SHAPE_PARTIDO::execute(ShapePartido* shapePartido)
{
}
void GAME_SHAPE_PARTIDO::exit(ShapePartido* shapePartido)
{
}
bool GAME_SHAPE_PARTIDO::onLetter(ShapePartido* shapePartido, Letter* letter)
{
        return false; 
}

