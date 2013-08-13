#ifndef COMBATANTSTATES_H
#define COMBATANTSTATES_H

#include "../../../fsm/state.h"

class Combatant;


/*******************************
*      GLOBAL_COMBATANT
******************************/

class GLOBAL_COMBATANT : public State<Combatant>
{
private:
  GLOBAL_COMBATANT(){}
public:
  static GLOBAL_COMBATANT* Instance();
  void enter  (Combatant* battle);
  void execute(Combatant* battle);
  void exit   (Combatant* battle);
  bool onLetter(Combatant* battle, Letter* letter);
};

/*******************************
*      Combatant
******************************/

class INIT_COMBATANT : public State<Combatant>
{
private:
  INIT_COMBATANT(){}
public:
  static INIT_COMBATANT* Instance();
  void enter  (Combatant* battle);
  void execute(Combatant* battle);
  void exit   (Combatant* battle);
  bool onLetter(Combatant* battle, Letter* letter);
};

class SENDING_QUESTION : public State<Combatant>
{
private:
  SENDING_QUESTION(){}
public:
  static SENDING_QUESTION* Instance();
  void enter  (Combatant* battle);
  void execute(Combatant* battle);
  void exit   (Combatant* battle);
  bool onLetter(Combatant* battle, Letter* letter);
};

class WAITING_FOR_ANSWER : public State<Combatant>
{
private:
  WAITING_FOR_ANSWER(){}
public:
  static WAITING_FOR_ANSWER* Instance();
  void enter  (Combatant* battle);
  void execute(Combatant* battle);
  void exit   (Combatant* battle);
  bool onLetter(Combatant* battle, Letter* letter);
};

class YIELD : public State<Combatant>
{
private:
  YIELD(){}
public:
  static YIELD* Instance();
  void enter  (Combatant* battle);
  void execute(Combatant* battle);
  void exit   (Combatant* battle);
  bool onLetter(Combatant* battle, Letter* letter);
};

#endif
