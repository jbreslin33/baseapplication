#ifndef APPLICATIONGAMERESET_H
#define APPLICATIONGAMERESET_H

#include "../../../statemachine/state.h"

class ApplicationBreslin;

class ApplicationGameReset : public State
{
public:
ApplicationGameReset(ApplicationBreslin* applicationBreslin);
~ApplicationGameReset();

ApplicationBreslin* mApplicationBreslin;


virtual void enter  ();
virtual void execute();
virtual void exit   ();

};

#endif
