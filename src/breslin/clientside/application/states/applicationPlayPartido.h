#ifndef APPLICATIONPLAYPARTIDO_H
#define APPLICATIONPLAYPARTIDO_H

#include "applicationPlay.h"

class ApplicationPartido;

class ApplicationPlayPartido : public ApplicationPlay
{
public:
ApplicationPlayPartido(ApplicationPartido* application);
~ApplicationPlayPartido();

ApplicationPartido* mApplication;


virtual void enter  ();
virtual void execute();
virtual void exit   ();

};

#endif
