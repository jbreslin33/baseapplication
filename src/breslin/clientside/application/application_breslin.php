var ApplicationBreslin = new Class(
{

initialize: function(serverIP, serverPort)
{
	this.mIntervalCount = 0;
	this.mIntervalCountLast = 0;
	//StartLog ...don't need to just need log function	

	//constants
	this.mMessageServerExit = 3;
	this.mMessageConnect     = -111; //browser code
	this.mMessageDisconnect  = -112; //browser code

	this.mAddSchool          = -109;
	this.mMessageLogin       = -125; //broswer
	this.mMessageLogout      = -126; //browser
	this.mMessageLoggedIn    = -113; 
	this.mMessageLoggedOut   = -114; 

	this.mMessageJoinGame    = -117; //browser
	this.mMessageLeaveGame   = -99; //browser
	this.mSentLeaveGame      = false; 

	//network
	this.mNetwork = new Network(this,serverIP,serverPort);
        
	//state transition variables
        this.mSetup = false;
        this.mPlayingGame = false;
	this.mConnectSent = false;
	this.mLoggedIn = false;	
	this.mLeaveGame = false;	

        //time
        this.mRenderTime = 0.0;
        this.mTimeSinceEpoch = 0;
        this.mLastTimeSinceEpoch = 0;

        //game
        this.mGame = 0;

	/*****GUI******/
	//all
	this.mButtonHit = 0;
	this.mSelectMenuHit = 0;
	this.mLabelHit = 0;
	this.mButtonExit = 0;

	//main screen
	this.mButtonJoinGame = 0;
	this.mButtonLogout = 0;

	//login	
	this.mSelectMenuSchool = 0;
	this.mLabelUsername = 0;
	this.mLabelPassword = 0;
	this.mButtonLogin = 0;
	this.mButtonExit = 0;
	this.mStringUsername = '';
	this.mStringPassword = '';

	//border
	this.mNorthBorder = 0;
	this.mEastBorder  = 0;
	this.mSouthBorder = 0;
	this.mWestBorder  = 0;

        //state machine (Menus)
        this.mStateMachine = new StateMachine();

        this.mApplicationGlobal     = new ApplicationGlobal    (this);
	this.mApplicationInitialize = new ApplicationInitialize(this);
	this.mApplicationLogin      = new ApplicationLogin     (this);
        this.mApplicationMain       = new ApplicationMain      (this);
        this.mApplicationPlay       = new ApplicationPlay      (this);

        this.mStateMachine.setGlobalState (this.mApplicationGlobal);
        this.mStateMachine.setCurrentState(this.mApplicationInitialize);
        this.mStateMachine.changeState(this.mApplicationInitialize);	

	//input
	this.mKey_up = false;
	this.mKey_down = false;
	this.mKey_right = false;
	this.mKey_left = false;
	this.mKey_counterclockwise = false;
	this.mKey_clockwise = false;
	this.mKey_esc = false;
	this.mKey_q = false;

	this.sendConnect();	

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
	//get time since epoch and set lasttime
        e = new Date();
        this.mLastTimeSinceEpoch = this.mTimeSinceEpoch;
        this.mTimeSinceEpoch = e.getTime();

        //set RenderTime as function of timeSinceEpoch and LastTimeSinceEpoch diff
        this.mRenderTime = this.mTimeSinceEpoch - this.mLastTimeSinceEpoch;
	this.mRenderTime = this.mRenderTime / 1000;
        this.mStateMachine.update();
	//document.getElementById('mMessageFrameI').innerHTML=':mSequence ' + this.mGame.mSequence;
},



/*********************************
        ADMIN
**********************************/

shutdown: function()
{

},

/*********************************
                NETWORK
**********************************/
sendConnect: function()
{
	this.mNetwork.sendConnect();
},

sendLogin: function()
{
	message = 'v1301 ahh';
	this.mNetwork.mSocket.emit('send_login', message);
},

sendLogout: function()
{
	message = '';
	this.mNetwork.mSocket.emit('send_logout', message);
},

sendJoinGame: function()
{
	message = '';
	this.mNetwork.mSocket.emit('send_join_game', message);
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
//CREATE BUTTON CONVIENCE FUNCTION
createButton: function(x,z,w,h,b,i)
{
	e = document.createElement("BUTTON");
	e.style.position = "absolute";
	e.style.left = x;
	e.style.top = z;
	e.style.width = w;
	e.style.height = h;
	e.style.background = b;
	var t=document.createTextNode(i);
	e.appendChild(t);
	document.body.appendChild(e);
	
	e.onclick = function()
	{
		mApplication.mButtonHit = e;	
	};

	return e;
},

//CREATE SELECTMenu CONVIENCE FUNCTION
createSelectMenu: function(x,z,w,h,b,i)
{
        e = document.createElement("SELECT");
        e.style.position = "absolute";
        e.style.left = x;
        e.style.top = z;
        e.style.width = w;
        e.style.height = h;
        e.style.background = b;
        document.body.appendChild(e);

        e.onclick = function()
        {
                mApplication.mSelectMenuHit = e;     
        };

        return e;
},

//CREATE Label CONVIENCE FUNCTION
createLabel: function(x,z,w,h,b,i)
{
        e = document.createElement("INPUT");
        e.style.position = "absolute";
        e.style.left = x;
        e.style.top = z;
        e.style.width = w;
        e.style.height = h;
        e.style.background = b;
        document.body.appendChild(e);

        e.onclick = function()
        {
                mApplication.mLabelHit = e;
        };

        return e;
},


//BORDERS
createBorder: function(x,z,w,h,b,i)
{
	border = document.createElement("div");
	border.style.position = "absolute";
	border.style.width = w;
	border.style.height = h;
	border.style.background = b;
	border.style.color = "white";
	border.innerHTML = i;
	border.style.left = x;
	border.style.top = z;
	
	document.body.appendChild(border);

	return border;
},

createBorders: function()
{
	this.mNorthBorder = this.createBorder("0px","0px","760px","30px","blue","");
	this.mEastBorder  = this.createBorder("760px","0px","10px","400px","blue","");
	this.mSouthBorder = this.createBorder("0px","370px","760px","30px","blue","");
	this.mWestBorder  = this.createBorder("0px","0px","10px","400px","blue","");
},

showBorders: function()
{

},

hideBorders: function()
{

},

//LOGIN SCREEN
createLoginScreen: function()
{
  	if (this.mSelectMenuSchool == 0)
        {
                this.mSelectMenuSchool = this.createSelectMenu(300,50,100,25,"green","Schools");
	}

  	if (this.mLabelUsername == 0)
	{
                this.mLabelUsername = this.createLabel(300,75,100,25,"green","Username");
	}

  	if (this.mLabelPassword == 0)
	{
                this.mLabelPassword = this.createLabel(300,100,100,25,"green","Password");
	}

	if (this.mButtonLogin == 0)
	{
        	this.mButtonLogin = this.createButton(300,125,100,50,"green","Login");
        	this.mButtonLogin.onclick = function()
        	{
                	mApplication.mButtonHit = mApplication.mButtonLogin;
        	};
	}
 	if (this.mButtonExit == 0)
        {
                this.mButtonExit = this.createButton(300,175,100,50,"green","Exit");
                this.mButtonExit.onclick = function()
                {
                        mApplication.mButtonHit = mApplication.mButtonExit;
                };
        }

},

showLoginScreen: function()
{       
        this.mSelectMenuSchool.style.display="block";
        this.mLabelUsername.style.display="block";
        this.mLabelPassword.style.display="block";
        this.mButtonLogin.style.display="block";
        this.mButtonExit.style.display="block";
},

hideLoginScreen: function()
{       
        this.mSelectMenuSchool.style.display="none";
        this.mLabelUsername.style.display="none";
        this.mLabelPassword.style.display="none";
        this.mButtonLogin.style.display="none";
        this.mButtonExit.style.display="none";
},


//MAIN SCREEN
createMainScreen: function()
{
	//join game
	if (this.mButtonJoinGame == 0)
	{
		this.mButtonJoinGame = this.createButton(300,100,100,50,"green","Join Game");
		this.mButtonJoinGame.onclick = function()
		{
			mApplication.mButtonHit = mApplication.mButtonJoinGame;	
		};
	}
	
	//logout 
	if (this.mButtonLogout == 0)
	{
		this.mButtonLogout = this.createButton(300,200,100,50,"green","Logout");
		this.mButtonLogout.onclick = function()
		{
			mApplication.mButtonHit = mApplication.mButtonLogout;	
		};
	}

	//create Borders	
	this.createBorders();
},

showMainScreen: function()
{
	this.mButtonJoinGame.style.display="block";
	this.mButtonLogout.style.display="block";
},

hideMainScreen: function()
{
	this.mButtonJoinGame.style.display="none";
	this.mButtonLogout.style.display="none";
},


/*********************************
                GRAPHICS
**********************************/
runGraphics: function()
{
	//no idea what to do here for browser code so i will leave blank since it's called from states
},

/*********************************
                INPUT 
**********************************/
keyDown: function(event)
{
	//left
        if (event.key == 'left')
        {
        	mApplication.mKey_left = true;
        }

        //right
        if (event.key == 'right')
        {
                mApplication.mKey_right = true;
        }

        //up
        if (event.key == 'up')
        {
                mApplication.mKey_up = true;
        }

        //down
        if (event.key == 'down')
        {
                mApplication.mKey_down = true;
        }

	//counterclockwise
        if (event.key == 'z')
        {
                mApplication.mKey_counterclockwise = true;
	}

	//clockwise
        if (event.key == 'x')
        {
                mApplication.mKey_clockwise = true;
	}
	
	//escape
        if (event.key == 'esc')
        {
                mApplication.mKey_esc = true;
	}

	//quit game
        if (event.key == 'q')
        {
                mApplication.mKey_q = true;
	}
},

keyUp: function(event)
{
	//left
        if (event.key == 'left')
        {
                mApplication.mKey_left = false;
        }

        //right
        if (event.key == 'right')
        {
                mApplication.mKey_right = false;
        }

        //up
        if (event.key == 'up')
        {
                mApplication.mKey_up = false;
        }

        //down
        if (event.key == 'down')
        {
                mApplication.mKey_down = false;
        }
        
	//counterclockwise
        if (event.key == 'z')
        {
                mApplication.mKey_counterclockwise = false;
	}

	//clockwise
        if (event.key == 'x')
        {
                mApplication.mKey_clockwise = false;
	}
	
	//escape
        if (event.key == 'esc')
        {
                mApplication.mKey_esc = false;
	}

	//quit game
        if (event.key == 'q')
        {
                mApplication.mKey_q = false;
	}
}


});

