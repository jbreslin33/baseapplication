#ifndef BATTLE_H
#define BATTLE_H

#include "../../fsm/stateMachine.h"

class ClientPartido;
class Combatant;

class Battle 
{

public:

Battle(ClientPartido* homeClient, ClientPartido* awayClient);
virtual ~Battle();

//update
void update();

StateMachine<Battle>* mStateMachine;

Combatant* mHomeCombatant;
Combatant* mAwayCombatant;

int mBattleScore;
std::string mBattleRecordText;
int mComputerAskedTime;
int mComputerAnswerTime;
int mBattleTime;
int mWins;
int mLosses;
int mTies;

void sendBattleStart();
void sendBattleEnd();
void scoreBattle(int result);
void resetBattle();
void resetRecords();
void resetOpponents();
void setBattleRecordText();


};

#endif

