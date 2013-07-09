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
  bool onMessage(Client* client, const Telegram& msg);
};


/*******************************
*       LOGIN 
******************************/

class Logged_In : public State<Client>
{
private:
  Logged_In(){}
public:
  static Logged_In* Instance();
  void enter  (Client* client);
  void execute(Client* client);
  void exit   (Client* client);
  bool onMessage(Client* client, const Telegram& msg);
};

class Logged_Out : public State<Client>
{
private:
  Logged_Out(){}
public:
  static Logged_Out* Instance();
  void enter  (Client* client);
  void execute(Client* client);
  void exit   (Client* client);
  bool onMessage(Client* client, const Telegram& msg);
};



/*******************************
*        GAME CONTROL
******************************/
class Human : public State<Client>
{
private:
  Human(){}
public:
  static Human* Instance();
  void enter  (Client* client);
  void execute(Client* client);
  void exit   (Client* client);
  bool onMessage(Client* client, const Telegram& msg);
};

class Computer : public State<Client>
{
private:
  Computer(){}
public:
  static Computer* Instance();
  void enter  (Client* client);
  void execute(Client* client);
  void exit   (Client* client);
  bool onMessage(Client* client, const Telegram& msg);
};

#endif
