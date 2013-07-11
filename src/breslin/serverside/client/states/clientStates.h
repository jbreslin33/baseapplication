#ifndef CLIENTSTATES_H
#define CLIENTSTATES_H

#include "../../../fsm/state.h"

class Client;
class Letter;

/*******************************
*      GlobalClient 
******************************/

class GlobalClient : public State<Client>
{
private:
  GlobalClient(){}
public:
  static GlobalClient* Instance();
  void enter  (Client* client);
  void execute(Client* client);
  void exit   (Client* client);
  bool onLetter(Client* client, Letter* letter);
};

#endif
