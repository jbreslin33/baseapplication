#ifndef ROTATIONSTATES_H
#define ROTATIONSTATES_H

#include "../../../fsm/state.h"

class Rotation;
struct Telegram;


/*******************************
*      GlobalRotation
******************************/

class GlobalRotation : public State<Rotation>
{
private:
  GlobalRotation(){}
public:
  static GlobalRotation* Instance();
  void enter  (Rotation* rotation);
  void execute(Rotation* rotation);
  void exit   (Rotation* rotation);
  bool onMessage(Rotation* rotation, const Telegram& msg);
};


/*******************************
*      ROTATION 
******************************/

class Normal_Rotation : public State<Rotation>
{
private:
  Normal_Rotation(){}
public:
  static Normal_Rotation* Instance();
  void enter  (Rotation* rotation);
  void execute(Rotation* rotation);
  void exit   (Rotation* rotation);
  bool onMessage(Rotation* rotation, const Telegram& msg);
};

class No_Rotation : public State<Rotation>
{
private:
  No_Rotation(){}
public:
  static No_Rotation* Instance();
  void enter  (Rotation* rotation);
  void execute(Rotation* rotation);
  void exit   (Rotation* rotation);
  bool onMessage(Rotation* rotation, const Telegram& msg);
};

class Accelerate_Rotation : public State<Rotation>
{
private:
  Accelerate_Rotation(){}
public:
  static Accelerate_Rotation* Instance();
  void enter  (Rotation* rotation);
  void execute(Rotation* rotation);
  void exit   (Rotation* rotation);
  bool onMessage(Rotation* rotation, const Telegram& msg);
};

class Decelerate_Rotation : public State<Rotation>
{
private:
  Decelerate_Rotation(){}
public:
  static Decelerate_Rotation* Instance();
  void enter  (Rotation* rotation);
  void execute(Rotation* rotation);
  void exit   (Rotation* rotation);
  bool onMessage(Rotation* rotation, const Telegram& msg);
};

#endif
