#ifndef COMPUTERSTATES_H
#define COMPUTERSTATES_H

#include "../../../fsm/state.h"

class Computer;


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

class Computer_Controlled : public State<Computer>
{
private:
  Computer_Controlled(){}
public:
  static Computer_Controlled* Instance();
  void enter  (Computer* computer);
  void execute(Computer* computer);
  void exit   (Computer* computer);
  bool onLetter(Computer* computer, Letter* letter);
};

class Human_Controlled : public State<Computer>
{
private:
  Human_Controlled(){}
public:
  static Human_Controlled* Instance();
  void enter  (Computer* computer);
  void execute(Computer* computer);
  void exit   (Computer* computer);
  bool onLetter(Computer* computer, Letter* letter);
};

#endif
