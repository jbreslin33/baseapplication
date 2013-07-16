//parent
#include "steeringStates.h"

//log
#include "../../tdreamsock/dreamSockLog.h"

//steering
#include "../steering.h"

//server
#include "../../server/server.h"

//game
#include "../../game/game.h"

//shape
#include "../../shape/shape.h"

//vector3D
#include "../../../math/vector3D.h"

//move
#include "../../move/move.h"

/*****************************************
*******       GLOBAL    ******************
****************************************/
GlobalSteering* GlobalSteering::Instance()
{
  static GlobalSteering instance;
  return &instance;
}
void GlobalSteering::enter(Steering* steering)
{
}
void GlobalSteering::execute(Steering* steering)
{

}
void GlobalSteering::exit(Steering* steering)
{
}
bool GlobalSteering::onLetter(Steering* steering, Letter* letter)
{
        return true;
}


/*****************************************
	Normal_Steering
****************************************/
Normal_Steering* Normal_Steering::Instance()
{
  static Normal_Steering instance;
  return &instance;
}
void Normal_Steering::enter(Steering* steering)
{
	//LogString("Normal");
}
void Normal_Steering::execute(Steering* steering)
{
}
void Normal_Steering::exit(Steering* steering)
{
}
bool Normal_Steering::onLetter(Steering* steering, Letter* letter)
{
        return true;
}

/*****************************************
	No_Steering
****************************************/
No_Steering* No_Steering::Instance()
{
	static No_Steering instance;
	return &instance;
}
void No_Steering::enter(Steering* steering)
{
	//LogString("No");
}
void No_Steering::execute(Steering* steering)
{
}
void No_Steering::exit(Steering* steering)
{
}
bool No_Steering::onLetter(Steering* steering, Letter* letter)
{
        return true;
}

