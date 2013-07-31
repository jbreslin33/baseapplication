#ifndef SERVERPARTIDO_H
#define SERVERPARTIDO_H

#include "../server.h"

class GamePartido;
class ClientPartido;

class ServerPartido : public Server
{
public:
	ServerPartido(Ogre::Root* root, const char *localIP, int serverPort);	
	~ServerPartido();

	//games
	void addGame(GamePartido* gamePartido);
   	std::vector<GamePartido*>* mGamePartidoVector;

   	//clients
	void createClients();
	virtual void addClient(Client* clientPartido, bool permanent);
        std::vector<ClientPartido*> mClientPartidoVector;
        std::vector<ClientPartido*> mClientPartidoVectorTemp;

        //add school
        static const int mMessageAddSchool = -109;

        //question
        static const int mMessageAskQuestion           = -76;
        static const int mMessageAnswerQuestion        = -84;
        static const int mMessageAnswerQuestionBrowser = -85;
	
	//battle
	static const int mMessageBattleStart = -75; 
	static const int mMessageBattleEnd   = -74; 

	//schools
        std::vector<std::string> mSchoolVector;
        void getSchools();

        //questions
	int mQuestionCount;
        void getQuestions();
        std::vector<std::string> mQuestionIDVector;
        std::vector<std::string> mQuestionVector;
        std::vector<std::string> mAnswerVector;
        std::vector<std::string> mLevelVector;

	void parsePacket(Message *mes, struct sockaddr *address);

	//updates
        virtual void processGames();
        virtual void processClients();
        virtual void sendCommands();

};

#endif
