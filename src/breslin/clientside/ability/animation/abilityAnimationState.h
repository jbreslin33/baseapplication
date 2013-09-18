#ifndef ABILITANIMATIONSTATE_H
#define ABILITANIMATIONSTATE_H

class AbilityAnimationOgre;

class AbilityAnimationState
{
public:

  virtual ~AbilityAnimationState(){}

  virtual void enter  (AbilityAnimationOgre*)=0;
  virtual void execute(AbilityAnimationOgre*)=0;
  virtual void exit   (AbilityAnimationOgre*)=0;
};

#endif
