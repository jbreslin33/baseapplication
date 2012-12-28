var ApplicationPlay = new Class(
{
	
initialize: function(applicationBreslin)
{
	this.mApplicationBreslin = applicationBreslin;
},

enter: function()
{
	this.mApplicationBreslin.log('ApplicationPlay: enter');
},

execute: function()
{
	this.mApplicationBreslin.log('ApplicationPlay: execute');
/*
       if (mApplicationBreslin->getKeyboard()->isKeyDown(OIS::KC_ESCAPE))
        {
                mApplicationBreslin->mPlayingGame = false;
                mApplicationBreslin->mStateMachine->changeState(mApplicationBreslin->mApplicationMain);
        }
        else
        {
                //game
                mApplicationBreslin->mGame->processUpdate();
        }
*/
},

exit: function()
{
	this.mApplicationBreslin.log('ApplicationPlay: exit');
/*
     mApplicationBreslin->shutdown();

        mApplicationBreslin->getSceneManager()->destroyAllEntities();
        delete mApplicationBreslin->mGame;

        mApplicationBreslin->showMainScreen();

*/
}

});
