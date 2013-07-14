#ifndef CLIENTPARTIDOSTATES_H
#define CLIENTPARTIDOSTATES_H

#include "../../../../fsm/state.h"

class ClientPartido;


/*******************************
*      GlobalClientPartido 
******************************/

class GlobalClientPartido : public State<ClientPartido>
{
private:
  GlobalClientPartido(){}
public:
  static GlobalClientPartido* Instance();
  void enter  (ClientPartido* clientPartido);
  void execute(ClientPartido* clientPartido);
  void exit   (ClientPartido* clientPartido);
  bool onLetter(ClientPartido* clientPartido, Letter* letter);
};

/*******************************
*       CLIENT STATES 
******************************/
/*
class Ajax_Node : public State<ClientPartido>
{
private:
  Ajax_Node(){}
public:
  static Ajax_Node* Instance();
  void enter  (ClientPartido* clientPartido);
  void execute(ClientPartido* clientPartido);
  void exit   (ClientPartido* clientPartido);
  bool onLetter(ClientPartido* clientPartido, Letter* letter);
};

class Logged_Out : public State<ClientPartido>
{
private:
  Logged_Out(){}
public:
  static Logged_Out* Instance();
  void enter  (ClientPartido* clientPartido);
  void execute(ClientPartido* clientPartido);
  void exit   (ClientPartido* clientPartido);
  bool onLetter(ClientPartido* clientPartido, Letter* letter);
};

class Lobby : public State<ClientPartido>
{
private:
  Lobby(){}
public:
  static Lobby* Instance();
  void enter  (ClientPartido* clientPartido);
  void execute(ClientPartido* clientPartido);
  void exit   (ClientPartido* clientPartido);
  bool onLetter(ClientPartido* clientPartido, Letter* letter);
};

class Game_Mode : public State<ClientPartido>
{
private:
  Game_Mode(){}
public:
  static Game_Mode* Instance();
  void enter  (ClientPartido* clientPartido);
  void execute(ClientPartido* clientPartido);
  void exit   (ClientPartido* clientPartido);
  bool onLetter(ClientPartido* clientPartido, Letter* letter);
};
*/
#endif
