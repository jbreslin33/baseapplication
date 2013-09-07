//header
#include "applicationPartidoStates.h"

//log
#include "../../../tdreamsock/dreamSockLog.h"

//game
#include "../../../application/partido/applicationPartido.h"

//game
#include "../../../game/partido/gamePartido.h"

//shape
#include "../../../shape/shape.h"

//utility
#include <math.h>

//command
#include "../../../command/command.h"


/******************** GLOBAL_PARTIDO_APPLICATION *****************/

GLOBAL_PARTIDO_APPLICATION* GLOBAL_PARTIDO_APPLICATION::Instance()
{
  static GLOBAL_PARTIDO_APPLICATION instance;
  return &instance;
}
void GLOBAL_PARTIDO_APPLICATION::enter(ApplicationPartido* application)
{
}
void GLOBAL_PARTIDO_APPLICATION::execute(ApplicationPartido* application)
{
}
void GLOBAL_PARTIDO_APPLICATION::exit(ApplicationPartido* application)
{
}
bool GLOBAL_PARTIDO_APPLICATION::onLetter(ApplicationPartido* application, Letter* letter)
{
        return true;
}

/******************** INIT_PARTIDO_APPLICATION *****************/

INIT_PARTIDO_APPLICATION* INIT_PARTIDO_APPLICATION::Instance()
{
  static INIT_PARTIDO_APPLICATION instance;
  return &instance;
}
void INIT_PARTIDO_APPLICATION::enter(ApplicationPartido* application)
{
}
void INIT_PARTIDO_APPLICATION::execute(ApplicationPartido* application)
{
}
void INIT_PARTIDO_APPLICATION::exit(ApplicationPartido* application)
{
}
bool INIT_PARTIDO_APPLICATION::onLetter(ApplicationPartido* application, Letter* letter)
{
        return true;
}

/******************** PLAY_PARTIDO_APPLICATION *****************/

PLAY_PARTIDO_APPLICATION* PLAY_PARTIDO_APPLICATION::Instance()
{
        static PLAY_PARTIDO_APPLICATION instance;
        return &instance;
}
void PLAY_PARTIDO_APPLICATION::enter(ApplicationPartido* application)
{
  	application->createLoginScreen();
        application->showLoginScreen();
        application->mLabelFocus = application->mLabelUsername;

}
void PLAY_PARTIDO_APPLICATION::execute(ApplicationPartido* applicationPartido)
{
	//check for logout as well....
        if (applicationPartido->mLoggedIn == false )
        {
               // applicationPartido->mStateMachine->changeState(LOGIN_APPLICATION::Instance());
        }

        if (applicationPartido->mKeyArray[27]) //esc
        {
                //check to see if in battle....
/*
                if (applicationPartido->getGame()->mStateMachine->getCurrentState() == applicationPartido->getGame()->mGamePlayPartidoBattle)
                {
                        applicationPartido->mAnswerTime = 2001;
                        applicationPartido->mStringAnswer = "esc";
                        LogString("sendAnswer via esc");
                        applicationPartido->sendAnswer();
                }
                else
                {
                        applicationPartido->mKeyArray[27] = false;
                        ByteBuffer* byteBuffer = new ByteBuffer();
                        byteBuffer->WriteByte(applicationPartido->mMessageLeaveGame);
                        applicationPartido->mNetwork->send(byteBuffer);
                        applicationPartido->mSentLeaveGame = true;
                }
*/
        }
/*
        if (applicationPartido->mLeaveGame)
        {
                LogString("mLeaveGame true");
                applicationPartido->mSentLeaveGame = false;
                if (applicationPartido->mLoggedIn)
                {
                        applicationPartido->mStateMachine->changeState(applicationPartido->mApplicationMain);
                }
                else
                {
                        applicationPartido->mStateMachine->changeState(applicationPartido->mApplicationLogin);
                }
        }
        else
        {
                if (applicationPartido->getGame())
                {
                        applicationPartido->getGame()->processUpdate();
                }
        }
*/

}
void PLAY_PARTIDO_APPLICATION::exit(ApplicationPartido* applicationPartido)
{
	applicationPartido->mPlayingGame = false;
        applicationPartido->mLeaveGame = false;
        if (applicationPartido->getGame())
        {
                applicationPartido->getGame()->remove();
                applicationPartido->setGame(NULL);
        }

}
bool PLAY_PARTIDO_APPLICATION::onLetter(ApplicationPartido* application, Letter* letter)
{
        return true;
}


/******************** MAIN_APPLICATION *****************/


MAIN_PARTIDO_APPLICATION* MAIN_PARTIDO_APPLICATION::Instance()
{
  static MAIN_PARTIDO_APPLICATION instance;
  return &instance;
}
void MAIN_PARTIDO_APPLICATION::enter(ApplicationPartido* applicationPartido)
{
}
void MAIN_PARTIDO_APPLICATION::execute(ApplicationPartido* applicationPartido)
{
	//pplicationMain::execute();

        if (applicationPartido->mButtonHit == applicationPartido->mButtonJoinGameB)
        {
                LogString("ApplicationMainPartido::execute....button hit for b");
                applicationPartido->mButtonHit = NULL;
                applicationPartido->setGame(new GamePartido(applicationPartido));
                applicationPartido->sendJoinGame(2);
                applicationPartido->mPartidoStateMachine->changeState(PLAY_PARTIDO_APPLICATION::Instance());
        }

}
void MAIN_PARTIDO_APPLICATION::exit(ApplicationPartido* applicationPartido)
{
}
bool MAIN_PARTIDO_APPLICATION::onLetter(ApplicationPartido* application, Letter* letter)
{
        return true;
}
