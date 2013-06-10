var GamePartido = new Class(
{

Extends: Game,

initialize: function(applicationPartido)
{
	this.parent(applicationPartido);

	this.mApplicationPartido = applicationPartido;
	
	//questions
	this.mMessageAskQuestion    = -76;
		
	//battle
	this.mMessageBattleStart = -75;
	this.mMessageBattleEnd   = -74;

	this.mBattleStart = false;
	this.mBattleEnd   = false;
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
	this.log('GamePartido::createStates');
        this.mGamePlay              = new GamePlayPartido(this);
        this.mGamePlayPartidoBattle = new GamePlayPartidoBattle(this);
},

setStates: function()
{
	this.log('GamePartido::setStates');
        this.mStateMachine.setGlobalState(this.mGameGlobal);
        this.mStateMachine.changeState(this.mGamePlay);
},
/*
void GamePartido::askQuestion(ByteBuffer* byteBuffer)
{
        mApplicationPartido->mStringQuestion.clear();
        int length = byteBuffer->ReadByte();
        for (int i = 0; i < length; i++)
        {
                char c =  byteBuffer->ReadByte();
                mApplicationPartido->mStringQuestion.append(1,c);
        }
        if (mApplicationPartido->mLabelQuestion)
        {
                mApplicationPartido->mLabelQuestion->setCaption(mApplicationPartido->mStringQuestion);
        }
        else
        {
                LogString("no label");
        }

        //reset mAnswerTime
        mApplicationPartido->mAnswerTime = 0;
}

*/
askQuestion: function(byteBuffer)
{
        this.mApplicationPartido.mStringQuestion = '';
        var length = byteBuffer.readByte();

        for (i = 0; i < length; i++)
        {
                this.mApplicationPartido.mStringQuestion = this.mApplicationPartido.mStringQuestion + byteBuffer.readByte();
        }
	if (this.mApplicationPartido.mLabelQuestion)
	{
		this.mApplicationPartido.mLabelQuestion.value = this.mApplicationPartido.mStringQuestion; 
	}
	else
	{
		this.log('no label');
	}
       	
	//reset mAnswerTime 
	this.mApplicationPartido.mAnswerTime = 0;
}

});
