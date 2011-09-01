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

class Global_ProcessTick_Move : public AbilityMoveState
{
private:
  Global_ProcessTick_Move(){}
public:
  static Global_ProcessTick_Move* Instance();
  void enter  (AbilityMove* abilityMove);
  void execute(AbilityMove* abilityMove);
  void exit   (AbilityMove* abilityMove);
};


/******************************************************
*				NORMAL
********************************************************/
class Normal_ProcessTick_Move : public AbilityMoveState
{
private:
  Normal_ProcessTick_Move(){}
public:
  static Normal_ProcessTick_Move* Instance();
  void enter  (AbilityMove* abilityMove);
  void execute(AbilityMove* abilityMove);
  void exit   (AbilityMove* abilityMove);
};


/******************************************************
*				CATCHUP
********************************************************/
class Catchup_ProcessTick_Move : public AbilityMoveState
{
private:
  Catchup_ProcessTick_Move(){}
public:
  static Catchup_ProcessTick_Move* Instance();
  void enter  (AbilityMove* abilityMove);
  void execute(AbilityMove* abilityMove);
  void exit   (AbilityMove* abilityMove);
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
class Normal_InterpolateTick_Move : public AbilityMoveState
{
private:
  Normal_InterpolateTick_Move(){}
public:
  static Normal_InterpolateTick_Move* Instance();
  void enter  (AbilityMove* abilityMove);
  void execute(AbilityMove* abilityMove);
  void exit   (AbilityMove* abilityMove);
};

#endif
