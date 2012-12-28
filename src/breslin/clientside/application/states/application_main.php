var ApplicationMain = new Class(
{
	
initialize: function(applicationBreslin)
{
	this.mApplicationBreslin = applicationBreslin;
},

enter: function()
{
//	this.mApplicationBreslin.log('ApplicationMain: enter');
        this.mApplicationBreslin.showMainScreen();
},

execute: function()
{
//	this.mApplicationBreslin.log('ApplicationMain: execute');

  	//this.mApplicationBreslin.log(this.mApplicationBreslin.mButtonGame.getTextNode());	
	if (this.mApplicationBreslin.mButtonHit == this.mApplicationBreslin.mButtonGame)
	{
	        this.mApplicationBreslin.mButtonHit = 0;
                this.mApplicationBreslin.sendConnect();
                this.mApplicationBreslin.mGame = new Game(this.mApplicationBreslin);

                this.mApplicationBreslin.hideMainScreen();

                this.mApplicationBreslin.mStateMachine.changeState(this.mApplicationBreslin.mApplicationPlay);
	}

/*
  if (mApplicationBreslin->mButtonHit == mApplicationBreslin->mButtonGame)
        {
                mApplicationBreslin->mButtonHit = NULL;
                mApplicationBreslin->sendConnect();
                mApplicationBreslin->mGame = new Game(mApplicationBreslin);

                mApplicationBreslin->hideMainScreen();

                mApplicationBreslin->mStateMachine->changeState(mApplicationBreslin->mApplicationPlay);
        }

        if (mApplicationBreslin->mButtonHit == mApplicationBreslin->mButtonTag)
        {
                mApplicationBreslin->mButtonHit = NULL;
                mApplicationBreslin->sendConnect();
                mApplicationBreslin->mGame = new GameTag(mApplicationBreslin);

                mApplicationBreslin->hideMainScreen();

                mApplicationBreslin->mStateMachine->changeState(mApplicationBreslin->mApplicationPlay);
        }

        if (mApplicationBreslin->mButtonHit == mApplicationBreslin->mButtonTagAll)
        {
                mApplicationBreslin->mButtonHit = NULL;
                mApplicationBreslin->sendConnect();
                mApplicationBreslin->mGame = new GameTag(mApplicationBreslin);

                mApplicationBreslin->hideMainScreen();

                mApplicationBreslin->mStateMachine->changeState(mApplicationBreslin->mApplicationPlay);
        }

        if (mApplicationBreslin->mButtonHit == mApplicationBreslin->mButtonExit)
        {

                mApplicationBreslin->mStateMachine->changeState(NULL);
                mApplicationBreslin->mStateMachine->setGlobalState(NULL);

                mApplicationBreslin->mButtonHit = NULL;

                mApplicationBreslin->shutdown();

                mApplicationBreslin->mShutDown = true;

                delete mApplicationBreslin;
        }
*/
},

exit: function()
{
//	this.mApplicationBreslin.log('ApplicationMain: exit');
}

});
