//header
#include "gamePartidoStates.h"

//log
#include "../../../tdreamsock/dreamSockLog.h"

//gamePartido
#include "../../../application/applicationBreslin.h"

//gamePartido
#include "../gamePartido.h"

//shape
#include "../../../shape/shape.h"

//utility
#include <math.h>


/******************** GLOBAL_PARTIDO_GAME *****************/

GLOBAL_PARTIDO_GAME* GLOBAL_PARTIDO_GAME::Instance()
{
  static GLOBAL_PARTIDO_GAME instance;
  return &instance;
}
void GLOBAL_PARTIDO_GAME::enter(GamePartido* gamePartido)
{

}
void GLOBAL_PARTIDO_GAME::execute(GamePartido* gamePartido)
{
}
void GLOBAL_PARTIDO_GAME::exit(GamePartido* gamePartido)
{
}
bool GLOBAL_PARTIDO_GAME::onLetter(GamePartido* gamePartido, Letter* letter)
{
        return true;
}

/******************** BATTLE_GAME *****************/

BATTLE_GAME* BATTLE_GAME::Instance()
{
  static BATTLE_GAME instance;
  return &instance;
}
void BATTLE_GAME::enter(GamePartido* gamePartido)
{
}
void BATTLE_GAME::execute(GamePartido* gamePartido)
{

}
void BATTLE_GAME::exit(GamePartido* gamePartido)
{
}
bool BATTLE_GAME::onLetter(GamePartido* gamePartido, Letter* letter)
{
        return true;
}

/******************** PLAY_PARTIDO_GAME *****************/

PLAY_PARTIDO_GAME* PLAY_PARTIDO_GAME::Instance()
{
        static PLAY_PARTIDO_GAME instance;
        return &instance;
}
void PLAY_PARTIDO_GAME::enter(GamePartido* gamePartido)
{
}
void PLAY_PARTIDO_GAME::execute(GamePartido* gamePartido)
{

}
void PLAY_PARTIDO_GAME::exit(GamePartido* gamePartido)
{
}
bool PLAY_PARTIDO_GAME::onLetter(GamePartido* gamePartido, Letter* letter)
{
        return true;
}


/******************** RESET_PARTIDO_GAME *****************/

RESET_PARTIDO_GAME* RESET_PARTIDO_GAME::Instance()
{
  static RESET_PARTIDO_GAME instance;
  return &instance;
}
void RESET_PARTIDO_GAME::enter(GamePartido* gamePartido)
{

}
void RESET_PARTIDO_GAME::execute(GamePartido* gamePartido)
{
}
void RESET_PARTIDO_GAME::exit(GamePartido* gamePartido)
{
}
bool RESET_PARTIDO_GAME::onLetter(GamePartido* gamePartido, Letter* letter)
{
        return true;
}

/******************** SHOWCORRECTANSWER_PARTIDO_GAME *****************/

SHOWCORRECTANSWER_PARTIDO_GAME* SHOWCORRECTANSWER_PARTIDO_GAME::Instance()
{
  static SHOWCORRECTANSWER_PARTIDO_GAME instance;
  return &instance;
}
void SHOWCORRECTANSWER_PARTIDO_GAME::enter(GamePartido* gamePartido)
{

}
void SHOWCORRECTANSWER_PARTIDO_GAME::execute(GamePartido* gamePartido)
{
}
void SHOWCORRECTANSWER_PARTIDO_GAME::exit(GamePartido* gamePartido)
{
}
bool SHOWCORRECTANSWER_PARTIDO_GAME::onLetter(GamePartido* gamePartido, Letter* letter)
{
        return true;
}

