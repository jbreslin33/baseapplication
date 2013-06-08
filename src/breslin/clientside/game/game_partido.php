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
        this.mGameGlobal            = new GameGlobal(this);
        this.mGameInitialize        = new GameInitialize(this);
        this.mGamePlay              = new GamePlayPartido(this);
        this.mGamePause             = new GamePause(this);
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
	this.log('GamePartido::askQuestion');
        var length = byteBuffer.readByte();

        this.mStringQuestion = '';
        for (i = 0; i < length; i++)
        {
                this.mStringQuestion = this.mStringQuestion + byteBuffer.readByte();
                this.log('question:' + this.mStringQuestion);
        }
}

});
