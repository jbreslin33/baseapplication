//header
#include "applicationStates.h"

//log
#include "../../tdreamsock/dreamSockLog.h"

//game
#include "../../application/applicationBreslin.h"

//game
#include "../../game/game.h"

//shape
#include "../../shape/shape.h"

//ability
#include "../application.h"

//utility
#include <math.h>

//command
#include "../../command/command.h"


/******************** GLOBAL_APPLICATION *****************/
/*
GLOBAL_APPLICATION* GLOBAL_APPLICATION::Instance()
{
  static GLOBAL_APPLICATION instance;
  return &instance;
}
void GLOBAL_APPLICATION::enter(Application* application)
{

}
void GLOBAL_APPLICATION::execute(Application* application)
{
  	if (application->mSetup)
        {
                //check network
                application->checkForByteBuffer();

                //graphics
                application->runGraphics();
        }

}
void GLOBAL_APPLICATION::exit(Application* application)
{
}
*/

/******************** INIT_APPLICATION *****************/
/*
INIT_APPLICATION* INIT_APPLICATION::Instance()
{
  static INIT_APPLICATION instance;
  return &instance;
}
void INIT_APPLICATION::enter(Application* application)
{
}
void INIT_APPLICATION::execute(Application* application)
{
   	//setup calls ogre specific graphics setup,
        //when it returns true we can begin our graphics stuff
        if (application->setup())
        {
                application->mSetup = true;
        }

        if (application->mSetup && application->mConnected)
        {
                application->mStateMachine->changeState(application->applicationLogin);
        }

}
void INIT_APPLICATION::exit(Application* application)
{
}
*/
/******************** LOGIN_APPLICATION *****************/
/*
LOGIN_APPLICATION* LOGIN_APPLICATION::Instance()
{
        static LOGIN_APPLICATION instance;
        return &instance;
}
void LOGIN_APPLICATION::enter(Application* application)
{
  	application->createLoginScreen();
        application->showLoginScreen();
        application->mLabelFocus = application->mLabelUsername;

}
void LOGIN_APPLICATION::execute(Application* application)
{
	if (application->mLoggedIn == true)
        {
                application->mStateMachine->changeState(application->applicationMain);
        }

        if (application->mButtonHit == application->mButtonLogin)
        {
                application->mButtonHit = NULL;
                if (application->mStringUsername.size() > 0)
                {
                        application->sendLogin();
                }
        }

        if (application->mButtonHit == application->mButtonExit)
        {
                application->mStateMachine->changeState(NULL);
                application->mStateMachine->setGlobalState(NULL);
                application->mButtonHit = NULL;
                application->shutdown();
                application->mShutDown = true;
                delete application;
        }

	//for keys
        if (application->mLabelFocus == application->mLabelUsername)
        {
                if (application->mKeyArray[8]) //backspace
                {
                        application->mKeyArray[8] = false;
                        int size = application->mStringUsername.size();
                        if (size > 0)
                        {
                                application->mStringUsername.resize(size - 1);
                        }
                        application->mLabelUsername->setCaption(application->mStringUsername);
                }

                if (application->mKeyArray[9]) //tab
                {
                        application->mKeyArray[9] = false;
                        application->mLabelFocus = application->mLabelPassword;

                }

                if (application->mKeyArray[13]) //enter
                {
                        application->mKeyArray[13] = false;
                        application->mLabelFocus = application->mLabelPassword;

                }

                for (int i = 47; i < 123; i++)
                {
                        if (application->mKeyArray[i])
                        {
                                application->mKeyArray[i] = false;
                                char ascii = (char)i;
                                application->mStringUsername.append(1,ascii);
                                application->mLabelUsername->setCaption(application->mStringUsername);
                        }
                }
        }

	if (application->mLabelFocus == application->mLabelPassword)
        {

                if (application->mKeyArray[8]) //backspace
                {
                        application->mKeyArray[8] = false;
                        int size = application->mStringPassword.size();
                        if (size > 0)
                        {
                                application->mStringPassword.resize(size - 1);
                        }
                        application->mLabelPassword->setCaption(application->mStringPassword);
                }

                if (application->mKeyArray[13]) //enter
                {
                        application->mKeyArray[13] = false;

                        //let's simulate hitting login button
                        if (application->mStringUsername.size() > 0)
                        {
                                application->sendLogin();
                        }
                }

                for (int i = 47; i < 123; i++)
                {
                        if (application->mKeyArray[i])
                        {
                                application->mKeyArray[i] = false;
                                char ascii = (char)i;
                                application->mStringPassword.append(1,ascii);
                                application->mLabelPassword->setCaption(application->mStringPassword);
                        }
                }
        }      
}
void LOGIN_APPLICATION::exit(Application* application)
{
	application->mStringUsername.clear();
        application->mStringPassword.clear();

        application->mLabelUsername->setCaption("Username");
        application->mLabelPassword->setCaption("Password");

        application->hideLoginScreen();

}

*/

