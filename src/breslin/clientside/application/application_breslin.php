var ApplicationBreslin = new Class(
{

initialize: function(serverIP, serverPort)
{
	//StartLog ...don't need to just need log function	

	this.mNetwork = new Network(this,serverIP,serverPort);
        
	//initilize
        this.mSetup = false;
        this.mPlayingGame = false;

        //time
        this.mRenderTime = 0.0;

        //game
        this.mGame = 0;

        //state machine (Menus)
        this.mStateMachine = new StateMachine();

/*
        this.mApplicationGlobal = new ApplicationGlobal(this);
        this.mApplicationInitialize = new ApplicationInitialize(this);
        this.mApplicationMain   = new ApplicationMain  (this);
        this.mApplicationPlay   = new ApplicationPlay(this);

        this.mStateMachine.setGlobalState (mApplicationGlobal);
        this.mStateMachine.changeState(mApplicationInitialize);	
*/
		document.getElementById("demo").innerHTML="My First JavaScript";	
	},

        log: function(msg)
        {
                setTimeout(function()
                {
                        throw new Error(msg);
                }, 0);
        },

	


});

