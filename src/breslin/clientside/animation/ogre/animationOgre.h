#ifndef ABILITYANIMATIONOGRE_H
#define ABILITYANIMATIONOGRE_H

/******************************************************
*				INCLUDES
********************************************************/
//parent
#include "abilityAnimation.h"

//Ogre headers
#include "Ogre.h"
using namespace Ogre;

/******************************************************
*				FORWARD DECLARATIONS
********************************************************/
class Shape;
class AbilityAnimationState;

/******************************************************
*				CLASS
********************************************************/
class AbilityAnimationOgre : public AbilityAnimation
{

// all the animations our character has, and a null ID
// some of these affect separate body parts and will be blended together
enum AnimID
{
    ANIM_IDLE_BASE,
    ANIM_IDLE_TOP,
    ANIM_RUN_BASE,
    ANIM_RUN_TOP,
    ANIM_HANDS_CLOSED,
    ANIM_HANDS_RELAXED,
    ANIM_DRAW_SWORDS,
    ANIM_SLICE_VERTICAL,
    ANIM_SLICE_HORIZONTAL,
    ANIM_DANCE,
    ANIM_JUMP_START,
    ANIM_JUMP_LOOP,
    ANIM_JUMP_END,
    ANIM_NONE
};

public:

	AbilityAnimationOgre(Shape* shape);
	~AbilityAnimationOgre();

/******************************************************
*				VARIABLES
********************************************************/
//animation
static const int mNumberOfAnimations = 13;
float mAnimationFadeSpeed;
Shape* mShape;
Ogre::AnimationState* mAnims[mNumberOfAnimations];     // master animation list
AnimID                mBaseAnimID;           // current base (full- or lower-body) animation
AnimID                mTopAnimID;            // current top (upper-body) animation
bool                  mFadingIn[mNumberOfAnimations];  // which animations are fading in
bool                  mFadingOut[mNumberOfAnimations]; // which animations are fading out
Ogre::AnimationState  *mAnimationState;

/******************************************************
*				METHODS
********************************************************/
void setupAnimations();
void runAnimations();
void fadeAnimations   (Real deltaTime);
void setTopAnimation  (AnimID id, bool reset);
void setBaseAnimation (AnimID id, bool reset);

//animations
virtual void run();
virtual void idle();


};

#endif
