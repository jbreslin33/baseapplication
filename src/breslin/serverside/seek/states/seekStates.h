#ifndef SEEKTATES_H
#define SEEKSTATES_H
#include "seekState.h"

class Seek;

class Normal_Seek : public SeekState
{
private:
  Normal_Seek(){}
public:
  static Normal_Seek* Instance();
  void enter  (Seek* seek);
  void execute(Seek* seek);
  void exit   (Seek* seek);
};

class No_Seek : public SeekState
{
private:
  No_Seek(){}
public:
  static No_Seek* Instance();
  void enter  (Seek* seek);
  void execute(Seek* seek);
  void exit   (Seek* seek);
};

#endif
