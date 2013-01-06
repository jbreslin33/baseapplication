#ifndef ABILITMOVESTATE_H
#define ABILITMOVESTATE_H

class AbilityMove;

class AbilityMoveState
{
public:

  virtual ~AbilityMoveState(){}

  virtual void enter  (AbilityMove*)=0;
  virtual void execute(AbilityMove*)=0;
  virtual void exit   (AbilityMove*)=0;
};

#endif
