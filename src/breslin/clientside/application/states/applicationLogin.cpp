//header
#include "applicationLogin.h"

//log
#include "../../tdreamsock/dreamSockLog.h"

//application
#include "../applicationBreslin.h"

//state machine
#include "../../../statemachine/stateMachine.h"

/***************************************
*	CONSTRUCTORS
***************************************/
ApplicationLogin::ApplicationLogin(ApplicationBreslin* application)
{
	mApplication = application;
}

ApplicationLogin::~ApplicationLogin()
{

}

void ApplicationLogin::enter()
{
	mApplication->createLoginScreen();
	mApplication->showLoginScreen();
}

void ApplicationLogin::execute()
{
	if (mApplication->mLoggedIn == true)
	{
		mApplication->mStateMachine->changeState(mApplication->mApplicationMain);
	}

	if (mApplication->mButtonHit == mApplication->mButtonLogin)
	{
		mApplication->mButtonHit = NULL;
		if (mApplication->mStringUsername.size() > 0) 
		{
			mApplication->sendLogin();
		}
	}

	if (mApplication->mButtonHit == mApplication->mButtonExit)
	{
		mApplication->mStateMachine->changeState(NULL);
		mApplication->mStateMachine->setGlobalState(NULL);
		mApplication->mButtonHit = NULL;
		mApplication->shutdown();
		mApplication->mShutDown = true;
		delete mApplication;
	}

	//for keys
	if (mApplication->mLabelFocus == mApplication->mLabelUsername)
        {
        	if (mApplication->mKeyArray[8] == true) //backspace
		{
        		mApplication->mKeyArray[8] = false;
			LogString("backspace");
                	int size = mApplication->mStringUsername.size();
                        if (size > 0)
                        {
                                mApplication->mStringUsername.resize(size - 1);
                        }
                        mApplication->mLabelUsername->setCaption(mApplication->mStringUsername);
                }
	}
/*
                        if (numeric == 9) //tab
                        {
                                mLabelFocus = mLabelPassword;
                        }
                        if (numeric == 13) //enter
                        {
                                mLabelFocus = mLabelPassword;
                        }

                        if (numeric > 47 && numeric < 123) //letters and valid symbols for username and password
                        {
                                mStringUsername.append(1,ascii);
                                mLabelUsername->setCaption(mStringUsername);
                        }
                }

                if (mLabelFocus == mLabelPassword)
                {
                        int numeric = arg.text;
                        char ascii = (char)numeric;

                        if (numeric == 8) //backspace
                        {
                                int size = mStringPassword.size();
                                if (size > 0)
                                {
                                        mStringPassword.resize(size - 1);
                                }
                                mLabelPassword->setCaption(mStringPassword);
                        }

                        if (numeric == 9) //tab
                        {
                        }
                        if (numeric == 13) //enter
                        {
                                //let's simulate hitting login button
                                if (mStringUsername.size() > 0)
                                {
                                        sendLogin();
                                }

                        }

                        if (numeric > 47 && numeric < 123) //letters and valid symbols for username and password
                        {
                                mStringPassword.append(1,ascii);
                                mLabelPassword->setCaption(mStringPassword);
                        }
*/
}

void ApplicationLogin::exit()
{
	mApplication->mStringUsername.clear();
	mApplication->mStringPassword.clear();

	mApplication->mLabelUsername->setCaption("Username");
	mApplication->mLabelPassword->setCaption("Password");

	mApplication->hideLoginScreen();
}

