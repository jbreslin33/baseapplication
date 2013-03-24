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

	//network
	this.mNetwork = new Network(this,serverIP,serverPort);
        
	//state transition variables
        this.mSetup = false;
        this.mPlayingGame = false;
	this.mConnectSent = false;
	this.mLoggedIn = false;	

        //time
        this.mRenderTime = 0.0;
        this.mTimeSinceEpoch = 0;
        this.mLastTimeSinceEpoch = 0;

        //game
        this.mGame = 0;

	/*****GUI******/
	//all
	this.mButtonHit = 0;
	this.mButtonExit = 0;

	//main screen
	this.mButtonJoinGame = 0;
	
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
	this.log('sending connect...');
	this.mNetwork.sendConnect();
},


/*********************************
               LOGIN 
**********************************/
sendLogin: function()
{
	message = 'v1301 ' + 'ahh';
	this.mNetwork.mSocket.emit('send_login', message);
},

sendLogout: function()
{
	message = '';
	this.mNetwork.mSocket.emit('send_logout', message);
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
	button = document.createElement("BUTTON");
	button.style.position = "absolute";
	button.style.left = x;
	button.style.top = z;
	button.style.width = w;
	button.style.height = h;
	button.style.background = b;
	var t=document.createTextNode(i);
	button.appendChild(t);
	document.body.appendChild(button);
	
	button.onclick = function()
	{
		mApplication.mButtonHit = button;	
	};

	return button;
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
	//logout game
        this.mButtonLogin = this.createButton(300,100,100,50,"green","Login");
        this.mButtonLogin.onclick = function()
        {
                mApplication.mButtonHit = mApplication.mButtonLogin;
        };
},

showLoginScreen: function()
{       
        this.mButtonLogin.style.display="block";
},

hideLoginScreen: function()
{       
        this.mButtonLogin.style.display="none";
},


//MAIN SCREEN
createMainScreen: function()
{
	//join game
	this.mButtonJoinGame = this.createButton(300,100,100,50,"green","Join Game");
	this.mButtonJoinGame.onclick = function()
	{
		mApplication.mButtonHit = mApplication.mButtonJoinGame;	
	};

	//logout 
	this.mButtonLogout = this.createButton(300,100,100,50,"green","Logout");
	this.mButtonLogout.onclick = function()
	{
		mApplication.mButtonHit = mApplication.mButtonLogout;	
	};

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
}


});

