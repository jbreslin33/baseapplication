#ifndef GAMESTATES_H
#define GAMESTATES_H

#include "../../../fsm/state.h"

class Game;

/******************************************************
	         GLOBAL_MOVE
********************************************************/

class GLOBAL_GAME : public State<Game>
{
private:
  GLOBAL_GAME(){}
public:
  static GLOBAL_GAME* Instance();
  void enter  (Game* game);
  void execute(Game* game);
  void exit   (Game* game);
  bool onLetter(Game* game, Letter* letter);
};


/******************************************************
*				NORMAL
********************************************************/
class PLAY_GAME : public State<Game>
{
private:
  PLAY_GAME(){}
public:
  static PLAY_GAME* Instance();
  void enter  (Game* game);
  void execute(Game* game);
  void exit   (Game* game);
  bool onLetter(Game* game, Letter* letter);
};


#endif
