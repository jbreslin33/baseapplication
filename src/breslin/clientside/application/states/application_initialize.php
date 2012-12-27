var ApplicationInitialize = new Class(
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
	//setup calls ogre specific graphics setup,
        //when it returns true we can begin our graphics stuff
/*
        if (mApplicationBreslin.setup())
        {
        	mApplicationBreslin.mSetup = true;
                mApplicationBreslin.createMainScreen();
        	mApplicationBreslin.mStateMachine.changeState(mApplicationBreslin.mApplicationMain);
        }
*/
},

exit: function()
{

}

});
