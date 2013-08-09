#ifndef SEEKTATES_H
#define SEEKSTATES_H

#include "../../../fsm/state.h"

class Steering;
struct Telegram;


/*******************************
*      GlobalSteering
******************************/

class GlobalSteering : public State<Steering>
{
private:
  GlobalSteering(){}
public:
  static GlobalSteering* Instance();
  void enter  (Steering* steering);
  void execute(Steering* steering);
  void exit   (Steering* steering);
  bool onLetter(Steering* steering, Letter* letter);
};

/*******************************
*      Steering
******************************/

class Normal_Steering : public State<Steering>
{
private:
  Normal_Steering(){}
public:
  static Normal_Steering* Instance();
  void enter  (Steering* steering);
  void execute(Steering* steering);
  void exit   (Steering* steering);
  bool onLetter(Steering* steering, Letter* letter);
};

class No_Steering : public State<Steering>
{
private:
  No_Steering(){}
public:
  static No_Steering* Instance();
  void enter  (Steering* steering);
  void execute(Steering* steering);
  void exit   (Steering* steering);
  bool onLetter(Steering* steering, Letter* letter);
};

#endif
