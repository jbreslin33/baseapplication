//parent
#include "battleStates.h"

//log
#include "../../tdreamsock/dreamSockLog.h"

//battle
#include "../battle.h"

/*****************************************
*******       GLOBAL    ******************
****************************************/
GLOBAL_BATTLE* GLOBAL_BATTLE::Instance()
{
  static GLOBAL_BATTLE instance;
  return &instance;
}
void GLOBAL_BATTLE::enter(Battle* battle)
{
}
void GLOBAL_BATTLE::execute(Battle* battle)
{

}
void GLOBAL_BATTLE::exit(Battle* battle)
{
}
bool GLOBAL_BATTLE::onLetter(Battle* battle, Letter* letter)
{
        return true;
}


/*****************************************
	NORMAL_BATTLE
****************************************/
NORMAL_BATTLE* NORMAL_BATTLE::Instance()
{
  static NORMAL_BATTLE instance;
  return &instance;
}
void NORMAL_BATTLE::enter(Battle* battle)
{
}
void NORMAL_BATTLE::execute(Battle* battle)
{
}
void NORMAL_BATTLE::exit(Battle* battle)
{
}
bool NORMAL_BATTLE::onLetter(Battle* battle, Letter* letter)
{
        return true;
}

/*****************************************
	INIT_BATTLE
****************************************/
INIT_BATTLE* INIT_BATTLE::Instance()
{
	static INIT_BATTLE instance;
	return &instance;
}
void INIT_BATTLE::enter(Battle* battle)
{
}
void INIT_BATTLE::execute(Battle* battle)
{
}
void INIT_BATTLE::exit(Battle* battle)
{
}
bool INIT_BATTLE::onLetter(Battle* battle, Letter* letter)
{
        return true;
}

/*****************************************
	OVER_BATTLE
****************************************/
OVER_BATTLE* OVER_BATTLE::Instance()
{
	static OVER_BATTLE instance;
	return &instance;
}
void OVER_BATTLE::enter(Battle* battle)
{
}
void OVER_BATTLE::execute(Battle* battle)
{
}
void OVER_BATTLE::exit(Battle* battle)
{
}
bool OVER_BATTLE::onLetter(Battle* battle, Letter* letter)
{
        return true;
}
