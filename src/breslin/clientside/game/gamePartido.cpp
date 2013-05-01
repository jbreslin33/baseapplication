//header
#include "gamePartido.h"

//log
#include "../tdreamsock/dreamSockLog.h"

//ObjectTitle
#include "../billboard/objectTitle.h"

//byteBuffer
#include "../bytebuffer/byteBuffer.h"

//shape
#include "../shape/shape.h"

/***************************************
*			          CONSTRUCTORS
***************************************/
GamePartido::GamePartido(ApplicationBreslin* applicationBreslin) : Game(applicationBreslin)
{

}

GamePartido::~GamePartido()
{
}

void GamePartido::checkByteBuffer(ByteBuffer* byteBuffer)
{
	Game::checkByteBuffer(byteBuffer);

        byteBuffer->BeginReading();

        int type = byteBuffer->ReadByte();
        
	switch(type)
        {
                case mMessageAskQuestion:
                        askQuestion(byteBuffer);
                        break;
        }
}

void GamePartido::askQuestion(ByteBuffer* byteBuffer)
{
	std::string question;
        int length = byteBuffer->ReadByte();
        for (int i = 0; i < length; i++)
        {
        	char c =  byteBuffer->ReadByte();
                question.append(1,c);
        }

	for(int i = 0; i < mShapeVector->size(); i++)
	{	
		if (mShapeVector->at(i)->mLocal == 1)
		{
			mShapeVector->at(i)->clearTitle();
			mShapeVector->at(i)->appendToTitle(question);
		}
	}
}

