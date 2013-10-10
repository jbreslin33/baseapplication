var GamePlayPartido = new Class(
{

Extends: GamePlay,


initialize: function()
{
},

log: function(msg)
{
        setTimeout(function()
        {
                throw new Error(msg);
        }, 0);
},

enter: function(gamePartido)
{
	this.log('GamePlayPartido::enter');
	this.parent(gamePartido);
},

execute: function(gamePartido)
{
        
        if (gamePartido.mApplicationPartido.mGameReset)
        {
                gamePartido.mStateMachine.changeState(gamePartido.mGamePlayPartidoReset);
        }
        else if (gamePartido.mBattleStart)
        {
                gamePartido.mStateMachine.changeState(gamePartido.mGamePlayPartidoBattle);
        }
},	

exit: function(gamePartido)
{
	this.log('GamePlayPartido::exit');
	this.parent(gamePartido);
}

});

var GamePlayPartidoBattle = new Class(
{

initialize: function()
{
},

log: function(msg)
{
        setTimeout(function()
        {
                throw new Error(msg);
        }, 0);
},

enter: function(gamePartido)
{
	//reset text labels	
	this.log('GamePlayPartidoBattle::enter');
	gamePartido.mApplicationPartido.mStringAnswer = '';
	gamePartido.mApplicationPartido.mLabelAnswer.value = '';
	gamePartido.mApplicationPartido.mLabelAnswer.focus();
	
	gamePartido.mApplicationPartido.showBattleScreen();
	gamePartido.mBattleStart = false;
        //gamePartido.mBattleEnd = false;
        gamePartido.mCorrectAnswerStart = false;
        gamePartido.mApplicationPartido.mGameReset = false;

	gamePartido.mApplicationPartido.mAnswerTime = 0;
},

execute: function(gamePartido)
{
/*
	if (gamePartido.mApplicationPartido.mAnswerTime > 2) //overtime....
        {
                gamePartido.mApplicationPartido.mLabelAnswer.value = 'oot';
                gamePartido.mApplicationPartido.sendAnswer();
		gamePartido.mApplicationPartido.mAnswerTime = 0;
        }
*/

	gamePartido.mApplicationPartido.mLabelAnswer.focus();

	if (gamePartido.mCorrectAnswerStart)
        {
		this.log('mCorrectAnswerStart true');
                gamePartido.mStateMachine.changeState(gamePartido.mGamePlayPartidoCorrectAnswer);
        }

	//check for end of batlle
	if (gamePartido.mBattleEnd)
        {
               	gamePartido.mStateMachine.changeState(gamePartido.mGamePlay);
        }
       
	if (gamePartido.mApplicationPartido.mGameReset)
        {
                gamePartido.mStateMachine.changeState(gamePartido.mGamePlayPartidoReset);
        }
	
	//for enter
   	if (gamePartido.mApplicationPartido.mLabelAnswer == document.activeElement)
       	{ 
		if (gamePartido.mApplicationPartido.mKey_enter == true)
		{
        		gamePartido.mApplicationPartido.sendAnswer();
			gamePartido.mApplicationPartido.mKey_enter = false;
		
			//reset text labels	
			gamePartido.mApplicationPartido.mStringAnswer = '';
			gamePartido.mApplicationPartido.mLabelQuestion.value = '';
			gamePartido.mApplicationPartido.mLabelAnswer.value = '';
		}
        }
},	

exit: function(gamePartido)
{
	this.log('GamePlayPartidoBattle::exit');
	gamePartido.mApplicationPartido.mStringAnswer = '';
        gamePartido.mApplicationPartido.hideBattleScreen();
        gamePartido.mBattleEnd   = false;
        gamePartido.mBattleStart = false;
	
	//reset text labels	
	gamePartido.mApplicationPartido.mStringAnswer = '';
	gamePartido.mApplicationPartido.mLabelQuestion.value = '';
	gamePartido.mApplicationPartido.mLabelAnswer.value = '';
}

});

var GamePlayPartidoCorrectAnswer = new Class(
{

initialize: function()
{
},

log: function(msg)
{
        setTimeout(function()
        {
                throw new Error(msg);
        }, 0);
},

enter: function(gamePartido)
{
	gamePartido.mApplicationPartido.showCorrectAnswerScreen();
        gamePartido.mCorrectAnswerStart = false;
	this.log('GamePlayPartidoCorrectAnswer:enter');
},

execute: function(gamePartido)
{
	if (gamePartido.mCorrectAnswerEnd || gamePartido.mBattleEnd || gamePartido.mApplicationPartido.mGameReset)
        {
		this.log('GamePlayPartidoCorrectAnswer:execute if satisfied');
                gamePartido.mStateMachine.changeState(gamePartido.mGamePlayPartidoBattle);
        }
},	

exit: function(gamePartido)
{
	this.log('GamePlayPartidoCorrectAnswer:exit');
 	gamePartido.mApplicationPartido.hideCorrectAnswerScreen();
        gamePartido.mCorrectAnswerStart = false;
        gamePartido.mCorrectAnswer      = false;
        gamePartido.mCorrectAnswerEnd   = false;

        //reset text box
        gamePartido.mApplicationPartido.mStringCorrectAnswer = '';
        gamePartido.mApplicationPartido.mLabelCorrectAnswer.value = '';
}

});

var GamePlayPartido = new Class(
{

Extends: GamePlay,


initialize: function()
{
},

log: function(msg)
{
        setTimeout(function()
        {
                throw new Error(msg);
        }, 0);
},

enter: function(gamePartido)
{
	this.parent(gamePartido);
},

execute: function(gamePartido)
{
        if (gamePartido.mBattleStart)
        {
                gamePartido.mStateMachine.changeState(gamePartido.mGamePlayPartidoBattle);
        }
        
        if (gamePartido.mApplicationPartido.mGameReset)
        {
                gamePartido.mStateMachine.changeState(gamePartido.mGamePlayPartidoReset);
        }

	this.parent(gamePartido)
},	

exit: function(gamePartido)
{
	this.parent(gamePartido);
}

});

var GamePlayPartidoReset = new Class(
{

initialize: function()
{
},

log: function(msg)
{
        setTimeout(function()
        {
                throw new Error(msg);
        }, 0);
},

enter: function(gamePartido)
{
	this.log("GamePlayPartidoReset::enter");
/*
	gamePartido.mApplicationPartido.showCorrectAnswerScreen();
        gamePartido.mCorrectAnswerStart = false;
*/
},

execute: function(gamePartido)
{
/*
	if (gamePartido.mCorrectAnswerEnd)
        {
                gamePartido.mStateMachine.changeState(gamePartido.mGamePlayPartidoBattle);
        }

        if (gamePartido.mBattleEnd)
        {
                gamePartido.mStateMachine.changeState(gamePartido.mGamePlayPartidoBattle);
        }
*/
	if (!gamePartido.mApplicationPartido.mGameReset)
        {
                gamePartido.mStateMachine.changeState(gamePartido.mGamePlay);
        }

},	

exit: function(gamePartido)
{
/*
 	gamePartido.mApplicationPartido.hideCorrectAnswerScreen();
        gamePartido.mCorrectAnswerStart = false;
        gamePartido.mCorrectAnswer      = false;
        gamePartido.mCorrectAnswerEnd   = false;

        //reset text box
        gamePartido.mApplicationPartido.mStringCorrectAnswer = '';
        gamePartido.mApplicationPartido.mLabelCorrectAnswer.value = '';
*/
}

});

