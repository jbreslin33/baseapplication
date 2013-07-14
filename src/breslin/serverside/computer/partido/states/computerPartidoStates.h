#ifndef COMPUTERPARTIDOSTATES_H
#define COMPUTERPARTIDOSTATES_H

#include "../../../../fsm/state.h"

class ComputerPartido;

/*******************************
*     GLOBAL COMPTER 
******************************/

class GlobalComputerPartido : public State<ComputerPartido>
{
private:
  GlobalComputerPartido(){}
public:
  static GlobalComputerPartido* Instance();
  void enter  (ComputerPartido* computerPartido);
  void execute(ComputerPartido* computerPartido);
  void exit   (ComputerPartido* computerPartido);
  bool onLetter(ComputerPartido* computerPartido, Letter* letter);
};


/*******************************
*     COMPTER 
******************************/
/*
class ComputerPartido_Controlled : public State<ComputerPartido>
{
private:
  ComputerPartido_Controlled(){}
public:
  static ComputerPartido_Controlled* Instance();
  void enter  (ComputerPartido* computerPartido);
  void execute(ComputerPartido* computerPartido);
  void exit   (ComputerPartido* computerPartido);
  bool onLetter(ComputerPartido* computerPartido, Letter* letter);
};

class Human_Controlled : public State<ComputerPartido>
{
private:
  Human_Controlled(){}
public:
  static Human_Controlled* Instance();
  void enter  (ComputerPartido* computerPartido);
  void execute(ComputerPartido* computerPartido);
  void exit   (ComputerPartido* computerPartido);
  bool onLetter(ComputerPartido* computerPartido, Letter* letter);
};
*/
#endif
