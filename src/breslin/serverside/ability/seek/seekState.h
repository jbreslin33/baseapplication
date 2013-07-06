#ifndef SEEKSTATE_H
#define SEEKSTATE_H

class Seek;

class SeekState
{
public:

  virtual ~SeekState(){}

  virtual void enter(Seek*)=0;

  virtual void execute(Seek*)=0;

  virtual void exit(Seek*)=0;
};

#endif
