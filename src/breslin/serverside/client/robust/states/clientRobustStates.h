#ifndef CLIENTROBUSTSTATES_H
#define CLIENTROBUSTSTATES_H

#include "../../../../fsm/state.h"

class ClientRobust;


/*******************************
*      GLOBAL_CLIENT_ROBUST 
******************************/

class GLOBAL_CLIENT_ROBUST : public State<ClientRobust>
{
private:
  GLOBAL_CLIENT_ROBUST(){}
public:
  static GLOBAL_CLIENT_ROBUST* Instance();
  void enter  (ClientRobust* clientRobust);
  void execute(ClientRobust* clientRobust);
  void exit   (ClientRobust* clientRobust);
  bool onLetter(ClientRobust* clientRobust, Letter* letter);
};

/*******************************
*       CLIENT STATES 
******************************/

class AJAX_NODE : public State<ClientRobust>
{
private:
  AJAX_NODE(){}
public:
  static AJAX_NODE* Instance();
  void enter  (ClientRobust* clientRobust);
  void execute(ClientRobust* clientRobust);
  void exit   (ClientRobust* clientRobust);
  bool onLetter(ClientRobust* clientRobust, Letter* letter);
};

class LOGGED_OUT : public State<ClientRobust>
{
private:
  LOGGED_OUT(){}
public:
  static LOGGED_OUT* Instance();
  void enter  (ClientRobust* clientRobust);
  void execute(ClientRobust* clientRobust);
  void exit   (ClientRobust* clientRobust);
  bool onLetter(ClientRobust* clientRobust, Letter* letter);
};

class LOBBY : public State<ClientRobust>
{
private:
  LOBBY(){}
public:
  static LOBBY* Instance();
  void enter  (ClientRobust* clientRobust);
  void execute(ClientRobust* clientRobust);
  void exit   (ClientRobust* clientRobust);
  bool onLetter(ClientRobust* clientRobust, Letter* letter);
};

class GAME_MODE : public State<ClientRobust>
{
private:
  GAME_MODE(){}
public:
  static GAME_MODE* Instance();
  void enter  (ClientRobust* clientRobust);
  void execute(ClientRobust* clientRobust);
  void exit   (ClientRobust* clientRobust);
  bool onLetter(ClientRobust* clientRobust, Letter* letter);
};

#endif
