#ifndef ABILITYANIMATIONSTATES_H
#define ABILITYANIMATIONSTATES_H

#include "../../../fsm/state.h"

class AbilityAnimationOgre;


class IDLE_INTERPOLATETICK_ANIMATION : public State<AbilityAnimationOgre> 
{
private:
  IDLE_INTERPOLATETICK_ANIMATION(){}
public:
  static IDLE_INTERPOLATETICK_ANIMATION* Instance();
  void enter  (AbilityAnimationOgre* abilityAnimationOgre);
  void execute(AbilityAnimationOgre* abilityAnimationOgre);
  void exit   (AbilityAnimationOgre* abilityAnimationOgre);
  void onLetter   (AbilityAnimationOgre* abilityAnimationOgre);
  bool onLetter(AbilityAnimationOgre* abilityAnimationOgre, Letter* letter);

};


/******************************************************
*				RUN
********************************************************/
class RUN_INTERPOLATETICK_ANIMATION : public State<AbilityAnimationOgre>  
{
private:
  RUN_INTERPOLATETICK_ANIMATION(){}
public:
  static RUN_INTERPOLATETICK_ANIMATION* Instance();
  void enter  (AbilityAnimationOgre* abilityAnimationOgre);
  void execute(AbilityAnimationOgre* abilityAnimationOgre);
  void exit   (AbilityAnimationOgre* abilityAnimationOgre);
  bool onLetter(AbilityAnimationOgre* abilityAnimationOgre, Letter* letter);
};

#endif
