#ifndef BATTLE_H
#define BATTLE_H

#include <vector>
using namespace std;

class ShapePartido;
class GamePartido;
class Battler;

class Battle 
{
public:
	
	Battle(GamePartido* gamePartido, std::vector<ShapePartido*> shapePartidoVector);
	~Battle();

//shapes
std::vector<ShapePartido*> mShapePartidoVector;       //every shape in the battle..

std::vector<Battler*> mBattlerVector;       //every battler in the battle..

void processUpdate();
int getQuestionLevelID(int userID);

bool mOver;
	
GamePartido* mGamePartido; 
int mLimit;
	
};

#endif
