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

class Connecting : public State<Client>
{
private:
  Connecting(){}
public:
  static Connecting* Instance();
  void enter  (Client* client);
  void execute(Client* client);
  void exit   (Client* client);
  bool onLetter(Client* client, Letter* letter);
};

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


#endif
