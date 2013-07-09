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
  bool onMessage(Seek* seek, const Telegram& msg);
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
  bool onMessage(Seek* seek, const Telegram& msg);
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
  bool onMessage(Seek* seek, const Telegram& msg);
};

#endif
