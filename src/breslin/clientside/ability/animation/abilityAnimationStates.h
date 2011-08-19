#ifndef ABILITYANIMATIONSTATES_H
#define ABILITYANIMATIONSTATES_H
#include "../../states/stateShapeDynamic.h"

class ShapeDynamic;

/******************************************************
*				INTERPOLATE
*
*				   STATES
*
********************************************************/


/******************************************************
*				IDLE
********************************************************/

class Idle_InterpolateTick_Animation : public ShapeDynamicState
{
private:
  Idle_InterpolateTick_Animation(){}
public:
  static Idle_InterpolateTick_Animation* Instance();
  void enter  (ShapeDynamic* shapeDynamic);
  void execute(ShapeDynamic* shapeDynamic);
  void exit   (ShapeDynamic* shapeDynamic);
};


/******************************************************
*				RUN
********************************************************/
class Run_InterpolateTick_Animation : public ShapeDynamicState
{
private:
  Run_InterpolateTick_Animation(){}
public:
  static Run_InterpolateTick_Animation* Instance();
  void enter  (ShapeDynamic* shapeDynamic);
  void execute(ShapeDynamic* shapeDynamic);
  void exit   (ShapeDynamic* shapeDynamic);
};

#endif