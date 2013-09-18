#ifndef ABILITANIMATIONSTATE_H
#define ABILITANIMATIONSTATE_H

class AbilityAnimation;

class AbilityAnimationState
{
public:

  virtual ~AbilityAnimationState(){}

  virtual void enter  (AbilityAnimation*)=0;
  virtual void execute(AbilityAnimation*)=0;
  virtual void exit   (AbilityAnimation*)=0;
};

#endif
