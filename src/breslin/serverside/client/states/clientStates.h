#ifndef CLIENTSTATES_H
#define CLIENTSTATES_H
#include "clientState.h"

class Client;

class Human_Client : public ClientState
{
private:
  Human_Client(){}
public:
  static Human_Client* Instance();
  void enter  (Client* client);
  void execute(Client* client);
  void exit   (Client* client);
};

class Computer_Client : public ClientState
{
private:
  Computer_Client(){}
public:
  static Computer_Client* Instance();
  void enter  (Client* client);
  void execute(Client* client);
  void exit   (Client* client);
};

#endif
