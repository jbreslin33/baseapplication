#ifndef DYNAMICSHAPEROTATIONSTATES_H
#define DYNAMICSHAPEROTATIONSTATES_H
#include "shapeDynamicState.h"

class DynamicShape;

class Global_ProcessTick_Rotation : public DynamicShapeState
{
private:
  Global_ProcessTick_Rotation(){}
public:
  static Global_ProcessTick_Rotation* Instance();
  void enter  (DynamicShape* shapeDynamic);
  void execute(DynamicShape* shapeDynamic);
  void exit   (DynamicShape* shapeDynamic);
};

class Normal_ProcessTick_Rotation : public DynamicShapeState
{
private:
  Normal_ProcessTick_Rotation(){}
public:
  static Normal_ProcessTick_Rotation* Instance();
  void enter  (DynamicShape* shapeDynamic);
  void execute(DynamicShape* shapeDynamic);
  void exit   (DynamicShape* shapeDynamic);
};

class Catchup_ProcessTick_Rotation : public DynamicShapeState
{
private:
  Catchup_ProcessTick_Rotation(){}
public:
  static Catchup_ProcessTick_Rotation* Instance();
  void enter  (DynamicShape* shapeDynamic);
  void execute(DynamicShape* shapeDynamic);
  void exit   (DynamicShape* shapeDynamic);
};
/********************InterpolateTick*************/

class Global_InterpolateTick_Rotation : public DynamicShapeState
{
private:
  Global_InterpolateTick_Rotation(){}
public:
  static Global_InterpolateTick_Rotation* Instance();
  void enter  (DynamicShape* shapeDynamic);
  void execute(DynamicShape* shapeDynamic);
  void exit   (DynamicShape* shapeDynamic);
};

class Normal_InterpolateTick_Rotation : public DynamicShapeState
{
private:
  Normal_InterpolateTick_Rotation(){}
public:
  static Normal_InterpolateTick_Rotation* Instance();
  void enter  (DynamicShape* shapeDynamic);
  void execute(DynamicShape* shapeDynamic);
  void exit   (DynamicShape* shapeDynamic);
};

class Off_InterpolateTick_Rotation : public DynamicShapeState
{
private:
  Off_InterpolateTick_Rotation(){}
public:
  static Off_InterpolateTick_Rotation* Instance();
  void enter  (DynamicShape* shapeDynamic);
  void execute(DynamicShape* shapeDynamic);
  void exit   (DynamicShape* shapeDynamic);
};
#endif