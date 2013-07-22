#ifndef SEEKTATES_H
#define SEEKSTATES_H

#include "../../../fsm/state.h"

class Avoid;
struct Telegram;


/*******************************
*      GLOBAL_AVOID
******************************/

class GLOBAL_AVOID : public State<Avoid>
{
private:
  GLOBAL_AVOID(){}
public:
  static GLOBAL_AVOID* Instance();
  void enter  (Avoid* avoid);
  void execute(Avoid* avoid);
  void exit   (Avoid* avoid);
  bool onLetter(Avoid* avoid, Letter* letter);
};

/*******************************
*      Avoid
******************************/

class NORMAL_AVOID : public State<Avoid>
{
private:
  NORMAL_AVOID(){}
public:
  static NORMAL_AVOID* Instance();
  void enter  (Avoid* avoid);
  void execute(Avoid* avoid);
  void exit   (Avoid* avoid);
  bool onLetter(Avoid* avoid, Letter* letter);
};

class SEEK_AVOID : public State<Avoid>
{
private:
  SEEK_AVOID(){}
public:
  static SEEK_AVOID* Instance();
  void enter  (Avoid* avoid);
  void execute(Avoid* avoid);
  void exit   (Avoid* avoid);
  bool onLetter(Avoid* avoid, Letter* letter);
};

class NO_AVOID : public State<Avoid>
{
private:
  NO_AVOID(){}
public:
  static NO_AVOID* Instance();
  void enter  (Avoid* avoid);
  void execute(Avoid* avoid);
  void exit   (Avoid* avoid);
  bool onLetter(Avoid* avoid, Letter* letter);
};

#endif
