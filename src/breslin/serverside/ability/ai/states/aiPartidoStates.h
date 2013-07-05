#ifndef AISTATES_H
#define AISTATES_H
#include "aiState.h"

class AI;

class Random_AI : public AIState
{
private:
  Random_AI(){}
public:
  static Random_AI* Instance();
  void enter  (AI* ai);
  void execute(AI* ai);
  void exit   (AI* ai);
};

class No_AI : public AIState
{
private:
  No_AI(){}
public:
  static No_AI* Instance();
  void enter  (AI* ai);
  void execute(AI* ai);
  void exit   (AI* ai);
};

#endif
