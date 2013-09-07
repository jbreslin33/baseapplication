#ifndef GAMEPARTIDOSTATES_H
#define GAMEPARTIDOSTATES_H

#include "../../../../fsm/state.h"

class GamePartido;
/******************************************************
	         GLOBAL_GAMEPARTIDO
********************************************************/

class GLOBAL_PARTIDO_GAME : public State<GamePartido>
{
private:
  GLOBAL_PARTIDO_GAME(){}
public:
  static GLOBAL_PARTIDO_GAME* Instance();
  void enter  (GamePartido* gamePartido);
  void execute(GamePartido* gamePartido);
  void exit   (GamePartido* gamePartido);
  bool onLetter(GamePartido* gamePartido, Letter* letter);
};


/******************************************************
*			BATTLE_GAME	
********************************************************/
class BATTLE_GAME : public State<GamePartido>
{
private:
  BATTLE_GAME(){}
public:
  static BATTLE_GAME* Instance();
  void enter  (GamePartido* gamePartido);
  void execute(GamePartido* gamePartido);
  void exit   (GamePartido* gamePartido);
  bool onLetter(GamePartido* gamePartido, Letter* letter);
};

/******************************************************
*			PLAY_PARTIDO_GAME	
********************************************************/
class PLAY_PARTIDO_GAME : public State<GamePartido>
{
private:
  PLAY_PARTIDO_GAME(){}
public:
  static PLAY_PARTIDO_GAME* Instance();
  void enter  (GamePartido* gamePartido);
  void execute(GamePartido* gamePartido);
  void exit   (GamePartido* gamePartido);
  bool onLetter(GamePartido* gamePartido, Letter* letter);
};

/******************************************************
*			RESET_PARTIDO_GAME	
********************************************************/
class RESET_PARTIDO_GAME : public State<GamePartido>
{
private:
  RESET_PARTIDO_GAME(){}
public:
  static RESET_PARTIDO_GAME* Instance();
  void enter  (GamePartido* gamePartido);
  void execute(GamePartido* gamePartido);
  void exit   (GamePartido* gamePartido);
  bool onLetter(GamePartido* gamePartido, Letter* letter);
};

/******************************************************
*			SHOWCORRECTANSWER_PARTIDO_GAME	
********************************************************/
class SHOWCORRECTANSWER_PARTIDO_GAME : public State<GamePartido>
{
private:
  SHOWCORRECTANSWER_PARTIDO_GAME(){}
public:
  static SHOWCORRECTANSWER_PARTIDO_GAME* Instance();
  void enter  (GamePartido* gamePartido);
  void execute(GamePartido* gamePartido);
  void exit   (GamePartido* gamePartido);
  bool onLetter(GamePartido* gamePartido, Letter* letter);
};

#endif