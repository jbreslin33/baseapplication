#ifndef ABILITYMOVESTATES_H
#define ABILITYMOVESTATES_H
#include "../../states/stateShapeDynamic.h"

class ShapeDynamic;

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


class Global_InterpolateTick_Move : public ShapeDynamicState
{
private:
  Global_InterpolateTick_Move(){}
public:
  static Global_InterpolateTick_Move* Instance();
  void enter  (ShapeDynamic* shapeDynamic);
  void execute(ShapeDynamic* shapeDynamic);
  void exit   (ShapeDynamic* shapeDynamic);
};

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

class Off_InterpolateTick_Move : public ShapeDynamicState
{
private:
  Off_InterpolateTick_Move(){}
public:
  static Off_InterpolateTick_Move* Instance();
  void enter  (ShapeDynamic* shapeDynamic);
  void execute(ShapeDynamic* shapeDynamic);
  void exit   (ShapeDynamic* shapeDynamic);
};


#endif
