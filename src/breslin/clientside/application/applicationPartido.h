#ifndef APPLICATIONPARTIDO_H
#define APPLICATIONPARTIDO_H

//parents
#include "applicationBreslin.h"


class ApplicationPartido : public ApplicationBreslin
{
public:
	
	ApplicationPartido(const char* serverIP, int serverPort);
	~ApplicationPartido();

//main
OgreBites::Button* mButtonJoinGameB;

//processUpdate
virtual void processUpdate();

//states
virtual void createStates();
virtual void setStates();

//main
virtual void createMainScreen();
virtual void showMainScreen();
virtual void hideMainScreen();


};

#endif
