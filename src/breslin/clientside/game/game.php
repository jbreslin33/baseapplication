var Game = new Class(
{

initialize: function(applicationBreslin)
{
	// constants
	this.mCommandKey          = 1;
	this.mCommandFrameTime = 2;

	this.mMessageFrame = 1;

	this.mMessageAddShape    = -103;
	this.mMessageRemoveShape = -104;

	//application	
	this.mApplicationBreslin = applicationBreslin;	

	//shapes
	this.mShapeVector      = new Array();
	this.mShapeGhostVector = new Array();

        //keys
        this.mKeyUp = 1;
        this.mKeyDown = 2;
        this.mKeyLeft = 4;
        this.mKeyRight = 8;
        this.mKeyCounterClockwise = 16;
        this.mKeyClockwise = 32;

        //input
        this.mKeyCurrent = 0;
        this.mKeyLast = 0;

        //sequence
        this.mOutgoingSequence               = 1;

        //time
        this.mRunNetworkTime = 0.0;

       	//states 
	this.mStateMachine = new StateMachine();
        
        this.mGameGlobal = new GameGlobal(this);
        this.mGameInitialize = new GameInitialize(this);
        this.mGamePlay = new GamePlay(this);
        this.mGamePause = new GamePause(this);

        this.mStateMachine.setGlobalState(this.mGameGlobal);
        this.mStateMachine.changeState(this.mGamePlay);

/*
        //set Camera
        // Position it at 500 in Z direction
        mApplicationBreslin->getCamera()->setPosition(Ogre::Vector3(0,20,20));
        // Look back along -Z
        mApplicationBreslin->getCamera()->lookAt(Ogre::Vector3(0,0,0));
        mApplicationBreslin->getCamera()->setNearClipDistance(5);
*/

},

log: function(msg)
{
	setTimeout(function()
        {
        	throw new Error(msg);
        }, 0);
},
/*********************************
                Update
**********************************/

processUpdate: function()
{
	this.mStateMachine.update();

	for (i = 0; i < this.mShapeVector.length; i++)
	{
		this.mShapeVector[i].interpolateTick(this.mApplicationBreslin.getRenderTime());
	}
},

/*********************************
               NETWORK 
**********************************/
pack: function(bytes) {
    var chars = [];
    for(var i = 0, n = bytes.length; i < n;) {
        chars.push(((bytes[i++] & 0xff) << 8) | (bytes[i++] & 0xff));
    }
    return String.fromCharCode.apply(null, chars);
},

unpack: function(str) {
    var bytes = [];
    for(var i = 0, n = str.length; i < n; i++) {
        var char = str.charCodeAt(i);
        bytes.push(char >>> 8, char & 0xFF);
    }
    return bytes;
},

sendByteBuffer: function()
{
        this.mRunNetworkTime += this.mApplicationBreslin.getRenderTime() * 1000.0;
  	
	// Framerate is too high
        if(this.mRunNetworkTime > (1000 / 60))
        {
                // Build delta-compressed move command
                flags = 0;

                //if key has not been changed return having done nothing
                if(this.mKeyLast != this.mKeyCurrent)
                {
                        flags |= this.mCommandKey;
                }
                else
                {
                        return;
                }

                // Send the packet
                this.mApplicationBreslin.mNetwork.sendMove(this.mMessageFrame,this.mOutgoingSequence,flags,this.mKeyCurrent);

                //set 'last' commands for diff
                this.mKeyLast = this.mKeyCurrent;
                
		this.mOutgoingSequence++; //increase for next time...
		
		//reset network time so we can start count anew
		this.mRunNetworkTime = 0.0;
	}
},


/***************************************
*                       INPUT
******************************************/

processInput: function()
{
	this.mKeyCurrent = 0;

	if (this.mApplicationBreslin.mKey_up)
	{
		this.mKeyCurrent |= this.mKeyUp;
	}
	if (this.mApplicationBreslin.mKey_down)
	{
		this.mKeyCurrent |= this.mKeyDown;
	}
	if (this.mApplicationBreslin.mKey_left)
	{
		this.mKeyCurrent |= this.mKeyLeft;
	}
	if (this.mApplicationBreslin.mKey_right)
	{
		this.mKeyCurrent |= this.mKeyRight;
	}

	if (this.mApplicationBreslin.mKey_z)
	{
		this.mKeyCurrent |= this.mKeyCounterClockwise;
	}
	if (this.mApplicationBreslin.mKey_x)
	{
		this.mKeyCurrent |= this.mKeyClockwise;
	}
}

});

