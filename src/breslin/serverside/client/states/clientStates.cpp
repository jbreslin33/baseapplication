//parent
#include "clientStates.h"

//log
#include "../../tdreamsock/dreamSockLog.h"

//states
#include "../../../fsm/stateMachine.h"

//client
#include "../client.h"
#include "../stable/clientStable.h"

//server
#include "../../server/server.h"

/*****************************************
*******       GLOBAL    ******************
****************************************/
GlobalClient* GlobalClient::Instance()
{
  static GlobalClient instance;
  return &instance;
}
void GlobalClient::enter(Client* client)
{
}
void GlobalClient::execute(Client* client)
{

}
void GlobalClient::exit(Client* client)
{
}
bool GlobalClient::onLetter(Client* client, Letter* letter)
{
	LogString("GlobalClient::onLetter");
     	Message* message = letter->mMessage;
        message->BeginReading();
        int type = message->ReadByte();

        if (type == client->mServer->mMessageLogin)
        {
                client->readLoginMessage(message);

                ClientStable* proposedClientStable;
                for (unsigned int i = 0; i < client->mServer->mClientVector.size(); i++)
                {
                        proposedClientStable = client->mServer->mClientVector.at(i);
                        if (client->mStringUsername.compare(proposedClientStable->db_username) == 0 && client->mStringPassword.compare(proposedClientStable->db_password) == 0)
                        {
                                if (client == proposedClientStable)
                                {
                                        proposedClientStable->login();
                                }
                                else //we have a diff clientStable but a pass match...
                                {
                                        client->mConnectionState = 4;

                                        //swap
                                        proposedClientStable->setSocketAddress(&client->mSocketAddress);
                                        proposedClientStable->mConnectionState = 1;
                                        proposedClientStable->mClientID = client->mClientID;
                                        proposedClientStable->login();
                                }
                        }
                }
                return true;
        }
        else
        {
                return false;
        }

}


