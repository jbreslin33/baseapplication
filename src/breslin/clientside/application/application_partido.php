var ApplicationPartido = new Class(
{

Extends: ApplicationBreslin,

initialize: function(serverIP, serverPort)
{
	this.parent(serverIP,serverPort);
  	
	/*****GUI******/

        //main screen
        this.mButtonJoinGameB = 0;

},


log: function(msg)
{
	setTimeout(function()
        {
        	throw new Error(msg);
        }, 0);
},

createStates: function()
{
	this.mApplicationGlobal     = new ApplicationGlobal     (this);
        this.mApplicationInitialize = new ApplicationInitialize (this);
        this.mApplicationLogin      = new ApplicationLogin      (this);
        this.mApplicationMain       = new ApplicationMainPartido(this);
        this.mApplicationPlay       = new ApplicationPlay       (this);
},

setStates: function()
{
	this.mStateMachine.setGlobalState  (this.mApplicationGlobal    );
        this.mStateMachine.changeState     (this.mApplicationInitialize);
        this.mStateMachine.setPreviousState(this.mApplicationInitialize);
},

//MAIN SCREEN
createMainScreen: function()
{
	this.parent();

  	//join game B
        if (this.mButtonJoinGameB == 0)
        {
                this.mButtonJoinGameB = this.createButton(300,150,100,50,"green","Join Game B");
                this.mButtonJoinGameB.onclick = function()
                {
                        mApplication.mButtonHit = mApplication.mButtonJoinGameB;
                };
        }
},

showMainScreen: function()
{
	this.parent();

        this.mButtonJoinGameB.style.display="block";
},

hideMainScreen: function()
{
	this.parent();

        this.mButtonJoinGameB.style.display="none";
},

//battle
createBattleScreen: function()
{

},

hideBattleScreen: function()
{

},


hideBattleScreen: function()
{

}


});

/*
*/
