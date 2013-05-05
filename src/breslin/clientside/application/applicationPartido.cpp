//header
#include "applicationPartido.h"

ApplicationPartido::ApplicationPartido(const char* serverIP, int serverPort) : ApplicationBreslin(serverIP,serverPort)
{

}

ApplicationPartido::~ApplicationPartido()
{

}

void  ApplicationPartido::createBattleScreen()
{
	if (!mLabelQuestion)
        {
                mLabelQuestion  = mTrayMgr->createLabel(OgreBites::TL_CENTER, "mLabelQuestion", "Question:");
        }
	if (!mLabelAnswer)
        {
                mLabelAnswer  = mTrayMgr->createLabel(OgreBites::TL_CENTER, "mLabelAnswer", "Answer:");
        }

}
void  ApplicationPartido::showBattleScreen()
{
	mTrayMgr->moveWidgetToTray(mLabelQuestion,OgreBites::TL_CENTER);
	mTrayMgr->moveWidgetToTray(mLabelAnswer,OgreBites::TL_CENTER);
	
	mLabelQuestion->show();
	mLabelAnswer->show();

	mTrayMgr->showCursor();

	mLabelFocus = mLabelAnswer;
}
void  ApplicationPartido::hideBattleScreen()
{
	mLabelQuestion->hide();
	mLabelAnswer->hide();

	mTrayMgr->removeWidgetFromTray(mLabelQuestion);
	mTrayMgr->removeWidgetFromTray(mLabelAnswer);
}
