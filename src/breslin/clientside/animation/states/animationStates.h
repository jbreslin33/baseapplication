#ifndef ANIMATIONSTATES_H
#define ANIMATIONSTATES_H

#include "../animationBreslin.h"

class IDLE_INTERPOLATETICK_ANIMATION : public State<AnimationBreslin>
{
private:
  IDLE_INTERPOLATETICK_ANIMATION(){}
public:
  static IDLE_INTERPOLATETICK_ANIMATION* Instance();
  void enter  (AnimationBreslin* animationBreslin);
  void execute(AnimationBreslin* animationBreslin);
  void exit   (AnimationBreslin* animationBreslin);
  bool onLetter(AnimationBreslin* animationBreslin, Letter* letter);

};


class RUN_INTERPOLATETICK_ANIMATION : public State<AnimationBreslin>
{
private:
  RUN_INTERPOLATETICK_ANIMATION(){}
public:
  static RUN_INTERPOLATETICK_ANIMATION* Instance();
  void enter  (AnimationBreslin* animationBreslin);
  void execute(AnimationBreslin* animationBreslin);
  void exit   (AnimationBreslin* animationBreslin);
  bool onLetter(AnimationBreslin* animationBreslin, Letter* letter);
};

#endif
