#ifndef ABILITYROTATIONSTATES_H
#define ABILITYROTATIONSTATES_H
#include "../../states/stateShapeDynamic.h"

class ShapeDynamic;

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
/********************InterpolateTick*************/

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