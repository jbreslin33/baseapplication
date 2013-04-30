//header
#include "gamePartido.h"

//log
#include "../tdreamsock/dreamSockLog.h"

//ObjectTitle
#include "../billboard/objectTitle.h"

//byteBuffer
#include "../bytebuffer/byteBuffer.h"

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

}

