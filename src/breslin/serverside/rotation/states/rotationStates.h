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
  bool onLetter(Rotation* rotation, Letter* letter);
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
  bool onLetter(Rotation* rotation, Letter* letter);
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
  bool onLetter(Rotation* rotation, Letter* letter);
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
  bool onLetter(Rotation* rotation, Letter* letter);
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
  bool onLetter(Rotation* rotation, Letter* letter);
};

#endif
