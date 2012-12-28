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
	if (this.mApplicationBreslin.mKey_esc)
        {
                this.mApplicationBreslin.mPlayingGame = false;
                this.mApplicationBreslin.mStateMachine.changeState(this.mApplicationBreslin.mApplicationMain);
        }
        else
        {
                //game
                this.mApplicationBreslin.mGame.processUpdate();
        }
},

exit: function()
{
	this.mApplicationBreslin.log('ApplicationPlay: exit');
     	
	this.mApplicationBreslin.shutdown();

        //mApplicationBreslin->getSceneManager()->destroyAllEntities();
        //delete mApplicationBreslin->mGame;

        this.mApplicationBreslin.showMainScreen();

}

});
