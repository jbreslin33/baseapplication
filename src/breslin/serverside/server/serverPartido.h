#ifndef SERVERPARTIDO_H
#define SERVERPARTIDO_H

#include "server.h"

class ServerPartido : public Server
{
public:
	ServerPartido(Ogre::Root* root, const char *localIP, int serverPort);	
	~ServerPartido();

        //add school
        static const int mMessageAddSchool = -109;

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
};

#endif
