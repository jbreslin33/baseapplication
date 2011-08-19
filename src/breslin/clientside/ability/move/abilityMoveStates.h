#ifndef ABILITYMOVESTATES_H
#define ABILITYMOVESTATES_H
#include "../../states/stateShapeDynamic.h"

class ShapeDynamic;

/******************************************************
*				PROCESS TICK
*
*				   STATES
*
********************************************************/


/******************************************************
*				GLOBAL
********************************************************/

class Global_ProcessTick_Move : public ShapeDynamicState
{
private:
  Global_ProcessTick_Move(){}
public:
  static Global_ProcessTick_Move* Instance();
  void enter  (ShapeDynamic* shapeDynamic);
  void execute(ShapeDynamic* shapeDynamic);
  void exit   (ShapeDynamic* shapeDynamic);
};


/******************************************************
*				NORMAL
********************************************************/
class Normal_ProcessTick_Move : public ShapeDynamicState
{
private:
  Normal_ProcessTick_Move(){}
public:
  static Normal_ProcessTick_Move* Instance();
  void enter  (ShapeDynamic* shapeDynamic);
  void execute(ShapeDynamic* shapeDynamic);
  void exit   (ShapeDynamic* shapeDynamic);
};


/******************************************************
*				CATCHUP
********************************************************/
class Catchup_ProcessTick_Move : public ShapeDynamicState
{
private:
  Catchup_ProcessTick_Move(){}
public:
  static Catchup_ProcessTick_Move* Instance();
  void enter  (ShapeDynamic* shapeDynamic);
  void execute(ShapeDynamic* shapeDynamic);
  void exit   (ShapeDynamic* shapeDynamic);
};

/******************************************************
*				INTERPOLATE TICK
*
*				   STATES
*
********************************************************/

/******************************************************
*				NORMAL
********************************************************/
class Normal_InterpolateTick_Move : public ShapeDynamicState
{
private:
  Normal_InterpolateTick_Move(){}
public:
  static Normal_InterpolateTick_Move* Instance();
  void enter  (ShapeDynamic* shapeDynamic);
  void execute(ShapeDynamic* shapeDynamic);
  void exit   (ShapeDynamic* shapeDynamic);
};

#endif
