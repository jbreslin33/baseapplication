//parent
#include "animationStates.h"

//log
#include "../../tdreamsock/dreamSockLog.h"

//shape
#include "../../shape/shape.h"

//billboard
#include "../../billboard/objectTitle.h"

//animation
#include "../animationBreslin.h"

//command
#include "../../command/command.h"

IDLE_INTERPOLATETICK_ANIMATION* IDLE_INTERPOLATETICK_ANIMATION::Instance()
{
  static IDLE_INTERPOLATETICK_ANIMATION instance;
  return &instance;
}
void IDLE_INTERPOLATETICK_ANIMATION::enter(AnimationBreslin* animation)
{
	animation->idleEnter();
}

void IDLE_INTERPOLATETICK_ANIMATION::execute(AnimationBreslin* animation)
{
	animation->idleExecute();
}
void IDLE_INTERPOLATETICK_ANIMATION::exit(AnimationBreslin* animation)
{
}

bool IDLE_INTERPOLATETICK_ANIMATION::onLetter(AnimationBreslin* animationBreslin, Letter* letter)
{
        return true;
}

RUN_INTERPOLATETICK_ANIMATION* RUN_INTERPOLATETICK_ANIMATION::Instance()
{
  static RUN_INTERPOLATETICK_ANIMATION instance;
  return &instance;
}
void RUN_INTERPOLATETICK_ANIMATION::enter(AnimationBreslin* animation)
{
	animation->runEnter(); 
}
void RUN_INTERPOLATETICK_ANIMATION::execute(AnimationBreslin* animation)
{
	animation->runExecute();		
}

void RUN_INTERPOLATETICK_ANIMATION::exit(AnimationBreslin* animation)
{
}

bool RUN_INTERPOLATETICK_ANIMATION::onLetter(AnimationBreslin* animationBreslin, Letter* letter)
{
        return true;
}
