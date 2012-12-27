var ApplicationPlay = new Class(
{
	
initialize: function(applicationBreslin)
{
	this.mApplicationBreslin = applicationBreslin;
},

enter: function()
{

},

execute: function()
{
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
/*
     mApplicationBreslin->shutdown();

        mApplicationBreslin->getSceneManager()->destroyAllEntities();
        delete mApplicationBreslin->mGame;

        mApplicationBreslin->showMainScreen();

*/
}

});
