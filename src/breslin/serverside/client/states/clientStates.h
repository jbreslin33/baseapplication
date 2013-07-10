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
*       CLIENT STATES 
******************************/

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

class Lobby : public State<Client>
{
private:
  Lobby(){}
public:
  static Lobby* Instance();
  void enter  (Client* client);
  void execute(Client* client);
  void exit   (Client* client);
  bool onMessage(Client* client, const Telegram& msg);
};


class Game_Mode : public State<Client>
{
private:
  Game_Mode(){}
public:
  static Game_Mode* Instance();
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

class Computer_Mode : public State<Client>
{
private:
  Computer_Mode(){}
public:
  static Computer_Mode* Instance();
  void enter  (Client* client);
  void execute(Client* client);
  void exit   (Client* client);
  bool onMessage(Client* client, const Telegram& msg);
};

/*******************************
*          PERMANENCE 
******************************/

class Initialize_Permanence : public State<Client>
{
private:
  Initialize_Permanence(){}
public:
  static Initialize_Permanence* Instance();
  void enter  (Client* client);
  void execute(Client* client);
  void exit   (Client* client);
  bool onMessage(Client* client, const Telegram& msg);
};


class Permanent : public State<Client>
{
private:
  Permanent(){}
public:
  static Permanent* Instance();
  void enter  (Client* client);
  void execute(Client* client);
  void exit   (Client* client);
  bool onMessage(Client* client, const Telegram& msg);
};

class Temporary : public State<Client>
{
private:
  Temporary(){}
public:
  static Temporary* Instance();
  void enter  (Client* client);
  void execute(Client* client);
  void exit   (Client* client);
  bool onMessage(Client* client, const Telegram& msg);
};


#endif
