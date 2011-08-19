#ifndef ABILITYSTATE_H
#define ABILITYSTATE_H

class Ability;

class AbilityState
{
public:

  virtual ~AbilityState(){}

  //this will execute when the state is entered
  virtual void enter(Ability*)=0;

  //this is the states normal update function
  virtual void execute(Ability*)=0;

  //this will execute when the state is exited. (My word, isn't
  //life full of surprises... ;o))
  virtual void exit(Ability*)=0;
};

#endif
