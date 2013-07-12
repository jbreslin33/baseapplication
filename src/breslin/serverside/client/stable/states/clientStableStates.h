#ifndef CLIENTSTABLESTATES_H
#define CLIENTSTABLESTATES_H

#include "../../../../fsm/state.h"

class ClientStable;
struct Telegram;


/*******************************
*      GlobalClientStable 
******************************/

class GlobalClientStable : public State<ClientStable>
{
private:
  GlobalClientStable(){}
public:
  static GlobalClientStable* Instance();
  void enter  (ClientStable* clientStable);
  void execute(ClientStable* clientStable);
  void exit   (ClientStable* clientStable);
  bool onLetter(ClientStable* clientStable, Letter* letter);
};


#endif
