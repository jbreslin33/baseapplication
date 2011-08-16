#ifndef DYNAMICSHAPEANIMATIONSTATES_H
#define DYNAMICSHAPEANIMATIONSTATES_H
#include "../../states/shapeDynamicState.h"

class DynamicShape;

/********************InterpolateTick*************/

class Global_InterpolateTick_Animation : public DynamicShapeState
{
private:
  Global_InterpolateTick_Animation(){}
public:
  static Global_InterpolateTick_Animation* Instance();
  void enter  (DynamicShape* shapeDynamic);
  void execute(DynamicShape* shapeDynamic);
  void exit   (DynamicShape* shapeDynamic);
};

class Idle_InterpolateTick_Animation : public DynamicShapeState
{
private:
  Idle_InterpolateTick_Animation(){}
public:
  static Idle_InterpolateTick_Animation* Instance();
  void enter  (DynamicShape* shapeDynamic);
  void execute(DynamicShape* shapeDynamic);
  void exit   (DynamicShape* shapeDynamic);
};

class Run_InterpolateTick_Animation : public DynamicShapeState
{
private:
  Run_InterpolateTick_Animation(){}
public:
  static Run_InterpolateTick_Animation* Instance();
  void enter  (DynamicShape* shapeDynamic);
  void execute(DynamicShape* shapeDynamic);
  void exit   (DynamicShape* shapeDynamic);
};

#endif