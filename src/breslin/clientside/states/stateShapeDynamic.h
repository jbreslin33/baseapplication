#ifndef DYNAMICSHAPESTATE_H
#define DYNAMICSHAPESTATE_H

class ShapeDynamic;

class ShapeDynamicState
{
public:

  virtual ~ShapeDynamicState(){}

  //this will execute when the state is entered
  virtual void enter(ShapeDynamic*)=0;

  //this is the states normal update function
  virtual void execute(ShapeDynamic*)=0;

  //this will execute when the state is exited. (My word, isn't
  //life full of surprises... ;o))
  virtual void exit(ShapeDynamic*)=0;
};

#endif
