#ifndef ABILITYMOVESTATES_H
#define ABILITYMOVESTATES_H
#include "abilityMoveState.h"

class Ability;

/******************************************************
*				PROCESS TICK
*
*				   STATES
*
********************************************************/


/******************************************************
*				GLOBAL
********************************************************/

class Global_ProcessTick_Move : public AbilityState
{
private:
  Global_ProcessTick_Move(){}
public:
  static Global_ProcessTick_Move* Instance();
  void enter  (Ability* ability);
  void execute(Ability* ability);
  void exit   (Ability* ability);
};


/******************************************************
*				NORMAL
********************************************************/
class Normal_ProcessTick_Move : public AbilityState
{
private:
  Normal_ProcessTick_Move(){}
public:
  static Normal_ProcessTick_Move* Instance();
  void enter  (Ability* ability);
  void execute(Ability* ability);
  void exit   (Ability* ability);
};


/******************************************************
*				CATCHUP
********************************************************/
class Catchup_ProcessTick_Move : public AbilityState
{
private:
  Catchup_ProcessTick_Move(){}
public:
  static Catchup_ProcessTick_Move* Instance();
  void enter  (Ability* ability);
  void execute(Ability* ability);
  void exit   (Ability* ability);
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
class Normal_InterpolateTick_Move : public AbilityState
{
private:
  Normal_InterpolateTick_Move(){}
public:
  static Normal_InterpolateTick_Move* Instance();
  void enter  (Ability* ability);
  void execute(Ability* ability);
  void exit   (Ability* ability);
};

#endif
