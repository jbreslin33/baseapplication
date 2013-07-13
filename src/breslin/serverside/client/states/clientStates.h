#ifndef CLIENTSTATES_H
#define CLIENTSTATES_H

#include "../../../fsm/state.h"

class Client;
struct Telegram;


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

/*******************************
*       CLIENT STATES 
******************************/
class Connected : public State<Client>
{
private:
  Connected(){}
public:
  static Connected* Instance();
  void enter  (Client* client);
  void execute(Client* client);
  void exit   (Client* client);
  bool onLetter(Client* client, Letter* letter);
};



class Disconnected : public State<Client>
{
private:
  Disconnected(){}
public:
  static Disconnected* Instance();
  void enter  (Client* client);
  void execute(Client* client);
  void exit   (Client* client);
  bool onLetter(Client* client, Letter* letter);
};

#endif
