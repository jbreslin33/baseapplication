#ifndef APPLICATIONPARTIDO_H
#define APPLICATIONPARTIDO_H

//parents
#include "applicationBreslin.h"


class ApplicationPartido : public ApplicationBreslin
{
public:
	
	ApplicationPartido(const char* serverIP, int serverPort);
	~ApplicationPartido();

//battle
OgreBites::Label* mLabelQuestion; 
OgreBites::Label* mLabelAnswer; 

void createBattleScreen();
void showBattleScreen();
void hideBattleScreen();

};

#endif
