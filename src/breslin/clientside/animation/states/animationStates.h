#ifndef ANIMATIONSTATES_H
#define ANIMATIONSTATES_H

#include "../../../fsm/state.h"

class AnimationBreslin;

class IDLE_INTERPOLATETICK_ANIMATION : public State<AnimationBreslin>
{
private:
  IDLE_INTERPOLATETICK_ANIMATION(){}
public:
  static IDLE_INTERPOLATETICK_ANIMATION* Instance();
  void enter  (AnimationBreslin* animation);
  void execute(AnimationBreslin* animation);
  void exit   (AnimationBreslin* animation);
  bool onLetter(AnimationBreslin* animation, Letter* letter);
};


class RUN_INTERPOLATETICK_ANIMATION : public State<AnimationBreslin>
{
private:
  RUN_INTERPOLATETICK_ANIMATION(){}
public:
  static RUN_INTERPOLATETICK_ANIMATION* Instance();
  void enter  (AnimationBreslin* animation);
  void execute(AnimationBreslin* animation);
  void exit   (AnimationBreslin* animation);
  bool onLetter(AnimationBreslin* animation, Letter* letter);
};

#endif
