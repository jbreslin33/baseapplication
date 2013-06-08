var ApplicationPartido = new Class(
{

Extends: ApplicationBreslin,

initialize: function(serverIP, serverPort)
{
	this.parent(serverIP,serverPort);
	this.log('ApplicationPartido::ApplicationPartido');  	
	/*****GUI******/

        //main screen
        this.mButtonJoinGameB = 0;

	//battle
        this.mLabelQuestion = 0;
        this.mLabelAnswer = 0;
	
	this.mStringQuestion = '';
	this.mStringAnswer = '';
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
	this.log('ApplicationPartido::createStates');  	
	this.mApplicationGlobal     = new ApplicationGlobal     (this);
        this.mApplicationInitialize = new ApplicationInitialize (this);
        this.mApplicationLogin      = new ApplicationLogin      (this);
        this.mApplicationMain       = new ApplicationMainPartido(this);
        this.mApplicationPlay       = new ApplicationPlay       (this);
},

setStates: function()
{
	this.log('ApplicationPartido::setStates');  	
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
 	if (this.mLabelQuestion == 0)
        {
                this.mLabelQuestion = this.createLabel(300,75,100,25,"blue","Question:");
        }

        if (this.mLabelAnswer == 0)
        {
                this.mLabelAnswer= this.createLabel(300,100,100,25,"yellow","Answer:");
        }
},

showBattleScreen: function()
{
        this.mLabelUsername.style.display="block";
        this.mLabelPassword.style.display="block";
},


hideBattleScreen: function()
{
        this.mLabelUsername.style.display="none";
        this.mLabelPassword.style.display="none";
}


});

/*
*/
