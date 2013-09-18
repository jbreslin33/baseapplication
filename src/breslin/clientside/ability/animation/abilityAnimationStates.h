#ifndef ABILITYANIMATIONSTATES_H
#define ABILITYANIMATIONSTATES_H

/******************************************************
*				INCLUDES
********************************************************/

//parent
#include "abilityAnimationState.h"

/******************************************************
*				FORWARD DECLARATIONS
********************************************************/

class Ability;

/******************************************************
*				INTERPOLATE
*
*				   STATES
*
********************************************************/


/******************************************************
*				IDLE
********************************************************/

class Idle_InterpolateTick_Animation : public AbilityAnimationState
{
private:
  Idle_InterpolateTick_Animation(){}
public:
  static Idle_InterpolateTick_Animation* Instance();
  void enter  (AbilityAnimationOgre* abilityAnimation);
  void execute(AbilityAnimationOgre* abilityAnimation);
  void exit   (AbilityAnimationOgre* abilityAnimation);
};


/******************************************************
*				RUN
********************************************************/
class Run_InterpolateTick_Animation : public AbilityAnimationState
{
private:
  Run_InterpolateTick_Animation(){}
public:
  static Run_InterpolateTick_Animation* Instance();
  void enter  (AbilityAnimationOgre* abilityAnimation);
  void execute(AbilityAnimationOgre* abilityAnimation);
  void exit   (AbilityAnimationOgre* abilityAnimation);
};

#endif
