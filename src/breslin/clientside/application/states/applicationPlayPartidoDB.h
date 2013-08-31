#ifndef APPLICATIONPLAYPARTIDO_H
#define APPLICATIONPLAYPARTIDO_H

#include "applicationPlay.h"

class ApplicationPartido;

class ApplicationPlayPartido : public ApplicationPlay
{
public:
ApplicationPlayPartido(ApplicationPartido* applicationPartido);
~ApplicationPlayPartido();

ApplicationPartido* mApplicationPartido;


virtual void enter  ();
virtual void execute();
virtual void exit   ();

};

#endif
