#ifndef ABILITYANIMATIONSTATES_H
#define ABILITYANIMATIONSTATES_H
#include "../../states/stateShapeDynamic.h"

class ShapeDynamic;

/********************InterpolateTick*************/

class Global_InterpolateTick_Animation : public ShapeDynamicState
{
private:
  Global_InterpolateTick_Animation(){}
public:
  static Global_InterpolateTick_Animation* Instance();
  void enter  (ShapeDynamic* shapeDynamic);
  void execute(ShapeDynamic* shapeDynamic);
  void exit   (ShapeDynamic* shapeDynamic);
};

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