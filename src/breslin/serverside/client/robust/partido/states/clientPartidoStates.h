#ifndef CLIENTPARTIDOSTATES_H
#define CLIENTPARTIDOSTATES_H

#include "../../../../../fsm/state.h"

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
*       CLIENT PARTIDO STATES 
******************************/

class CLIENT_PARTIDO_BATTLE : public State<ClientPartido>
{
private:
  CLIENT_PARTIDO_BATTLE(){}
public:
  static CLIENT_PARTIDO_BATTLE* Instance();
  void enter  (ClientPartido* clientPartido);
  void execute(ClientPartido* clientPartido);
  void exit   (ClientPartido* clientPartido);
  bool onLetter(ClientPartido* clientPartido, Letter* letter);
};

class Game_Partido_Mode : public State<ClientPartido>
{
private:
  Game_Partido_Mode(){}
public:
  static Game_Partido_Mode* Instance();
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

class Waiting_For_Answer : public State<ClientPartido>
{
private:
  Waiting_For_Answer(){}
public:
  static Waiting_For_Answer* Instance();
  void enter  (ClientPartido* clientPartido);
  void execute(ClientPartido* clientPartido);
  void exit   (ClientPartido* clientPartido);
  bool onLetter(ClientPartido* clientPartido, Letter* letter);
};

class Sending_Question : public State<ClientPartido>
{
private:
  Sending_Question(){}
public:
  static Sending_Question* Instance();
  void enter  (ClientPartido* clientPartido);
  void execute(ClientPartido* clientPartido);
  void exit   (ClientPartido* clientPartido);
  bool onLetter(ClientPartido* clientPartido, Letter* letter);
};
#endif
