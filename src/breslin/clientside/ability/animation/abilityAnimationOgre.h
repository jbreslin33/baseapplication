#ifndef ABILITYANIMATIONOGRE_H
#define ABILITYANIMATIONOGRE_H

#define NUM_ANIMS 13           // number of animations the character has
#define ANIM_FADE_SPEED 7.5f   // animation crossfade speed in % of full weight per second

#include "abilityAnimation.h"

//Ogre headers
#include "Ogre.h"
using namespace Ogre;

class ShapeDynamicOgre;

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

	AbilityAnimationOgre(ShapeDynamicOgre* shape);
	~AbilityAnimationOgre();

/******************************************************
*				VARIABLES
********************************************************/
//animation
ShapeDynamicOgre* mShape;
Ogre::AnimationState* mAnims[NUM_ANIMS];     // master animation list
AnimID                mBaseAnimID;           // current base (full- or lower-body) animation
AnimID                mTopAnimID;            // current top (upper-body) animation
bool                  mFadingIn[NUM_ANIMS];  // which animations are fading in
bool                  mFadingOut[NUM_ANIMS]; // which animations are fading out
Ogre::AnimationState  *mAnimationState;

/******************************************************
*				METHODS
********************************************************/
void setupAnimations();
void runAnimations();
void enterAnimationState(ShapeDynamicState* animationState);
void fadeAnimations   (Real deltaTime);
void setTopAnimation  (AnimID id, bool reset);
void setBaseAnimation (AnimID id, bool reset);


};

#endif