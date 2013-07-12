#ifndef MOVESTATES_H
#define MOVESTATES_H

#include "../../../fsm/state.h"

class Move;
struct Telegram;

/*******************************
*      GlobalMove
******************************/

class GlobalMove : public State<Move>
{
private:
  GlobalMove(){}
public:
  static GlobalMove* Instance();
  void enter  (Move* move);
  void execute(Move* move);
  void exit   (Move* move);
  bool onLetter(Move* move, Letter* letter);
};


/*******************************
*      Move
******************************/
class Normal_Move : public State<Move>
{
private:
  Normal_Move(){}
public:
  static Normal_Move* Instance();
  void enter  (Move* move);
  void execute(Move* move);
  void exit   (Move* move);
  bool onLetter(Move* move, Letter* letter);
};

class No_Move : public State<Move>
{
private:
  No_Move(){}
public:
  static No_Move* Instance();
  void enter  (Move* move);
  void execute(Move* move);
  void exit   (Move* move);
  bool onLetter(Move* move, Letter* letter);
};

class Accelerate_Move : public State<Move>
{
private:
  Accelerate_Move(){}
public:
  static Accelerate_Move* Instance();
  void enter  (Move* move);
  void execute(Move* move);
  void exit   (Move* move);
  bool onLetter(Move* move, Letter* letter);
};

class Decelerate_Move : public State<Move>
{
private:
  Decelerate_Move(){}
public:
  static Decelerate_Move* Instance();
  void enter  (Move* move);
  void execute(Move* move);
  void exit   (Move* move);
  bool onLetter(Move* move, Letter* letter);
};
#endif
