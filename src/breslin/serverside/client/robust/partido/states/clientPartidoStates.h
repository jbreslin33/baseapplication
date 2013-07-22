#ifndef CLIENTPARTIDOSTATES_H
#define CLIENTPARTIDOSTATES_H

#include "../../../../../fsm/state.h"

class ClientPartido;


/*******************************
*      GLOBAL_CLIENT_PARTIDO 
******************************/

class GLOBAL_CLIENT_PARTIDO : public State<ClientPartido>
{
private:
  GLOBAL_CLIENT_PARTIDO(){}
public:
  static GLOBAL_CLIENT_PARTIDO* Instance();
  void enter  (ClientPartido* clientPartido);
  void execute(ClientPartido* clientPartido);
  void exit   (ClientPartido* clientPartido);
  bool onLetter(ClientPartido* clientPartido, Letter* letter);
};

/*******************************
*       CLIENT PARTIDO STATES 
******************************/

class BATTLE : public State<ClientPartido>
{
private:
  BATTLE(){}
public:
  static BATTLE* Instance();
  void enter  (ClientPartido* clientPartido);
  void execute(ClientPartido* clientPartido);
  void exit   (ClientPartido* clientPartido);
  bool onLetter(ClientPartido* clientPartido, Letter* letter);
};

class GAME_PARTIDO_MODE : public State<ClientPartido>
{
private:
  GAME_PARTIDO_MODE(){}
public:
  static GAME_PARTIDO_MODE* Instance();
  void enter  (ClientPartido* clientPartido);
  void execute(ClientPartido* clientPartido);
  void exit   (ClientPartido* clientPartido);
  bool onLetter(ClientPartido* clientPartido, Letter* letter);
};

/***BATTLE***/
class BATTLE_OFF : public State<ClientPartido>
{
private:
  BATTLE_OFF(){}
public:
  static BATTLE_OFF* Instance();
  void enter  (ClientPartido* clientPartido);
  void execute(ClientPartido* clientPartido);
  void exit   (ClientPartido* clientPartido);
  bool onLetter(ClientPartido* clientPartido, Letter* letter);
};

class WAITING_FOR_ANSWER : public State<ClientPartido>
{
private:
  WAITING_FOR_ANSWER(){}
public:
  static WAITING_FOR_ANSWER* Instance();
  void enter  (ClientPartido* clientPartido);
  void execute(ClientPartido* clientPartido);
  void exit   (ClientPartido* clientPartido);
  bool onLetter(ClientPartido* clientPartido, Letter* letter);
};

class SENDING_QUESTION : public State<ClientPartido>
{
private:
  SENDING_QUESTION(){}
public:
  static SENDING_QUESTION* Instance();
  void enter  (ClientPartido* clientPartido);
  void execute(ClientPartido* clientPartido);
  void exit   (ClientPartido* clientPartido);
  bool onLetter(ClientPartido* clientPartido, Letter* letter);
};
#endif
