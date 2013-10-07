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

},

log: function(msg)
{
	setTimeout(function()
        {
        	throw new Error(msg);
        }, 0);
},

createStates: function()
{
        this.mGamePlay              = new GamePlayPartido(this);
        this.mGamePlayPartidoBattle = new GamePlayPartidoBattle(this);
        this.mGamePlayPartidoCorrectAnswer = new GamePlayPartidoCorrectAnswer(this);
 	this.mGamePlayPartidoReset = new GamePlayPartidoReset(this);
},

setStates: function()
{
        this.mStateMachine.setGlobalState(this.mGameGlobal);
        this.mStateMachine.changeState(this.mGamePlay);
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
}

});
