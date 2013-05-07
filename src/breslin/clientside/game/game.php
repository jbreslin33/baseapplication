var Game = new Class(
{

initialize: function(applicationBreslin)
{
	this.mDelayClick = 100;
	this.mDelayClickCounter = 0;

	// constants
	this.mCommandKey          = 1;
	this.mCommandFrameTime = 2;

	this.mSequence = 0;

	this.mMessageFrame = 2;  //changed this to browser code

	this.mMessageAddShape    = -103;
	this.mMessageRemoveShape = -104;

	//application	
	this.mApplicationBreslin = applicationBreslin;	

	//shapes
	this.mShapeVector      = new Array();
	this.mShapeGhostVector = new Array();
	this.mControlObject      = 0; 
	this.mControlObjectGhost = 0; 
	this.mOffSet = new Vector3D();

	//byteBuffer
	this.mByteBuffer = new ByteBuffer();

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

        //time
        this.mRunNetworkTime = 0.0;
	this.mPollDelay = 100;
	this.mPollDelayCounter = 0;
	this.mFrameTimeServer = 0;

	this.mStateMachine = new StateMachine();
/*
        //set Camera
        // Position it at 500 in Z direction
        mApplicationBreslin->getCamera()->setPosition(Ogre::Vector3(0,20,20));
        // Look back along -Z
        mApplicationBreslin->getCamera()->lookAt(Ogre::Vector3(0,0,0));
        mApplicationBreslin->getCamera()->setNearClipDistance(5);
*/

},

createStates: function()
{
        this.mGameGlobal = new GameGlobal(this);
        this.mGameInitialize = new GameInitialize(this);
        this.mGamePlay = new GamePlay(this);
        this.mGamePause = new GamePause(this);
},

setStates: function()
{
        this.mStateMachine.setGlobalState(this.mGameGlobal);
        this.mStateMachine.changeState(this.mGamePlay);
},

log: function(msg)
{
	setTimeout(function()
        {
        	throw new Error(msg);
        }, 0);
},

remove: function()
{
	//set shapes to not visible and clear shapeArrays

	if (this.mShapeGhostVector)
	{
		for (i = 0; i < this.mShapeGhostVector.length; i++)
		{
			this.mShapeGhostVector[i].mDiv.mDiv.removeChild(this.mShapeGhostVector[i].mObjectTitle);
			this.mShapeGhostVector[i].mDiv.mDiv.removeChild(this.mShapeGhostVector[i].mMesh);
			document.body.removeChild(this.mShapeGhostVector[i].mDiv.mDiv);
		}
		//set vector to 0 length...
		this.mShapeGhostVector.length = 0;
	}
	if (this.mShapeVector)
	{
		for (i = 0; i < this.mShapeVector.length; i++)
		{
			this.mShapeVector[i].mDiv.mDiv.removeChild(this.mShapeVector[i].mObjectTitle);
			this.mShapeVector[i].mDiv.mDiv.removeChild(this.mShapeVector[i].mMesh);
			document.body.removeChild(this.mShapeVector[i].mDiv.mDiv);
		}
		//set vector to 0 length...
		this.mShapeVector.length = 0;
	}

},

/*********************************
                Update
**********************************/
processUpdate: function()
{
	//set intervalCount back to zero to signify we are still running game loop
	mIntervalCount = 0;

	//set the offset
	if (this.mControlObject)
	{
		x = parseFloat(this.mControlObject.mPosition.x);
		z = parseFloat(this.mControlObject.mPosition.z);
		x = x * 2;
		z = z * 2;

		this.mOffSet.x = parseInt(this.mApplicationBreslin.mScreenCenter.x) - parseFloat(x);
        	this.mOffSet.y = 0;
        	this.mOffSet.z = parseInt(this.mApplicationBreslin.mScreenCenter.z) - parseFloat(z);
	}

	this.mStateMachine.update();

	for (i = 0; i < this.mShapeVector.length; i++)
	{
		this.mShapeVector[i].interpolateTick(this.mApplicationBreslin.getRenderTime());
	}
},

/*********************************
               NETWORK 
**********************************/
checkForByteBuffer: function()
{

},

/*********************************
*               SHAPE
**********************************/
addShape: function(byteBuffer)
{
	shape = new Shape(this.mApplicationBreslin,byteBuffer,false);

	//ability
        abilityMove = new AbilityMove(shape);
        shape.addAbility(abilityMove);
        
	//put shape and ghost in game vectors so they can be looped and game now knows of them.
        this.mShapeVector.push(shape);
        this.mShapeGhostVector.push(shape.mGhost);
/*
	if (shape.mLocal == 1)
	{
		shape.mGhost.setVisible(true);
	}
	else
	{
		shape.mGhost.setVisible(false);
	}
*/
	shape.mGhost.setVisible(true);

},

removeShape: function(byteBuffer)
{
	if (this.mApplicationBreslin.mLeaveGame || this.mApplicationBreslin.mSentLeaveGame)
	{
		this.log('dont call');
	}
	else
	{
		this.log('call');	
 		byteBuffer.beginReading();
        	type     = byteBuffer.readByte();
        	clientID = byteBuffer.readByte();
        	index    = byteBuffer.readByte();
	
  		for (i=0; i < this.mShapeVector.length; i++)
        	{
                	if (index == this.mShapeVector[i].mIndex)
			{
				this.log('removeChild:' + index);
 				this.mShapeVector[i].mDiv.mDiv.removeChild(this.mShapeVector[i].mObjectTitle);
                        	this.mShapeVector[i].mDiv.mDiv.removeChild(this.mShapeVector[i].mMesh);
                        	document.body.removeChild(this.mShapeVector[i].mDiv.mDiv);

				this.mShapeVector.splice(i,1);
			}
			inverseIndex = index * -1;
                	if (inverseIndex == this.mShapeGhostVector[i].mIndex)
			{
				this.log('removeChild:' + inverseIndex);
 				this.mShapeGhostVector[i].mDiv.mDiv.removeChild(this.mShapeGhostVector[i].mObjectTitle);
                        	this.mShapeGhostVector[i].mDiv.mDiv.removeChild(this.mShapeGhostVector[i].mMesh);
                        	document.body.removeChild(this.mShapeGhostVector[i].mDiv.mDiv);

				this.mShapeGhostVector.splice(i,1);
			}
		}
	}
},

readServerTick: function(byteBuffer)
{
	this.mApplicationBreslin.mIntervalCountLast = this.mApplicationBreslin.mIntervalCount;
	this.mApplicationBreslin.mIntervalCount++;

	seq = byteBuffer.readByte(); //seq
	this.mSequence = seq;
	this.mFrameTimeServer = byteBuffer.readByte(); //time
	
	while (byteBuffer.mReadCount < byteBuffer.mBufferArray.length)
	{
		var id = byteBuffer.readByte();
		
		var shape = this.getShape(id);
		
		if (shape != 0)
		{
			shape.processDeltaByteBuffer(byteBuffer);
		}
		else
		{
			//do nothing
		}
	}
},

getShape: function(id)
{
	var shape = 0;

	for (i=0; i < this.mShapeVector.length; i++)
	{
		var curShape = this.mShapeVector[i];	
		if (curShape.mIndex == id)
		{
			shape = curShape;
		}
	}
	if (shape == 0)
	{
		return 0;
	}
	else
	{
		return shape;
	}
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
        	message = '1 ' + this.mKeyCurrent;
        	this.mApplicationBreslin.mNetwork.mSocket.emit('send_move', message);

                //set 'last' commands for diff
                this.mKeyLast = this.mKeyCurrent;
                
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

	if (this.mApplicationBreslin.mKey_counterclockwise)
	{
		this.mKeyCurrent |= this.mKeyCounterClockwise;
	}
	if (this.mApplicationBreslin.mKey_clockwise)
	{
		this.mKeyCurrent |= this.mKeyClockwise;
	}
}

});
