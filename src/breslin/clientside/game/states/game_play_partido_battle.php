var GamePlayPartidoBattle = new Class(
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
	//reset text labels	
	this.mGamePartido.mApplicationPartido.mStringAnswer = '';
	this.mGamePartido.mApplicationPartido.mLabelAnswer.value = '';
	this.mGamePartido.mApplicationPartido.mLabelAnswer.focus();
	
	this.mGamePartido.mApplicationPartido.showBattleScreen();
	this.mGamePartido.mBattleStart = false;
	this.mGamePartido.mApplicationPartido.mAnswerTime = 0;
},

execute: function()
{
/*
	if (this.mGamePartido.mApplicationPartido.mAnswerTime > 2) //overtime....
        {
                this.mGamePartido.mApplicationPartido.mLabelAnswer.value = 'oot';
                this.mGamePartido.mApplicationPartido.sendAnswer();
		this.mGamePartido.mApplicationPartido.mAnswerTime = 0;
        }
*/

	this.mGamePartido.mApplicationPartido.mLabelAnswer.focus();
	//check for end of batlle
	if (this.mGamePartido.mBattleEnd)
        {
               	this.mGamePartido.mStateMachine.changeState(this.mGamePartido.mGamePlay);
        }
	
	//for enter
   	if (this.mGamePartido.mApplicationPartido.mLabelAnswer == document.activeElement)
       	{ 
		if (this.mGamePartido.mApplicationPartido.mKey_enter == true)
		{
        		this.mGamePartido.mApplicationPartido.sendAnswer();
			this.mGamePartido.mApplicationPartido.mKey_enter = false;
		
			//reset text labels	
			this.mGamePartido.mApplicationPartido.mStringAnswer = '';
			this.mGamePartido.mApplicationPartido.mLabelQuestion.value = '';
			this.mGamePartido.mApplicationPartido.mLabelAnswer.value = '';
		}
        }
},	

exit: function()
{
        this.mGamePartido.mApplicationPartido.hideBattleScreen();
        this.mGamePartido.mBattleEnd   = false;
        this.mGamePartido.mBattleStart = false;
	
	//reset text labels	
	this.mGamePartido.mApplicationPartido.mStringAnswer = '';
	this.mGamePartido.mApplicationPartido.mLabelQuestion.value = '';
	this.mGamePartido.mApplicationPartido.mLabelAnswer.value = '';
}

});

