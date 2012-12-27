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

        this.mApplicationGlobal = new ApplicationGlobal(this);
	this.mApplicationInitialize = new ApplicationInitialize(this);
        this.mApplicationMain   = new ApplicationMain  (this);
        this.mApplicationPlay   = new ApplicationPlay(this);

        this.mStateMachine.setGlobalState (this.mApplicationGlobal);
        this.mStateMachine.changeState(this.mApplicationInitialize);	
	
	document.getElementById("demo").innerHTML="My First JavaScript";	
},

log: function(msg)
{
	setTimeout(function()
        {
        	throw new Error(msg);
        }, 0);
},

/*******************************

******************************/
setup: function()
{
	return true;
},

/*********************************
                GUI
**********************************/

createMainScreen: function()
{
	//make buttons
/*
        mButtonGame = mTrayMgr->createButton(OgreBites::TL_CENTER, "mButtonGame", "Join Game");
        mButtonTag = mTrayMgr->createButton(OgreBites::TL_CENTER, "mButtonTag", "Join Tag");
        mButtonTagAll = mTrayMgr->createButton(OgreBites::TL_CENTER, "mButtonTagAll", "Join TagAll");
        mButtonExit = mTrayMgr->createButton(OgreBites::TL_CENTER, "mButtonExit", "Exit Application");
*/
},

showMainScreen: function()
{
/*
     mTrayMgr->moveWidgetToTray(mButtonGame,OgreBites::TL_CENTER);
        mTrayMgr->moveWidgetToTray(mButtonTag,OgreBites::TL_CENTER);
        mTrayMgr->moveWidgetToTray(mButtonTagAll,OgreBites::TL_CENTER);
        mTrayMgr->moveWidgetToTray(mButtonExit,OgreBites::TL_CENTER);
        
        mButtonGame->show();
        mButtonTag->show();
        mButtonTagAll->show();
        mButtonExit->show();

        mTrayMgr->showCursor();
*/
},


/*********************************
                GRAPHICS
**********************************/
runGraphics: function()
{
	//no idea what to do here for browser code so i will leave blank since it's called from states
}
	


});

