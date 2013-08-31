var GamePlayPartidoReset = new Class(
{

initialize: function(gamePartido)
{
	this.mGamePartido = gamePartido; 
},

log: function(msg)
{
        setTimeout(function()
        {
                throw new Error(msg);
        }, 0);
},

enter: function()
{
	this.log("GamePlayPartidoReset::enter");
/*
	this.mGamePartido.mApplicationPartido.showCorrectAnswerScreen();
        this.mGamePartido.mCorrectAnswerStart = false;
*/
},

execute: function()
{
/*
	if (this.mGamePartido.mCorrectAnswerEnd)
        {
                this.mGamePartido.mStateMachine.changeState(this.mGamePartido.mGamePlayPartidoBattle);
        }

        if (this.mGamePartido.mBattleEnd)
        {
                this.mGamePartido.mStateMachine.changeState(this.mGamePartido.mGamePlayPartidoBattle);
        }
*/
	if (!this.mGamePartido.>mApplicationPartido.mGameReset)
        {
                this.mGamePartido.mStateMachine.changeState(this.mGamePartido.mGamePlay);
        }

},	

exit: function()
{
/*
 	this.mGamePartido.mApplicationPartido.hideCorrectAnswerScreen();
        this.mGamePartido.mCorrectAnswerStart = false;
        this.mGamePartido.mCorrectAnswer      = false;
        this.mGamePartido.mCorrectAnswerEnd   = false;

        //reset text box
        this.mGamePartido.mApplicationPartido.mStringCorrectAnswer = '';
        this.mGamePartido.mApplicationPartido.mLabelCorrectAnswer.value = '';
*/
}

});

