#ifndef APPLICATIONPARTIDO_H
#define APPLICATIONPARTIDO_H

//parents
#include "../applicationBreslin.h"

#include "../../../fsm/stateMachine.h"

template <class entity_type> class State;

class GamePartido;

class ApplicationPartido : public ApplicationBreslin
{
public:
	
	ApplicationPartido(const char* serverIP, int serverPort);
	~ApplicationPartido();

//state machine
StateMachine<ApplicationPartido>* mPartidoStateMachine;

//game partido
GamePartido* mGamePartido;
void setGame(GamePartido* gamePartido);
virtual void createGame();

//rendering
virtual bool frameRenderingQueued (const Ogre::FrameEvent& evt);

static const char mMessageAnswerQuestion  = -84;
static const char mMessageGameStart  = -57;
static const char mMessageGameEnd    = -58;

//main
OgreBites::Button* mButtonJoinGameB;

//processUpdate
virtual void processUpdate();

//main
virtual void createMainScreen();
virtual void showMainScreen();
virtual void hideMainScreen();

//battle
void createBattleScreen();
void showBattleScreen();
void hideBattleScreen();
OgreBites::Label* mLabelQuestion;
OgreBites::Label* mLabelAnswer;
std::string mStringAnswer;
std::string mStringQuestion;

//correctAnswer
void createCorrectAnswerScreen();
void showCorrectAnswerScreen();
void hideCorrectAnswerScreen();
OgreBites::Label* mLabelCorrectAnswer;
std::string mStringCorrectAnswer;

//time
unsigned short mAnswerTime;

void sendAnswer();

};

#endif
