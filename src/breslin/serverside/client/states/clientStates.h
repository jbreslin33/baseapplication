#ifndef CLIENTSTATES_H
#define CLIENTSTATES_H
#include "clientState.h"

class Client;

/*******************************
*       LOGIN 
******************************/

class Logged_In : public ClientState
{
private:
  Logged_In(){}
public:
  static Logged_In* Instance();
  void enter  (Client* client);
  void execute(Client* client);
  void exit   (Client* client);
};

class Logged_Out : public ClientState
{
private:
  Logged_Out(){}
public:
  static Logged_Out* Instance();
  void enter  (Client* client);
  void execute(Client* client);
  void exit   (Client* client);
};



/*******************************
*        GAME CONTROL
******************************/
class Human : public ClientState
{
private:
  Human(){}
public:
  static Human* Instance();
  void enter  (Client* client);
  void execute(Client* client);
  void exit   (Client* client);
};

class Computer : public ClientState
{
private:
  Computer(){}
public:
  static Computer* Instance();
  void enter  (Client* client);
  void execute(Client* client);
  void exit   (Client* client);
};

#endif
