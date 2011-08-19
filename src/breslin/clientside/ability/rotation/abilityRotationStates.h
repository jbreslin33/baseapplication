#ifndef ABILITYROTATIONSTATES_H
#define ABILITYROTATIONSTATES_H

/******************************************************
*				INCLUDES
********************************************************/
#include "abilityRotationState.h"

/******************************************************
*				FORWARD DECLARATIONS
********************************************************/
class AbilityRotation;

/******************************************************
*				PROCESS TICK
*
*				   STATES
*
********************************************************/


/******************************************************
*				GLOBAL
********************************************************/

class Global_ProcessTick_Rotation : public AbilityState
{
private:
  Global_ProcessTick_Rotation(){}
public:
  static Global_ProcessTick_Rotation* Instance();
  void enter  (AbilityRotation* abilityRotation);
  void execute(AbilityRotation* abilityRotation);
  void exit   (AbilityRotation* abilityRotation);
};

/******************************************************
*				NORMAL
********************************************************/
class Normal_ProcessTick_Rotation : public AbilityState
{
private:
  Normal_ProcessTick_Rotation(){}
public:
  static Normal_ProcessTick_Rotation* Instance();
  void enter  (AbilityRotation* abilityRotation);
  void execute(AbilityRotation* abilityRotation);
  void exit   (AbilityRotation* abilityRotation);
};

/******************************************************
*				CATCHUP
********************************************************/
class Catchup_ProcessTick_Rotation : public AbilityState
{
private:
  Catchup_ProcessTick_Rotation(){}
public:
  static Catchup_ProcessTick_Rotation* Instance();
  void enter  (AbilityRotation* abilityRotation);
  void execute(AbilityRotation* abilityRotation);
  void exit   (AbilityRotation* abilityRotation);
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

class Normal_InterpolateTick_Rotation : public AbilityState
{
private:
  Normal_InterpolateTick_Rotation(){}
public:
  static Normal_InterpolateTick_Rotation* Instance();
  void enter  (AbilityRotation* abilityRotation);
  void execute(AbilityRotation* abilityRotation);
  void exit   (AbilityRotation* abilityRotation);
};

/******************************************************
*				OFF
********************************************************/
class Off_InterpolateTick_Rotation : public AbilityState
{
private:
  Off_InterpolateTick_Rotation(){}
public:
  static Off_InterpolateTick_Rotation* Instance();
  void enter  (AbilityRotation* abilityRotation);
  void execute(AbilityRotation* abilityRotation);
  void exit   (AbilityRotation* abilityRotation);
};
#endif