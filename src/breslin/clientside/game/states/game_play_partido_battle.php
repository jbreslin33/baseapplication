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
	this.mGamePartido.mApplicationPartido.createBattleScreen();
	this.mGamePartido.mApplicationPartido.showBattleScreen();
	this.mGamePartido.mBattleStart = false;
},

execute: function()
{
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
   			this.mGamePartido.mApplicationPartido.mLabelQuestion.value = '';
   			this.mGamePartido.mApplicationPartido.mLabelAnswer.value = '';
		}
        }
},	

exit: function()
{
	//clear labels
	this.mGamePartido.mApplicationPartido.mStringAnswer = '';
	this.mGamePartido.mApplicationPartido.mLabelAnswer.value = '';
	
	//hide screen
        this.mGamePartido.mApplicationPartido.hideBattleScreen();

	//battle end var
        this.mGamePartido.mBattleEnd   = false;
        this.mGamePartido.mBattleStart = false;
}

});

