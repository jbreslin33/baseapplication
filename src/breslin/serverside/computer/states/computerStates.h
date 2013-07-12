#ifndef COMPUTERSTATES_H
#define COMPUTERSTATES_H

#include "../../../fsm/state.h"

class Computer;
struct Telegram;


/*******************************
*     GLOBAL COMPTER 
******************************/

class GlobalComputer : public State<Computer>
{
private:
  GlobalComputer(){}
public:
  static GlobalComputer* Instance();
  void enter  (Computer* computer);
  void execute(Computer* computer);
  void exit   (Computer* computer);
  bool onLetter(Computer* computer, Letter* letter);
};


/*******************************
*     COMPTER 
******************************/

class Random_Computer : public State<Computer>
{
private:
  Random_Computer(){}
public:
  static Random_Computer* Instance();
  void enter  (Computer* computer);
  void execute(Computer* computer);
  void exit   (Computer* computer);
  bool onLetter(Computer* computer, Letter* letter);
};

class No_Computer : public State<Computer>
{
private:
  No_Computer(){}
public:
  static No_Computer* Instance();
  void enter  (Computer* computer);
  void execute(Computer* computer);
  void exit   (Computer* computer);
  bool onLetter(Computer* computer, Letter* letter);
};

#endif
