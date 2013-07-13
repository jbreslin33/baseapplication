#ifndef CLIENTROBUSTSTATES_H
#define CLIENTROBUSTSTATES_H

#include "../../../../fsm/state.h"

class ClientRobust;
struct Telegram;


/*******************************
*      GlobalClientRobust 
******************************/

class GlobalClientRobust : public State<ClientRobust>
{
private:
  GlobalClientRobust(){}
public:
  static GlobalClientRobust* Instance();
  void enter  (ClientRobust* clientRobust);
  void execute(ClientRobust* clientRobust);
  void exit   (ClientRobust* clientRobust);
  bool onLetter(ClientRobust* clientRobust, Letter* letter);
};

/*******************************
*       CLIENT STATES 
******************************/

class Ajax_Node : public State<ClientRobust>
{
private:
  Ajax_Node(){}
public:
  static Ajax_Node* Instance();
  void enter  (ClientRobust* clientRobust);
  void execute(ClientRobust* clientRobust);
  void exit   (ClientRobust* clientRobust);
  bool onLetter(ClientRobust* clientRobust, Letter* letter);
};

class Logged_Out : public State<ClientRobust>
{
private:
  Logged_Out(){}
public:
  static Logged_Out* Instance();
  void enter  (ClientRobust* clientRobust);
  void execute(ClientRobust* clientRobust);
  void exit   (ClientRobust* clientRobust);
  bool onLetter(ClientRobust* clientRobust, Letter* letter);
};

class Lobby : public State<ClientRobust>
{
private:
  Lobby(){}
public:
  static Lobby* Instance();
  void enter  (ClientRobust* clientRobust);
  void execute(ClientRobust* clientRobust);
  void exit   (ClientRobust* clientRobust);
  bool onLetter(ClientRobust* clientRobust, Letter* letter);
};

class Game_Mode : public State<ClientRobust>
{
private:
  Game_Mode(){}
public:
  static Game_Mode* Instance();
  void enter  (ClientRobust* clientRobust);
  void execute(ClientRobust* clientRobust);
  void exit   (ClientRobust* clientRobust);
  bool onLetter(ClientRobust* clientRobust, Letter* letter);
};

#endif
