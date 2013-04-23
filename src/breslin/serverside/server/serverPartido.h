#ifndef SERVERPARTIDO_H
#define SERVERPARTIDO_H

#include "server.h"

class ServerPartido : public Server
{
public:
	ServerPartido(Ogre::Root* root, const char *localIP, int serverPort);	
	~ServerPartido();

	void processUpdate();
        void getQuestions();

        //questions
        std::vector<std::string> mQuestionIDVector;
        std::vector<std::string> mQuestionsVector;
        std::vector<std::string> mAnswersVector;
        std::vector<std::string> mLevelsVector;



};

#endif
