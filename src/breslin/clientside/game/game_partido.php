var GamePartido = new Class(
{

Extends: Game,

initialize: function(applicationBreslin)
{
	this.parent(applicationBreslin);

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
	//states
	this.mStateMachine = new StateMachine();

        this.mGameGlobal            = new GameGlobal(this);
        this.mGameInitialize        = new GameInitialize(this);
        this.mGamePlay              = new GamePlayPartido(this);
        this.mGamePause             = new GamePause(this);
        this.mGamePlayPartidoBattle = new GamePlayPartidoBattle(this);
},

createStates: function()
{
        this.mStateMachine.setGlobalState(this.mGameGlobal);
        this.mStateMachine.changeState(this.mGamePlay);
},

askQuestion: function(byteBuffer)
{
},

battleStart: function(byteBuffer)
{
	this.log('battleStart');
	this.mBattleStart = true;
},

battleEnd: function(byteBuffer)
{
	this.mBattleEnd = true;
}

});
