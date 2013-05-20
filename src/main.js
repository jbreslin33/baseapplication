var mApplication;
var mSize = 0;
var mMiddleOfViewPort = new Vector3D();;

window.addEvent('domready', function()
{
       	mSize = window.getSize();

        //let's move control object to middle of screen
        mMiddleOfViewPort.x =  mSize.x / 2;
        mMiddleOfViewPort.y =  0;
        mMiddleOfViewPort.z =  mSize.y / 2;

        mApplication = new ApplicationPartido(mIP,'10001');
	mApplication.createStates();
	mApplication.setStates();
       	
        //input
        document.addEvent("keydown", mApplication.keyDown);
        document.addEvent("keyup", mApplication.keyUp);

        //main loop
	mIntervalCount = 0;
        mInterval=setInterval("mApplication.processUpdate()",32)
        
	mApplication.mNetwork.mSocket.on('news', function (data)
        {
		mApplication.mTimeSinceLastServerTick = 0;

                s = data.split(',');

                byteBuffer = new ByteBuffer(s);

                type = byteBuffer.readByte();
		//mApplication.log('type:' + type);

		//mMessageConnected
  		if (type == -90)
                {
                        mApplication.mConnected = true;
                }

		//mMessageAskQuestion
		if (type == -76)
		{
			if (mApplication.mGame)
                        {
                                mApplication.mGame.askQuestion(byteBuffer);
                        }
                        else
                        {
                                mApplication.log('no game yet on client!');
                        }
		}

		//mMessageBattleStart
		if (type == -75)
		{
			if (mApplication.mGame)
                        {
                                mApplication.mGame.battleStart(byteBuffer);
                        }
                        else
                        {
                                mApplication.log('no game yet on client!');
                        }
			
		}

		//mMessageBattleEnd
		if (type == -74)
		{
			if (mApplication.mGame)
                        {
                                mApplication.mGame.battleEnd(byteBuffer);
                        }
                        else
                        {
                                mApplication.log('no game yet on client!');
                        }
			
		}

		if (type == -109)
		{
/*
                	length = byteBuffer.readByte();
			mApplication.log('length:' + length);			
			var string = "";
			for (i = 0; i < length; i++)
			{
				string = string + byteBuffer.readByte();
			}
			

			var option=document.createElement("option");
			option.text=string;
			try
  			{
  				// for IE earlier than version 8
  				mApplication.mSelectMenuSchool.add(option,x.options[null]);
  			}
			catch (e)
  			{
  				mApplication.mSelectMenuSchool.add(option,null);
  			}
*/
		}
	
                if (type == -103)
                {
			if (mApplication.mGame)
			{
				
				mApplication.mGame.addShape(byteBuffer);
			}
			else
			{
				mApplication.log('no game yet on client!');
			}
                }
	
                if (type == -104)
		{
			if (mApplication.mGame)
			{
				mApplication.mGame.removeShape(byteBuffer);
			}
			else
			{
				mApplication.log('no game so cant process -104');
			}
		}

		if (type == mApplication.mMessageLoggedIn)
                {
                        mApplication.mLoggedIn = true;
                }

                if (type == mApplication.mMessageLoggedOut)
                {
                        mApplication.mLoggedIn = false;
                }

                if (type == mApplication.mMessageLeaveGame)
                {
                        mApplication.mLeaveGame = true;
                }

                if (type == 1)
                {
			if (mApplication.mGame)
			{
				mIntervalCount++;
		
				//check if we stopped game loop	
				if (mIntervalCount > 25)
				{
					//game loop stopped so let's clear interval and start a new one.	
					mApplication.log('gameloop stopped');
					//clear it
					clearInterval(mInterval);

					//set it again
        				mInterval=setInterval("mApplication.processUpdate()",32)

					mIntervalCount = 0;

				}
                        	mApplication.mGame.readServerTick(byteBuffer);
			}
                }
        });
}
);

window.onresize = function(event)
{
	mSize = window.getSize();	

        //let's move control object to middle of screen
        mMiddleOfViewPort.x =  mSize.x / 2;
        mMiddleOfViewPort.y =  0;
        mMiddleOfViewPort.z =  mSize.y / 2;
    	//mApplication.mNetwork.mSocket.emit('send_disconnect', '');
}
