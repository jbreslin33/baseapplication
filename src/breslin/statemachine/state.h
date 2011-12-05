#ifndef STATE_H
#define STATE_H

template <class T*>

class State
{
public:

  virtual ~State(){}

  virtual void enter  (T tAbility*)=0;
  virtual void execute(T tAbility*)=0;
  virtual void exit   (T tAbility*)=0;
};

#endif
