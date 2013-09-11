#ifndef ANIMATIONOGRE_H
#define ANIMATIONOGRE_H

//parent
#include "../animationBreslin.h"

//Ogre headers
#include "Ogre.h"
using namespace Ogre;

class Shape;

class AnimationOgre : public AnimationBreslin
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

	AnimationOgre(Shape* shape);
	~AnimationOgre();

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
virtual void runEnter();
virtual void runExecute();
virtual void idleEnter();
virtual void idleExecute();

//update
virtual void update() { }

//handle letter
virtual bool  handleLetter(Letter* letter) { }


};

#endif
