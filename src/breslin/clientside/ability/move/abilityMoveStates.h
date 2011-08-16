#ifndef DYNAMICSHAPEMOVESTATES_H
#define DYNAMICSHAPEMOVESTATES_H
#include "shapeDynamicState.h"

class DynamicShape;

class Global_ProcessTick_Move : public DynamicShapeState
{
private:
  Global_ProcessTick_Move(){}
public:
  static Global_ProcessTick_Move* Instance();
  void enter  (DynamicShape* shapeDynamic);
  void execute(DynamicShape* shapeDynamic);
  void exit   (DynamicShape* shapeDynamic);
};

class Normal_ProcessTick_Move : public DynamicShapeState
{
private:
  Normal_ProcessTick_Move(){}
public:
  static Normal_ProcessTick_Move* Instance();
  void enter  (DynamicShape* shapeDynamic);
  void execute(DynamicShape* shapeDynamic);
  void exit   (DynamicShape* shapeDynamic);
};

class Catchup_ProcessTick_Move : public DynamicShapeState
{
private:
  Catchup_ProcessTick_Move(){}
public:
  static Catchup_ProcessTick_Move* Instance();
  void enter  (DynamicShape* shapeDynamic);
  void execute(DynamicShape* shapeDynamic);
  void exit   (DynamicShape* shapeDynamic);
};


class Global_InterpolateTick_Move : public DynamicShapeState
{
private:
  Global_InterpolateTick_Move(){}
public:
  static Global_InterpolateTick_Move* Instance();
  void enter  (DynamicShape* shapeDynamic);
  void execute(DynamicShape* shapeDynamic);
  void exit   (DynamicShape* shapeDynamic);
};

class Normal_InterpolateTick_Move : public DynamicShapeState
{
private:
  Normal_InterpolateTick_Move(){}
public:
  static Normal_InterpolateTick_Move* Instance();
  void enter  (DynamicShape* shapeDynamic);
  void execute(DynamicShape* shapeDynamic);
  void exit   (DynamicShape* shapeDynamic);
};

class Off_InterpolateTick_Move : public DynamicShapeState
{
private:
  Off_InterpolateTick_Move(){}
public:
  static Off_InterpolateTick_Move* Instance();
  void enter  (DynamicShape* shapeDynamic);
  void execute(DynamicShape* shapeDynamic);
  void exit   (DynamicShape* shapeDynamic);
};


#endif
