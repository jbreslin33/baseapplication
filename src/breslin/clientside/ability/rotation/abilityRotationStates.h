#ifndef ABILITYROTATIONSTATES_H
#define ABILITYROTATIONSTATES_H

/******************************************************
*				INCLUDES
********************************************************/
#include "../../states/stateShapeDynamic.h"

/******************************************************
*				FORWARD DECLARATIONS
********************************************************/
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

class Global_ProcessTick_Rotation : public ShapeDynamicState
{
private:
  Global_ProcessTick_Rotation(){}
public:
  static Global_ProcessTick_Rotation* Instance();
  void enter  (ShapeDynamic* shapeDynamic);
  void execute(ShapeDynamic* shapeDynamic);
  void exit   (ShapeDynamic* shapeDynamic);
};

/******************************************************
*				NORMAL
********************************************************/
class Normal_ProcessTick_Rotation : public ShapeDynamicState
{
private:
  Normal_ProcessTick_Rotation(){}
public:
  static Normal_ProcessTick_Rotation* Instance();
  void enter  (ShapeDynamic* shapeDynamic);
  void execute(ShapeDynamic* shapeDynamic);
  void exit   (ShapeDynamic* shapeDynamic);
};

/******************************************************
*				CATCHUP
********************************************************/
class Catchup_ProcessTick_Rotation : public ShapeDynamicState
{
private:
  Catchup_ProcessTick_Rotation(){}
public:
  static Catchup_ProcessTick_Rotation* Instance();
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

class Normal_InterpolateTick_Rotation : public ShapeDynamicState
{
private:
  Normal_InterpolateTick_Rotation(){}
public:
  static Normal_InterpolateTick_Rotation* Instance();
  void enter  (ShapeDynamic* shapeDynamic);
  void execute(ShapeDynamic* shapeDynamic);
  void exit   (ShapeDynamic* shapeDynamic);
};

/******************************************************
*				OFF
********************************************************/
class Off_InterpolateTick_Rotation : public ShapeDynamicState
{
private:
  Off_InterpolateTick_Rotation(){}
public:
  static Off_InterpolateTick_Rotation* Instance();
  void enter  (ShapeDynamic* shapeDynamic);
  void execute(ShapeDynamic* shapeDynamic);
  void exit   (ShapeDynamic* shapeDynamic);
};
#endif