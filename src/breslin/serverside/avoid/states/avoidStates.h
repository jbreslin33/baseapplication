#ifndef SEEKTATES_H
#define SEEKSTATES_H

#include "../../../fsm/state.h"

class Avoid;
struct Telegram;


/*******************************
*      GlobalAvoid
******************************/

class GlobalAvoid : public State<Avoid>
{
private:
  GlobalAvoid(){}
public:
  static GlobalAvoid* Instance();
  void enter  (Avoid* avoid);
  void execute(Avoid* avoid);
  void exit   (Avoid* avoid);
  bool onLetter(Avoid* avoid, Letter* letter);
};

/*******************************
*      Avoid
******************************/

class Normal_Avoid : public State<Avoid>
{
private:
  Normal_Avoid(){}
public:
  static Normal_Avoid* Instance();
  void enter  (Avoid* avoid);
  void execute(Avoid* avoid);
  void exit   (Avoid* avoid);
  bool onLetter(Avoid* avoid, Letter* letter);
};

class No_Avoid : public State<Avoid>
{
private:
  No_Avoid(){}
public:
  static No_Avoid* Instance();
  void enter  (Avoid* avoid);
  void execute(Avoid* avoid);
  void exit   (Avoid* avoid);
  bool onLetter(Avoid* avoid, Letter* letter);
};

class X_N_Z_N : public State<Avoid>
{
private:
  X_N_Z_N(){}
public:
  static X_N_Z_N* Instance();
  void enter  (Avoid* avoid);
  void execute(Avoid* avoid);
  void exit   (Avoid* avoid);
  bool onLetter(Avoid* avoid, Letter* letter);
};

class X_N_Z_P : public State<Avoid>
{
private:
  X_N_Z_P(){}
public:
  static X_N_Z_P* Instance();
  void enter  (Avoid* avoid);
  void execute(Avoid* avoid);
  void exit   (Avoid* avoid);
  bool onLetter(Avoid* avoid, Letter* letter);
};


class X_P_Z_P : public State<Avoid>
{
private:
  X_P_Z_P(){}
public:
  static X_P_Z_P* Instance();
  void enter  (Avoid* avoid);
  void execute(Avoid* avoid);
  void exit   (Avoid* avoid);
  bool onLetter(Avoid* avoid, Letter* letter);
};

class X_P_Z_N : public State<Avoid>
{
private:
  X_P_Z_N(){}
public:
  static X_P_Z_N* Instance();
  void enter  (Avoid* avoid);
  void execute(Avoid* avoid);
  void exit   (Avoid* avoid);
  bool onLetter(Avoid* avoid, Letter* letter);
};


#endif
