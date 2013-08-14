#ifndef BATTLE_H
#define BATTLE_H

#include "../../fsm/stateMachine.h"

class ClientPartido;
class Combatant;
class GamePartido;

class Battle 
{

public:

Battle(GamePartido* gamePartido, ClientPartido* homeClient, ClientPartido* awayClient);
virtual ~Battle();

//update
void update();

StateMachine<Battle>* mStateMachine;

GamePartido* mGamePartido;

Combatant* mHomeCombatant;
Combatant* mAwayCombatant;

int mBattleScore;
std::string mBattleRecordText;

// battle time
long mBattleTime;
long mBattleStartTime;
long mBattleEndTime;
long mBattleLengthTime;

void sendBattleStart();
void sendBattleEnd();
void scoreBattle(int result);
void resetBattle();
void resetRecords();
void resetOpponents();
void setBattleRecordText();


};

#endif

