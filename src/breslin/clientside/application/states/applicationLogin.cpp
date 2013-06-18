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
	mApplication->mLabelFocus = mApplication->mLabelUsername;

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
        	if (mApplication->mKeyArray[8]) //backspace
		{
        		mApplication->mKeyArray[8] = false;
                	int size = mApplication->mStringUsername.size();
                        if (size > 0)
                        {
                                mApplication->mStringUsername.resize(size - 1);
                        }
                        mApplication->mLabelUsername->setCaption(mApplication->mStringUsername);
                }

      	 	if (mApplication->mKeyArray[9]) //tab
		{
        		mApplication->mKeyArray[9] = false;
                        mApplication->mLabelFocus = mApplication->mLabelPassword;

		}

		if (mApplication->mKeyArray[13]) //enter
		{
        		mApplication->mKeyArray[13] = false;
                        mApplication->mLabelFocus = mApplication->mLabelPassword;

		}

		for (int i = 47; i < 123; i++)
		{
			if (mApplication->mKeyArray[i])
			{
        			mApplication->mKeyArray[i] = false;
				char ascii = (char)i;
                                mApplication->mStringUsername.append(1,ascii);
                                mApplication->mLabelUsername->setCaption(mApplication->mStringUsername);
			}
		} 
	}

	if (mApplication->mLabelFocus == mApplication->mLabelPassword)
	{

        	if (mApplication->mKeyArray[8]) //backspace
		{
        		mApplication->mKeyArray[8] = false;
                	int size = mApplication->mStringPassword.size();
                        if (size > 0)
                        {
                                mApplication->mStringPassword.resize(size - 1);
                        }
                        mApplication->mLabelPassword->setCaption(mApplication->mStringPassword);
                }

		if (mApplication->mKeyArray[13]) //enter
		{
        		mApplication->mKeyArray[13] = false;
                        
			//let's simulate hitting login button
                        if (mApplication->mStringUsername.size() > 0)
                        {
                        	mApplication->sendLogin();
                        }
		}

		for (int i = 47; i < 123; i++)
		{
			if (mApplication->mKeyArray[i])
			{
        			mApplication->mKeyArray[i] = false;
				char ascii = (char)i;
                                mApplication->mStringPassword.append(1,ascii);
                                mApplication->mLabelPassword->setCaption(mApplication->mStringPassword);
			}
		} 
	}	
}

void ApplicationLogin::exit()
{
	mApplication->mStringUsername.clear();
	mApplication->mStringPassword.clear();

	mApplication->mLabelUsername->setCaption("Username");
	mApplication->mLabelPassword->setCaption("Password");

	mApplication->hideLoginScreen();
}