/******************** MAIN_APPLICATION *****************/

/*
MAIN_APPLICATION* MAIN_APPLICATION::Instance()
{
  static MAIN_APPLICATION instance;
  return &instance;
}
void MAIN_APPLICATION::enter(Application* application)
{
	application->createMainScreen();
        application->showMainScreen();

}
void MAIN_APPLICATION::execute(Application* application)
{
	if (application->mButtonHit == application->mButtonJoinGameA)
        {
                application->mButtonHit = NULL;
                application->setGame(new Game(application));
                application->sendJoinGame(1);
                application->mStateMachine->changeState(application->applicationPlay);
        }

        if (application->mButtonHit == application->mButtonLogout)
        {
                application->mButtonHit = NULL;
                application->sendLogout();
        }

        if (application->mLoggedIn == false)
        {
                application->mStateMachine->changeState(application->applicationLogin);
        }

        if (application->mButtonHit == application->mButtonExit)
        {
                application->mStateMachine->changeState(NULL);
                application->mStateMachine->setGlobalState(NULL);
                application->mButtonHit = NULL;
                application->shutdown();
                application->mShutDown = true;
                delete application;
        }

}
void MAIN_APPLICATION::exit(Application* application)
{
	application->hideMainScreen();
}
*/

/******************** PLAY_APPLICATION *****************/
/*
PLAY_APPLICATION* PLAY_APPLICATION::Instance()
{
  static PLAY_APPLICATION instance;
  return &instance;
}
void PLAY_APPLICATION::enter(Application* application)
{
	application->mPlayingGame = true;
        application->mSentLeaveGame = false;
}
void PLAY_APPLICATION::execute(Application* application)
{
    	/check for logout as well....
        if (this->application->mLoggedIn == false )
        {
                this->application->mStateMachine->changeState(this->application->mApplicationLogin);
        }

        if (application->mKeyArray[27] && application->mSentLeaveGame == false) //esc
        {
                application->mKeyArray[27] = false;

                //send quit game
                ByteBuffer* byteBuffer = new ByteBuffer();
                byteBuffer->WriteByte(application->mMessageLeaveGame);
                application->mNetwork->send(byteBuffer);
                application->mSentLeaveGame = true;
        }

        if (application->mLeaveGame)
        {
                application->mSentLeaveGame = false;
                if (application->mLoggedIn)
                {
                        application->mStateMachine->changeState(application->mApplicationMain);
                }
                else
                {
                        application->mStateMachine->changeState(application->mApplicationLogin);
                }
        }
        else
        {
                //game
                if (application->getGame())
                {
                        application->getGame()->processUpdate();
                }
        }

}
void PLAY_APPLICATION::exit(Application* application)
{
	application->mPlayingGame = false;
        application->mLeaveGame = false;
        if (application->getGame())
        {
                application->getGame()->remove();
                application->setGame(NULL);
        }

}
*/
