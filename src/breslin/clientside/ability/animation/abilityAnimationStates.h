#ifndef ABILITYANIMATIONSTATES_H
#define ABILITYANIMATIONSTATES_H

/******************************************************
*				INCLUDES
********************************************************/

//parent
#include "../abilityState.h"

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

class Idle_InterpolateTick_Animation : public AbilityState
{
private:
  Idle_InterpolateTick_Animation(){}
public:
  static Idle_InterpolateTick_Animation* Instance();
  void enter  (Ability* ability);
  void execute(Ability* ability);
  void exit   (Ability* ability);
};


/******************************************************
*				RUN
********************************************************/
class Run_InterpolateTick_Animation : public AbilityState
{
private:
  Run_InterpolateTick_Animation(){}
public:
  static Run_InterpolateTick_Animation* Instance();
  void enter  (Ability* ability);
  void execute(Ability* ability);
  void exit   (Ability* ability);
};

#endif