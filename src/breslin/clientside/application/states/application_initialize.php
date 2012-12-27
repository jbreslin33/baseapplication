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
        if (this.mApplicationBreslin.setup())
        {
        	this.mApplicationBreslin.mSetup = true;
                this.mApplicationBreslin.createMainScreen();
        	this.mApplicationBreslin.mStateMachine.changeState(this.mApplicationBreslin.mApplicationMain);
        }
},

exit: function()
{

}

});
