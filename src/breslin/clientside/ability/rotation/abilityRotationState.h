#ifndef ABILITROTATIONSTATE_H
#define ABILITROTATIONSTATE_H

class AbilityRotation;

class AbilityRotationState
{
public:

  virtual ~AbilityRotationState(){}

  virtual void enter  (AbilityRotation*)=0;
  virtual void execute(AbilityRotation*)=0;
  virtual void exit   (AbilityRotation*)=0;
};

#endif
