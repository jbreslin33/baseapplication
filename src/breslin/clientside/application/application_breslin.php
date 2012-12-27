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
        this.mStateMachine.setCurrentState(this.mApplicationInitialize);
        this.mStateMachine.changeState(this.mApplicationInitialize);	

/*
        mStateMachine->setGlobalState (mApplicationGlobal);
        mStateMachine->changeState(mApplicationInitialize);

        mStateMachine.setGlobalState (mApplicationGlobal);
        //mStateMachine.changeState(mApplicationInitialize);
        mStateMachine.setPreviousState(mApplicationInitialize);
        mStateMachine.setCurrentState(mApplicationInitialize);

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

/*********************************
                        update
**********************************/
processUpdate: function()
{
        this.mStateMachine.update();
},

/*********************************
        ADMIN
**********************************/

shutdown: function()
{
/*
        ByteBuffer* byteBuffer = new ByteBuffer();
        byteBuffer->WriteByte(mMessageDisconnect);
        mNetwork->send(byteBuffer);
        mNetwork->reset();
*/
},

/*********************************
                NETWORK
**********************************/

sendConnect: function()
{
/*
        ByteBuffer* byteBuffer = new ByteBuffer();
        byteBuffer->WriteByte(mMessageConnect);
        mNetwork->send(byteBuffer);
*/
},


/*********************************

*               TIME
***********************************/

getRenderTime: function()
{
	return this.mRenderTime;
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
var btn=document.createElement("BUTTON");
var t=document.createTextNode("CLICK ME");
btn.appendChild(t);
document.body.appendChild(btn);
        mButtonGame = mTrayMgr->createButton(OgreBites::TL_CENTER, "mButtonGame", "Join Game");
        mButtonTag = mTrayMgr->createButton(OgreBites::TL_CENTER, "mButtonTag", "Join Tag");
        mButtonTagAll = mTrayMgr->createButton(OgreBites::TL_CENTER, "mButtonTagAll", "Join TagAll");
        mButtonExit = mTrayMgr->createButton(OgreBites::TL_CENTER, "mButtonExit", "Exit Application");
*/
this.log('create join game button');
//create Join Game button
var btn=document.createElement("BUTTON");
var t=document.createTextNode("Join Game");
btn.appendChild(t);
document.body.appendChild(btn);
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

