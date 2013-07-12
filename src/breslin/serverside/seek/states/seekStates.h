#ifndef SEEKTATES_H
#define SEEKSTATES_H

#include "../../../fsm/state.h"

class Seek;
struct Telegram;


/*******************************
*      GlobalSeek
******************************/

class GlobalSeek : public State<Seek>
{
private:
  GlobalSeek(){}
public:
  static GlobalSeek* Instance();
  void enter  (Seek* seek);
  void execute(Seek* seek);
  void exit   (Seek* seek);
  bool onLetter(Seek* seek, Letter* letter);
};

/*******************************
*      Seek
******************************/

class Normal_Seek : public State<Seek>
{
private:
  Normal_Seek(){}
public:
  static Normal_Seek* Instance();
  void enter  (Seek* seek);
  void execute(Seek* seek);
  void exit   (Seek* seek);
  bool onLetter(Seek* seek, Letter* letter);
};

class No_Seek : public State<Seek>
{
private:
  No_Seek(){}
public:
  static No_Seek* Instance();
  void enter  (Seek* seek);
  void execute(Seek* seek);
  void exit   (Seek* seek);
  bool onLetter(Seek* seek, Letter* letter);
};

#endif
