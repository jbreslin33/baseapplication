var ApplicationGlobal = new Class(
{
	
initialize: function(application)
{
	this.mApplication = application;
},

enter: function()
{

},

execute: function()
{
	if (this.mApplication.mSetup)
	{
		//graphics
		this.mApplication.runGraphics();
	}
},

exit: function()
{

}

});
