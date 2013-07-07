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

class Human_AI : public AIState
{
private:
  Human_AI(){}
public:
  static Human_AI* Instance();
  void enter  (AI* ai);
  void execute(AI* ai);
  void exit   (AI* ai);
};

#endif
