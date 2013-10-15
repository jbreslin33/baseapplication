var GamePartido = new Class(
{

Extends: Game,

initialize: function(applicationPartido)
{
	this.parent(applicationPartido);

	this.mApplicationPartido = applicationPartido;
	
	//questions
	this.mMessageAskQuestion    = -76;

	//show correct answer
	this.mMessageShowCorrectAnswer    = -62;
		
	//battle
	this.mMessageBattleStart = -75;
	this.mMessageBattleEnd   = -74;

	this.mBattleStart = false;
	this.mBattleEnd   = false;

	//correctAnswer
	this.mCorrectAnswerStart = false;
	this.mCorrectAnswerEnd   = false;

	//partido state machines
	this.mPartidoStateMachine = new StateMachine(this);

        this.mPLAY_PARTIDO_GAME              = new PLAY_PARTIDO_GAME(this);
 	this.mRESET_PARTIDO_GAME             = new RESET_PARTIDO_GAME(this);
	
	this.mPartidoStateMachine.changeState(this.mPLAY_PARTIDO_GAME);
 
	//battle state machine	
	this.mBattleStateMachine  = new StateMachine(this);

	this.mBATTLE_OFF                     = new BATTLE_OFF(this);
        this.mANSWER_QUESTION                = new ANSWER_QUESTION(this);
        this.mSHOWCORRECTANSWER_PARTIDO_GAME = new SHOWCORRECTANSWER_PARTIDO_GAME(this);
        
        this.mBattleStateMachine.changeState(this.mBATTLE_OFF);
},

log: function(msg)
{
	setTimeout(function()
        {
        	throw new Error(msg);
        }, 0);
},


askQuestion: function(byteBuffer)
{
        this.mApplicationPartido.mStringQuestion = '';

        this.mApplicationPartido.mStringQuestion = byteBuffer.readByte();

	if (this.mApplicationPartido.mLabelQuestion)
	{
		this.mApplicationPartido.mLabelQuestion.value = this.mApplicationPartido.mStringQuestion; 
	}
	else
	{
	}
       	
	//reset mAnswerTime 
	this.mApplicationPartido.mAnswerTime = 0;
},

correctAnswer: function(byteBuffer)
{
	this.log('correctAnswer called');
        this.mApplicationPartido.mStringCorrectAnswer = '';

        this.mApplicationPartido.mStringCorrectAnswer = byteBuffer.readByte();
	this.log('mStringCorrectAnswer:' + this.mApplicationPartido.mStringCorrectAnswer);

        if (this.mApplicationPartido.mLabelCorrectAnswer)
        {
                this.mApplicationPartido.mLabelCorrectAnswer.value = this.mApplicationPartido.mStringCorrectAnswer;
        }
        else
        {
        }
},

reset: function()
{
	this.parent();

},

processUpdate: function()
{
	this.parent();
        this.mPartidoStateMachine.update();
        this.mBattleStateMachine.update();
}


});
